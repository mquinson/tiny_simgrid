#include "configuration.h"

//namespace event {

void Configuration::updateMaxEvent(UnfoldingEvent* e)
{
  this->lastEvent = e;
  // update the maximal events for current Conf removing causes from maxEvent and adding e to the maxEvent
  for (auto evt : e->causes.events_) {
    maxEvent.erase(evt); // setMaxEvents.erase(evt->id);
  }
  maxEvent.insert(e);
  /* update the maximal events for the actor=>
   removing the evt shares the same actor with e, then adding e to the actorMaxEvent */

  std::set<UnfoldingEvent*> to_remove;

  for (auto evt : actorMaxEvent.events_)
    if (evt->transition.actor_id == e->transition.actor_id)
      to_remove.insert(evt);
  for (auto evt : to_remove)
    actorMaxEvent.erase(evt);
  actorMaxEvent.insert(e);
}

Configuration Configuration::plus(UnfoldingEvent* evt)
{
  Configuration res;

  res.events_       = this->events_;
  res.maxEvent      = this->maxEvent;
  res.actorMaxEvent = this->actorMaxEvent;
  if (not res.contains(evt))
    res.events_.insert(evt);
  return res;
}

UnfoldingEvent* Configuration ::findTestedComm(UnfoldingEvent* testEvt)
{
  for (auto it : this->events_)
    if (it->transition.commId == testEvt->transition.commId and it->transition.type != "Test" and
        it->transition.actor_id == testEvt->transition.actor_id)
      return it;
  return nullptr;
}

//}
