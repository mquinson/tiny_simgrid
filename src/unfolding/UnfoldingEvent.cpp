#include "UnfoldingEvent.h"
#include "EventSet.h"
#include "configuration.h"

namespace tiny_simgrid {
namespace mc {

template<typename T, typename... Args>
std::unique_ptr<T> make_unique( Args&&... args ) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

UnfoldingEvent::UnfoldingEvent(unsigned int nb_events, Transition t, EventSet causes) : id(nb_events), transition(t) {
    this->causes = make_unique<EventSet>(causes);
}

void UnfoldingEvent::print()
{
  std::cout << "e" << this->id << " =  < t" << this->transition.id << "-p" << this->transition.actor_id << "(";
  if (this->transition.type.length() > 1)
    std::cout << this->transition.type << ")"
              << ","
              << "(";
  if (this->causes->empty())
    std::cout << "-) >";
  else {
    for (auto evt : this->causes->events_)
      std::cout << "e" << evt->id << ",";
    std::cout << " ) >";
  }
}

// Recursively compute the history of a given event by adding the causes of all ancestors
EventSet UnfoldingEvent::getHistory() const
{
  if (causes->empty()) // No direct ancestor => empty history
    return *causes;
  else {
    // EventSet res = causes;
    EventSet res;
    for (auto ancestor : causes->events_) {
      EventSet h1;

      // if event ancestor is already in history set -> we do not need to get it's history

      if (not res.contains(ancestor))
        h1 = ancestor->getHistory();
      h1.insert(ancestor);
      res = res.makeUnion(res, h1);
    }
    return res;
  }
}

bool UnfoldingEvent::inHistory(UnfoldingEvent* otherEvent)
{
  if (this->getHistory().contains(otherEvent))
    return true;
  return false;
}

/*Check whether 2 events a Test and a Send/Receive concern the same communication,
 * Here the events are supposed that they are not causality related
 * */
bool UnfoldingEvent::concernSameComm(UnfoldingEvent* event, UnfoldingEvent* otherEvent)
{
  UnfoldingEvent *testEvt, *SdRcEvt, *testedEvt;
  if (event->transition.mailbox_id != otherEvent->transition.mailbox_id)
    return false;

  if (event->transition.type == "Test") {
    testEvt = event;
    SdRcEvt = otherEvent;
  } else {
    testEvt = otherEvent;
    SdRcEvt = event;
  }

  // 2 sends or 2 receives can not concern the same communication
  int comId = testEvt->transition.commId;

  EventSet testEvtH = testEvt->getHistory();
  EventSet SdRcEvtH = SdRcEvt->getHistory();

  for (auto it : testEvtH.events_)
    if (it->transition.actor_id == testEvt->transition.actor_id and it->transition.commId == comId)
      testedEvt = it;

  if (testedEvt->transition.type == SdRcEvt->transition.type)
    return false;

  int mbId = testedEvt->transition.mailbox_id;

  // std::cout <<" \n ham concern 2: \n";

  if (testedEvt->transition.type == "Isend") {

    EventSet testedEvtH = testedEvt->getHistory();
    int nbSend = 0, nbReceive = 0;

    // count the number of Isend event before testedEvt
    for (auto it : testedEvtH.events_)
      if (it->transition.mailbox_id == mbId and it->transition.type == "Isend")
        nbSend++;

    // count the number of Ireceive event before SdRcEvt
    for (auto it : SdRcEvtH.events_)
      if (it->transition.mailbox_id == mbId and it->transition.type == "Ireceive")
        nbReceive++;

    if (nbSend == nbReceive)
      return true;
  }

  if (testedEvt->transition.type == "Ireceive") {

    // std::cout <<" \n ham concern 3: \n";

    EventSet testedEvtH = testedEvt->getHistory();
    int nbSend = 0, nbReceive = 0;

    // count the number of Receive event before testedEvt
    for (auto it : testedEvtH.events_)
      if (it->transition.mailbox_id == mbId and it->transition.type == "Ireceive")
        nbReceive++;

    // count the number of Isend event before SdRcEvt
    for (auto it : SdRcEvtH.events_)
      if (it->transition.mailbox_id == mbId and it->transition.type == "Isend")
        nbSend++;

    // if (nbSend == nbReceive) std::cout<<"\n CONCERN the same COMM nbsend =" << nbSend <<" nb receive = "<< nbReceive
    // << "  \n";
    if (nbSend == nbReceive)
      return true;
  }

  return false;
}

/** @brief check for conflict in the history of provided events
 *
 * In the paper, this.isConflict(other) is written "this # other"
 */
bool UnfoldingEvent::isConflict(UnfoldingEvent* event, UnfoldingEvent* otherEvent)
{

  // event e should not conflict with itself

  // if(event->conflictEvts.contains(otherEvent) or otherEvent->conflictEvts.contains(event) ) return true;

  if (*event == *otherEvent)
    return false;
  //	std::cout<<"\n trong ham cflict";

  EventSet h1, h2;
  h1 = event->getHistory();
  h2 = otherEvent->getHistory();

  // checking causality relation, if they are in a causality relation return false
  if (h1.contains(otherEvent) or h2.contains(event))
    return false;

  // check direct conflict
  if (event->transition.isDependent(otherEvent->transition))
    return true;

  //  if 2 event they have the same causes, just check their last transition
  if (event->causes == otherEvent->causes)
    return event->transition.isDependent(otherEvent->transition);

  // if not, then check dependent relation on their full histories

  else {

    h1.insert(event);
    h2.insert(otherEvent);
    EventSet his = h1;
    // FIXME remove all common events
    for (auto evt : his.events_)
      if (h2.contains(evt)) {
        h1.erase(evt);
        h2.erase(evt);
      }

    return h1.depends(h2);
  }
  //	std::cout<<"\n trong ham cflict6";

  return false;
}

/** @brief Checks if current event is in immediate conflict with the provided one
 *
 * For that, there is two conditions to meet:
 *  - both events are in conflict (there is a conflict in their histories)
 *  -      Union(hist1,       hist2, evt2) is a valid configuration
 *    AND  Union(hist1, evt1, hist2)       is a valid configuration
 *
 * In the paper, e1.isImmediate(e2) will be written "e1 #ⁱ e2"
 */

bool UnfoldingEvent::isImmediateConflict(UnfoldingEvent* evt1, UnfoldingEvent* evt2)
{

  // event e should not conflict with itself
  if (*evt1 == *evt2)
    return false;

  // The first condition is easy to check
  if (not evt1->isConflict(evt1, evt2))
    return false;

  // Now, check the second condition
  EventSet hist1 = evt1->getHistory();
  EventSet hist2 = evt2->getHistory();

  // First compare the existing configurations

  // romove all common events
  for (auto e1 : hist2.events_)
    if (evt1->isConflict(evt1, e1))
      return false;

  // Compare the first config to the second new event
  for (auto e1 : hist1.events_)
    if (evt2->isConflict(evt2, e1))
      return false;
  // Every tests passed
  return true;
}

bool UnfoldingEvent::isImmediateConflict1(UnfoldingEvent* evt1, UnfoldingEvent* evt2)
{
  // event e should not conflict with itself
  if (*evt1 == *evt2)
    return false;

  bool chk1 = false, chk2 = false;

  if (not evt1->transition.isDependent(evt2->transition)) {

    chk1 = true;
    chk2 = true;
    if (evt1->transition.type == "Test" and (evt2->transition.type == "Isend" or evt2->transition.type == "Ireceive")) {
      if (not evt1->concernSameComm(evt1, evt2))
        return false;
      else {
        chk2 = false;
      }
    }

    if (evt2->transition.type == "Test" and (evt1->transition.type == "Isend" or evt1->transition.type == "Ireceive")) {
      if (not evt1->concernSameComm(evt1, evt2))
        return false;
      else {
        chk2 = false;
      }
    }
  }
  // 2 transitions are not depend and they are one is test other one is send/receive  -> return false

  if (chk1 and chk2)
    return false;

  // Now, check the second condition
  EventSet hist1  = evt1->getHistory();
  EventSet hist2  = evt2->getHistory();
  EventSet hist11 = hist1, hist21 = hist2;

  // if causality ralated - > no immidiate conflict
  if (hist1.contains(evt2) or hist2.contains(evt1))
    return false;

  for (auto e1 : hist1.events_)
    if (hist2.contains(e1)) {
      hist11.erase(e1);
      hist21.erase(e1);
    }

  EventSet evtS1, evtS2;

  evtS1.insert(evt1);
  evtS2.insert(evt2);

  if (hist11.depends(hist21) or evtS1.depends(hist21) or evtS2.depends(hist11)) {
    return false;
  }

  // std::cout <<"se tra ve true nhe ### \n";

  return true;
}

// checking conflict relation between one event and one configuration or one history, it used when computing enC
// there is a better way by checking the event with maximal events in the configuration, (change type of enC )
bool UnfoldingEvent::conflictWithConfig(UnfoldingEvent* event, Configuration* config)
{
    if (config->size() == 0)
    return false;

  // we don't really need to check the whole config. The maximal event should be enough.
    for (auto evt : config->maxEvent.events_)
    if (event->isConflict(event, evt))
      return true;
  return false;
}

// this operator is used for ordering in a set (need a key)
bool UnfoldingEvent::operator<(const UnfoldingEvent& other) const
{
  if ((this->transition.actor_id < other.transition.actor_id) or (this->transition.id < other.transition.id) or
      (not(this->causes == other.causes)))
    return true;
  return false;
}

/** @brief check semantic equality (same transition, same causes) */
bool UnfoldingEvent::operator==(const UnfoldingEvent& other) const
{

    if ((this->transition.id != other.transition.id) or (this->transition.actor_id != other.transition.actor_id))
        return false;
    if (this->causes->size() != other.causes->size())
        return false;

    for (auto it : this->causes->events_) {
        bool chk1 = false;
        for (auto it1 : other.causes->events_)
            if (*it == *it1) {
                chk1 = true;
                break;
            }
        if (not chk1)
            return false;
    }

    return true;
}

} // namespace mc
} // namespace tiny_simgrid
