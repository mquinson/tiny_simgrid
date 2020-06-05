#ifndef UNFOLDINGEVENT_H
#define UNFOLDINGEVENT_H

#include <iostream>
#include <memory>
#include "../transition/transition.h"
#include "../state/state.h"
//#include "../EventSet/EventSet.h"
//#include "../configuration/configuration.h"

class EventSet;
class Configuration;

class UnfoldingEvent
{
public:
    UnfoldingEvent(State* s) : appState(*s) {}
    UnfoldingEvent(unsigned int nb_events, Transition t, EventSet* causes);// : id(nb_events), transition(t) { this->causes = make_unique<EventSet>(*causes); }

    int id {-1};
    State appState;
    Transition transition; // The last transition made to reach that state
    std::unique_ptr<EventSet> causes; // used to store directed ancestors of event e

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

#endif // UNFOLDINGEVENT_H
