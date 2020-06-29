#include <algorithm>
#include <array>
#include <iostream>
#include <list>
#include <memory>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <math.h>

#include "transition.h"
#include "state.h"
#include "configuration.h"
#include "UnfoldingEvent.h"
#include "EventSet.h"
#include "../app/actor.h"
#include "Checker.h"

class Session;

using namespace std;

namespace tiny_simgrid {
namespace mc {

class UnfoldingChecker : public Checker {
    unsigned long expandedStatesCount_ = 0;
    // int Mode = 1; // Mode = 1 is a mutexed model
    std::vector<unsigned int> confs_expected_;
    bool confs_check_             = false;
    int error_                    = 0;
    unsigned int expected_events_ = 0;

public:    
    UnfoldingChecker() = default;
    UnfoldingChecker(Session& s) : Checker(s) {};
    UnfoldingChecker(std::vector<unsigned int> confs, unsigned int expected_events)
        : confs_expected_(confs), confs_check_(true), expected_events_(expected_events) {}

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


    int get_error_count() override { return error_; }
    void run() override;
};

extern unsigned int nb_events;
extern unsigned int nb_traces;
extern EventSet U, G, gD;

} // namespace mc
} // namespace tiny_simgrid
