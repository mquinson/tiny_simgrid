#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <iostream>
#include <algorithm>
#include <set>
#include "../App/Transition.h"
#include "State.h"

namespace uc {

class UnfoldingEvent;

class EventSet {
public:
    EventSet() = default;
//    EventSet(const EventSet&) = default;
//    EventSet& operator=(EventSet const&) = default;
//    EventSet(EventSet&&) = default;
//    ~EventSet() = default;

    bool contains(UnfoldingEvent* e);
    UnfoldingEvent* find(UnfoldingEvent* e);
    void subtruct(EventSet otherSet);
    bool depends(EventSet s2);
    bool isConfig();
    size_t size() const;
    std::set<UnfoldingEvent*> events_;
    bool conflictWithEvt(UnfoldingEvent* e);
    bool isEmptyIntersection(EventSet evtS1, EventSet evtS2);

    static EventSet makeUnion(EventSet s1, EventSet s2);
    static EventSet makeIntersection(EventSet s1, EventSet s2);
    const UnfoldingEvent* first();
    bool empty() const;
    UnfoldingEvent* begin() const;
    UnfoldingEvent* end() const;

    void insert(UnfoldingEvent*);
    void erase(UnfoldingEvent*);
    bool operator==(const EventSet& other) const;

    EventSet minus(UnfoldingEvent* evt);
    EventSet plus(UnfoldingEvent*);
};

class EvtSetTools {
public:
    static bool contains(std::set<UnfoldingEvent*> events, UnfoldingEvent* e);
    static UnfoldingEvent* find(std::set<UnfoldingEvent*> events, UnfoldingEvent* e);
    static void subtract(std::set<UnfoldingEvent*>& events, std::set<UnfoldingEvent*> otherSet);
    static bool depends(std::set<UnfoldingEvent*> events, std::set<UnfoldingEvent*> otherSet);
    static bool isEmptyIntersection(std::set<UnfoldingEvent*> evtS1, std::set<UnfoldingEvent*> evtS2);
    static std::set<UnfoldingEvent*> makeUnion(std::set<UnfoldingEvent*> s1, std::set<UnfoldingEvent*> s2);
    static std::set<UnfoldingEvent *> makeIntersection(std::set<UnfoldingEvent *> s1, std::set<UnfoldingEvent *> s2);
    static void insert(std::set<UnfoldingEvent*>& events, UnfoldingEvent* e);
    static void erase(std::set<UnfoldingEvent*>& events, UnfoldingEvent* e);
    static std::set<UnfoldingEvent*> minus(std::set<UnfoldingEvent *> events, UnfoldingEvent* e);
    static std::set<UnfoldingEvent*> plus(std::set<UnfoldingEvent *> events, UnfoldingEvent* e);
};

typedef struct s_evset_in {
    EventSet causuality_events;
    EventSet cause;
    EventSet ancestorSet;
} s_evset_in_t;

class Configuration : public EventSet {
public:
    EventSet maxEvent;         // Events recently added to events_
    EventSet actorMaxEvent;    // maximal events of the actors in current configuration
    UnfoldingEvent* lastEvent; // The last added event

    Configuration plus_config(UnfoldingEvent*);
    void createEvts(Configuration C, EventSet& result, const app::Transition &t,
                    s_evset_in_t ev_sets, bool chk, UnfoldingEvent* immPreEvt);
    void updateMaxEvent(UnfoldingEvent*);         // update maximal events of the configuration and actors
    UnfoldingEvent* findActorMaxEvt(int actorId); // find maximal event of a Actor whose id = actorId

    UnfoldingEvent* findTestedComm(UnfoldingEvent* testEvt); // find comm tested by action testTrans

    Configuration() = default;
    Configuration(const Configuration&) = default;
    Configuration& operator=(Configuration const&) = default;
    Configuration(Configuration&&) = default;
    ~Configuration() = default;
};

class UnfoldingEvent {
public:
    int id = -1;
    State appState;
    app::Transition transition; // The last transition made to reach that state
    EventSet causes;       // used to store directed ancestors of event e
    EventSet conflictEvts;

    explicit UnfoldingEvent(State* s) : appState(*s) {}
    UnfoldingEvent(unsigned int nb_events, app::Transition t, EventSet causes);
//    UnfoldingEvent(unsigned int nb_events, const Transition &t, const EventSet &causes);
    UnfoldingEvent(const UnfoldingEvent&) = default;
    UnfoldingEvent& operator=(UnfoldingEvent const&) = default;
    UnfoldingEvent(UnfoldingEvent&&) = default;
    ~UnfoldingEvent() = default;

    EventSet getHistory() const;

    bool isConflict(UnfoldingEvent* event, UnfoldingEvent* otherEvent);
    bool concernSameComm(UnfoldingEvent* event, UnfoldingEvent* otherEvent);

    // check otherEvent is in my history ?
    bool inHistory(UnfoldingEvent* otherEvent) const;

    bool isImmediateConflict1(UnfoldingEvent* evt, UnfoldingEvent* otherEvt);

    bool conflictWithConfig(UnfoldingEvent* event, Configuration config);
//    bool operator<(const UnfoldingEvent& other);
    bool operator==(const UnfoldingEvent& other) const;
    void print() const;
};

} // namespace uc

#endif // GLOBAL_HPP
