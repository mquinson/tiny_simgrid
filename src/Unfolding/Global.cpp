#include "Global.hpp"

namespace uc {

//UnfoldingEvent::UnfoldingEvent(unsigned int nb_events, const Transition &t, const EventSet &causes)
UnfoldingEvent::UnfoldingEvent(unsigned int nb_events,  app::Transition t,  EventSet causes)
{

    this->id         = nb_events;
    this->causes     = causes;
    this->transition = t;
}

void UnfoldingEvent::print() const
{

    std::cout << "e" << this->id << " =  < t" << this->transition.id << "-p" << this->transition.actor_id << "(";
    if (this->transition.type.length() > 1)
        std::cout << this->transition.type << ")"
                  << ","
                  << "(";
    if (this->causes.empty())
        std::cout << "-) >";
    else {
        for (auto evt : this->causes)
            std::cout << "e" << evt->id << ",";
        std::cout << " ) >";
    }
}

// Recursively compute the history of a given event by adding the causes of all ancestors
EventSet UnfoldingEvent::getHistory() const
{
    if (causes.empty()) // No direct ancestor => empty history
        return causes;
    else {
        EventSet res;
        for (auto ancestor : causes) {
            EventSet h1;

            // if event ancestor is already in history set -> we do not need to get it's history

            if (!EvtSetTools::contains(res, ancestor))
                h1 = ancestor->getHistory();
            EvtSetTools::insert(h1, ancestor);
            res = EvtSetTools::makeUnion(res, h1);
        }
        return res;
    }
}

bool UnfoldingEvent::inHistory(UnfoldingEvent* otherEvent) const
{
    auto history = getHistory();
    if (EvtSetTools::contains(history, otherEvent))
//    if (this->getHistory().contains(otherEvent))
        return true;
    return false;
}

/*Check whether 2 events a Test and a Send/Receive concern the same communication,
 * Here the events are supposed that they are not causality related
 * */

bool UnfoldingEvent::concernSameComm(UnfoldingEvent* event, UnfoldingEvent* otherEvent)
{
    UnfoldingEvent *testEvt = nullptr, *SdRcEvt = nullptr, *testedEvt = nullptr;

    // std::cout <<" \n hien thi evet trong ham concern :";
    // event->print();
    // otherEvent->print();
    // std::cout <<" \n ham concern 1: \n";

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

    for (auto it : testEvtH)
        if (it->transition.actor_id == testEvt->transition.actor_id && it->transition.commId == comId)
            testedEvt = it;

    if (testedEvt->transition.type == SdRcEvt->transition.type)
        return false;

    int mbId = testedEvt->transition.mailbox_id;

    // std::cout <<" \n ham concern 2: \n";

    if (testedEvt->transition.type == "Isend") {

        EventSet testedEvtH = testedEvt->getHistory();
        int nbSend = 0, nbReceive = 0;

        // count the number of Isend event before testedEvt
        for (auto it : testedEvtH)
            if (it->transition.mailbox_id == mbId && it->transition.type == "Isend")
                nbSend++;

        // count the number of Ireceive event before SdRcEvt
        for (auto it : SdRcEvtH)
            if (it->transition.mailbox_id == mbId && it->transition.type == "Ireceive")
                nbReceive++;

        if (nbSend == nbReceive)
            return true;
    }

    if (testedEvt->transition.type == "Ireceive") {

        // std::cout <<" \n ham concern 3: \n";

        EventSet testedEvtH = testedEvt->getHistory();
        int nbSend = 0, nbReceive = 0;

        // count the number of Receive event before testedEvt
        for (auto it : testedEvtH)
            if (it->transition.mailbox_id == mbId && it->transition.type == "Ireceive")
                nbReceive++;

        // count the number of Isend event before SdRcEvt
        for (auto it : SdRcEvtH)
            if (it->transition.mailbox_id == mbId && it->transition.type == "Isend")
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
    if (*event == *otherEvent)
        return false;

    EventSet h1, h2;
    h1 = event->getHistory();
    h2 = otherEvent->getHistory();

    // checking causality relation, if they are in a causality relation return false
    if (EvtSetTools::contains(h1, otherEvent) || EvtSetTools::contains(h2, event))
        return false;

    // check direct conflict
    if (event->transition.isDependent(otherEvent->transition))
        return true;

    //  if 2 event they have the same causes, just check their last transition
    if (event == otherEvent)
        return event->transition.isDependent(otherEvent->transition);
    else {
        EvtSetTools::insert(h1,event);
        EvtSetTools::insert(h2, otherEvent);
        EventSet his = h1;
        // FIXME remove all common events
        for (auto evt : his)
            if (EvtSetTools::contains(h2, evt)) {
                EvtSetTools::erase(h1, evt);
                EvtSetTools::erase(h2, evt);
            }

        return EvtSetTools::depends(h1, h2);
    }
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
bool UnfoldingEvent::isImmediateConflict1(UnfoldingEvent* evt1, UnfoldingEvent* evt2)
{

    // event e should not conflict with itself
    if (*evt1 == *evt2)
        return false;

    bool chk1 = false, chk2 = false;

    if (!evt1->transition.isDependent(evt2->transition)) {

        chk1 = true;
        chk2 = true;
        if (evt1->transition.type == "Test" && (evt2->transition.type == "Isend" || evt2->transition.type == "Ireceive")) {
            if (!evt1->concernSameComm(evt1, evt2))
                return false;
            else {
                chk2 = false;
            }
        }

        if (evt2->transition.type == "Test" && (evt1->transition.type == "Isend" || evt1->transition.type == "Ireceive")) {
            if (!evt1->concernSameComm(evt1, evt2))
                return false;
            else {
                chk2 = false;
            }
        }
    }
    // 2 transitions are not depend and they are one is test other one is send/receive  -> return false

    if (chk1 && chk2)
        return false;

    // Now, check the second condition
    EventSet hist1  = evt1->getHistory();
    EventSet hist2  = evt2->getHistory();
    EventSet hist11 = hist1, hist21 = hist2;

    // if causality ralated - > no immidiate conflict
    if (EvtSetTools::contains(hist1, evt2) || EvtSetTools::contains(hist2, evt1))
        return false;

    for (auto e1 : hist1)
        if (EvtSetTools::contains(hist2, e1)) {
            EvtSetTools::erase(hist11, e1);
            EvtSetTools::erase(hist21, e1);
        }

    EventSet evtS1, evtS2;

    EvtSetTools::insert(evtS1, evt1);
    EvtSetTools::insert(evtS2, evt2);

    if (EvtSetTools::depends(hist11, hist21) || EvtSetTools::depends(evtS1, hist21) || EvtSetTools::depends(evtS2, hist11)) {
        return false;
    }

    // std::cout <<"se tra ve true nhe ### \n";

    return true;
}

// checking conflict relation between one event and one configuration or one history, it used when computing enC
// there is a better way by checking the event with maximal events in the configuration, (change type of enC )
bool UnfoldingEvent::conflictWithConfig(UnfoldingEvent* event, Configuration config)
{    
    if (config.events_.size() == 0)
        return false;
    // we don't really need to check the whole config. The maximal event should be enough.
    for (auto evt : config.maxEvent)
        if (event->isConflict(event, evt))
            return true;
    return false;
}

// this operator is used for ordering in a set (need a key)
//bool UnfoldingEvent::operator<(const UnfoldingEvent& other)
//{
//    if ((this->transition.actor_id < other.transition.actor_id) || (this->transition.id < other.transition.id) or
//            (!(this->causes == other.causes)))
//        return true;
//    return false;
//}

/** @brief check semantic equality (same transition, same causes) */
bool UnfoldingEvent::operator==(const UnfoldingEvent& other) const
{

    if ((this->transition.id != other.transition.id) || (this->transition.actor_id != other.transition.actor_id))
        return false;
    if (this->causes.size() != other.causes.size())
        return false;

    for (auto it : this->causes) {
        bool chk1 = false;
        for (auto it1 : other.causes)
            if (*it == *it1) {
                chk1 = true;
                break;
            }
        if (!chk1)
            return false;
    }

    return true;
}

void Configuration::updateMaxEvent(UnfoldingEvent* e)
{
    this->lastEvent = e;
    // update the maximal events for current Conf removing causes from maxEvent and adding e to the maxEvent
    for (auto evt : e->causes) {
        EvtSetTools::erase(maxEvent, evt); // setMaxEvents.erase(evt->id);
    }
    EvtSetTools::insert(maxEvent, e);
    /* update the maximal events for the actor=>
   removing the evt shares the same actor with e, then adding e to the actorMaxEvent */

    std::set<UnfoldingEvent*> to_remove;

    for (auto evt : actorMaxEvent)
        if (evt->transition.actor_id == e->transition.actor_id)
            to_remove.insert(evt);
    for (auto evt : to_remove)
        EvtSetTools::erase(actorMaxEvent, evt);
    EvtSetTools::insert(actorMaxEvent, e);
}

Configuration Configuration::plus_config(UnfoldingEvent* evt)
{
    Configuration res;

    res.events_       = this->events_;
    res.maxEvent      = this->maxEvent;
    res.actorMaxEvent = this->actorMaxEvent;
    if (!EvtSetTools::contains(res.events_, evt))
        res.events_.insert(evt);
    return res;
}

UnfoldingEvent* Configuration ::findTestedComm(UnfoldingEvent* testEvt)
{
    for (auto it : this->events_)
        if (it->transition.commId == testEvt->transition.commId && it->transition.type != "Test" &&
                it->transition.actor_id == testEvt->transition.actor_id)
            return it;
    return nullptr;
}

bool EvtSetTools::contains(std::set<UnfoldingEvent*> events, UnfoldingEvent* e)
{
    for (auto evt : events)
        if (*evt == *e)
            return true;
    return false;
}

UnfoldingEvent* EvtSetTools::find(std::set<UnfoldingEvent*> events, UnfoldingEvent* e)
{
    for (auto evt : events)
        if (*evt == *e) {
            return evt;
        }
    return nullptr;
}

void EvtSetTools::subtract(std::set<UnfoldingEvent*>& events, std::set<UnfoldingEvent*> otherSet)
{
    for (auto evt : otherSet)
        EvtSetTools::erase(events, evt);
}


/** @brief Check if I'm dependent with another EventSet
 * Here we suppose that 2 given event sets do not have common events
*/
bool EvtSetTools::depends(std::set<UnfoldingEvent*> events, std::set<UnfoldingEvent*> otherSet)
{
    if (events.empty() || otherSet.empty())
        return false;

    for (auto e1 : events)
        for (auto e2 : otherSet)
            if (e1->transition.isDependent(e2->transition))
                return true;
            else if ((e1->transition.type == "Test" &&
                      (e2->transition.type == "Isend" || e2->transition.type == "Ireceive")) ||
                     (e2->transition.type == "Test" &&
                      (e1->transition.type == "Isend" || e1->transition.type == "Ireceive")))
                if (e1->concernSameComm(e1, e2))
                    return true;

    return false;
}

bool EvtSetTools::isEmptyIntersection(std::set<UnfoldingEvent*> evtS1, std::set<UnfoldingEvent*> evtS2)
{
    if(evtS1.size() == 0 || evtS2.size() == 0)
        return false;
    for(auto evt : evtS2)
        if(EvtSetTools::contains(evtS1, evt))
            return false;
    return true;
}

std::set<UnfoldingEvent*> EvtSetTools::makeUnion(std::set<UnfoldingEvent*> s1, std::set<UnfoldingEvent*> s2)
{
    std::set<UnfoldingEvent*> res = s1;
    for (auto evt : s2)
        EvtSetTools::insert(res, evt);
    return res;
}

std::set<UnfoldingEvent*> EvtSetTools::makeIntersection(std::set<UnfoldingEvent*> s1, std::set<UnfoldingEvent*> s2)
{
    std::set<UnfoldingEvent*> res;
    std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(),
                          std::inserter(res, res.begin()));
    return res;
}

void EvtSetTools::insert(std::set<UnfoldingEvent*>& events, UnfoldingEvent* e)
{
    if(!EvtSetTools::contains(events, e))
        events.insert(e);
}

void EvtSetTools::erase(std::set<UnfoldingEvent*>& events, UnfoldingEvent* e)
{
    std::set<UnfoldingEvent*> evtS = events;
    for (auto it : evtS) {
        if (*it == *e)
            events.erase(it);
    }
}

std::set<UnfoldingEvent*> EvtSetTools::minus(std::set<UnfoldingEvent*> events, UnfoldingEvent* e)
{
    std::set<UnfoldingEvent*> res = events;
    for (auto evt : events)
        if (*evt == *e)
            res.erase(e);
    return res;
}

std::set<UnfoldingEvent*> EvtSetTools::plus(std::set<UnfoldingEvent *> events, UnfoldingEvent* e)
{
    std::set<UnfoldingEvent*> res = events;
    if (!EvtSetTools::contains(events, e))
        res.insert(e);
    return res;
}

} // namespace uc
