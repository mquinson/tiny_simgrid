#include "eventset.h"

EventSet::EventSet()
{

}

bool EventSet::contains(UnfoldingEvent* e)
{
  for (auto evt : this->events_)
    if (*evt == *e)
      return true;
  return false;
}

void EventSet::subtruct(EventSet otherSet)
{
  for (auto evt : otherSet.events_)
    this->erase(evt);
}

UnfoldingEvent* EventSet::find(UnfoldingEvent* e)
{

  for (auto evt : this->events_)
    if (*evt == *e) {
      return evt;
    }
  return nullptr;
}

/** @brief Check if I'm dependent with another EventSet
 * Here we suppose that 2 given event sets do not have common events */
bool EventSet::depends(EventSet s2)
{
  if (this->events_.empty() or s2.events_.empty())
    return false;

  for (auto e1 : this->events_)
    for (auto e2 : s2.events_)
      if (e1->transition.isDependent(e2->transition))
        return true;
      else if ((e1->transition.type == "Test" and
                (e2->transition.type == "Isend" or e2->transition.type == "Ireceive")) or
               (e2->transition.type == "Test" and
                (e1->transition.type == "Isend" or e1->transition.type == "Ireceive")))
        if (e1->concernSameComm(e1, e2))
          return true;

  return false;
}

bool EventSet::isConfig()
{
  if ((this->size() == 1) && (this->begin()->causes.empty()))
    return true;

  // checking conflict relation between one event and all other events in the set
  for (auto e1 : events_) {
    for (auto e2 : events_) {
      if (*e1 == *e2)
        continue;

      if (e1->isConflict(e1, e2))
        return false;
    }
    // Every event of the history should be in the set
    for (auto ancestor : e1->getHistory().events_)
      if (not(this->contains(ancestor)))
        return false;
  }

  return true;
}

EventSet EventSet::makeUnion(EventSet s1, EventSet s2)
{
  EventSet res = s1;
  //	res.events_.insert(s1.events_.begin(), s1.events_.end());
  //	res.events_.insert(s2.events_.begin(), s2.events_.end());

  for (auto evt : s2.events_)
    res.insert(evt);

  return res;
}

EventSet EventSet::makeIntersection(EventSet s1, EventSet s2)
{
  EventSet res;
  std::set_intersection(s1.events_.begin(), s1.events_.end(), s2.events_.begin(), s2.events_.end(),
                        std::inserter(res.events_, res.events_.begin()));
  return res;
}

EventSet EventSet::minus(UnfoldingEvent* evt)
{

  EventSet res;
  res.events_ = this->events_;
  for (auto e : this->events_)
    if (*e == *evt)
      res.erase(e);

  return res;
}

EventSet EventSet::plus(UnfoldingEvent* evt)
{
  EventSet res;
  res.events_ = this->events_;
  if (not res.contains(evt))
    res.events_.insert(evt);
  return res;
}

size_t EventSet::size() const
{
  return events_.size();
}

bool EventSet::empty() const
{
  return this->events_.empty();
}

UnfoldingEvent* EventSet::begin() const
{
  return *events_.begin();
}

UnfoldingEvent* EventSet::end() const
{
  return *events_.end();
}

bool EventSet::operator==(const EventSet& other) const
{

  return this->events_ == other.events_;
}
void EventSet::insert(UnfoldingEvent* e)
{
  if (not this->contains(e))
    events_.insert(e);
}

void EventSet::erase(UnfoldingEvent* e)
{
  std::set<UnfoldingEvent*> evtS = this->events_;

  for (auto it : evtS)
    if (*it == *e)
      this->events_.erase(it);
}

bool EventSet::conflictWithEvt(UnfoldingEvent* e)
{
  for (auto evt : this->events_)
    if (evt->isConflict(evt, e))
      return true;
  return false;
}

bool EventSet::isEmptyIntersection(EventSet evtS1, EventSet evtS2)
{

  if (evtS1.size() == 0 or evtS2.size() == 0)
    return false;

  for (auto evt : evtS2.events_)
    if (evtS1.contains(evt))
      return false;

  return true;
}


