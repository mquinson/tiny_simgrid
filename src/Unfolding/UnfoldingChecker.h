#ifndef UNFOLDINGCHECKER_H
#define UNFOLDINGCHECKER_H

#include "list"
#include "Global.hpp"

extern unsigned int nb_events;
extern unsigned int nb_traces;
extern EventSet U, G, gD;

class UnfoldingChecker {
    unsigned long expandedStatesCount_ = 0;
    // int Mode = 1; // Mode = 1 is a mutexed model
    std::vector<unsigned int> confs_expected_;
    bool confs_check_             = false;
    int error_                    = 0;
    unsigned int expected_events_ = 0;

public:
    UnfoldingChecker() = default;
    UnfoldingChecker(std::vector<unsigned int> confs, unsigned int expected_events)
        : confs_expected_(confs), confs_check_(true), expected_events_(expected_events)
    {
    }

    void explore(State* state); // Start the exploration
    // Recursive function
    void explore(Configuration C, std::list<EventSet> maxEvtHistory, EventSet D, EventSet A, UnfoldingEvent* currentEvt,
                 EventSet prev_enC, std::set<Actor> proc);

    void extend(std::set<Actor> proc, Configuration C, std::list<EventSet> maxEvtHistory, EventSet& ExC, EventSet& enC);
    void remove(UnfoldingEvent* e, Configuration C, EventSet D);
    EventSet computeAlt(EventSet D, Configuration C);
    EventSet KpartialAlt(EventSet D, Configuration C);

    void genEventFromCandidate(EventSet& result, Transition t, UnfoldingEvent* preEvt, EventSet U1, EventSet Uc);
    EventSet filter(Configuration C, EventSet U);

    int error_count() { return error_; }
};

#endif // UNFOLDINGCHECKER_H
