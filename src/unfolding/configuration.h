#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "EventSet.h"
#include "UnfoldingEvent.h"

namespace tiny_simgrid {
namespace mc {

class Configuration : public EventSet {
public:
    EventSet maxEvent;         // Events recently added to events_
    EventSet actorMaxEvent;    // maximal events of the actors in current configuration
    UnfoldingEvent* lastEvent; // The last added event

    Configuration plus(UnfoldingEvent*);
    void createEvts(Configuration C, EventSet& result, Transition t, EventSet causuality_events, EventSet cause,
                    EventSet candidateHistory, bool chk, UnfoldingEvent* immPreEvt);
    void updateMaxEvent(UnfoldingEvent*);         // update maximal events of the configuration and actors
    UnfoldingEvent* findActorMaxEvt(int actorId); // find maximal event of a Actor whose id = actorId

    UnfoldingEvent* findTestedComm(UnfoldingEvent* testEvt); // find comm tested by action testTrans
};

} // namespace mc
} // namespace tiny_simgrid

#endif // CONFIGURATION_H
