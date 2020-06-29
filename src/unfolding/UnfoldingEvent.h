#ifndef UNFOLDINGEVENT_H
#define UNFOLDINGEVENT_H

#include <iostream>
#include <memory>
#include "transition.h"
#include "state.h"

namespace tiny_simgrid {
namespace mc {

class EventSet;
class Configuration;

class UnfoldingEvent {
public:
    UnfoldingEvent(State* s) : appState(*s) {}
    UnfoldingEvent(unsigned int nb_events, Transition t, EventSet causes);

    int id {-1};
    State appState;
    Transition transition; // The last transition made to reach that state

    std::unique_ptr<EventSet> causes; // used to store directed ancestors of event e
    std::unique_ptr<EventSet> conflictEvts; // used for Test and Send/Receive events, storing conflicts events with me (concern the same
                                            // communication)

    EventSet getHistory() const;

    bool isConflict(UnfoldingEvent* event, UnfoldingEvent* otherEvent);
    bool concernSameComm(UnfoldingEvent* event, UnfoldingEvent* otherEvent);

    // check otherEvent is in my history ?
    bool inHistory(UnfoldingEvent* otherEvent);

    bool isImmediateConflict(UnfoldingEvent* evt, UnfoldingEvent* otherEvt);
    bool isImmediateConflict1(UnfoldingEvent* evt, UnfoldingEvent* otherEvt);

    bool conflictWithConfig(UnfoldingEvent* event, Configuration* config);
    bool operator<(const UnfoldingEvent& other) const;
    bool operator==(const UnfoldingEvent& other) const;
    void print();
};

} // namespace mc
} // namespace tiny_simgrid

#endif // UNFOLDINGEVENT_H
