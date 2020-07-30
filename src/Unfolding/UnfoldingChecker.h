#ifndef UNFOLDINGCHECKER_H
#define UNFOLDINGCHECKER_H

#include "list"
#include "Global.hpp"
//#include "../App/AppSide.h"

namespace uc {

class UnfoldingChecker {
    unsigned long expandedStatesCount_ = 0;
    // int Mode = 1; // Mode = 1 is a mutexed model
    std::vector<unsigned int> confs_expected_;
    bool confs_check_             = false;
    int error_                    = 0;
    unsigned int expected_events_ = 0;
//    std::unique_ptr<AppSide> app_side_ = std::unique_ptr<AppSide>(new AppSide());;

public:    
    UnfoldingChecker() = default;
    UnfoldingChecker(std::vector<unsigned int> confs, unsigned int expected_events) : confs_expected_(confs), confs_check_(true), expected_events_(expected_events) {}
    UnfoldingChecker(const UnfoldingChecker&) = default;
    UnfoldingChecker& operator=(UnfoldingChecker const&) = default;
    UnfoldingChecker(UnfoldingChecker&&) = default;
    ~UnfoldingChecker() = default;

    void explore(State* state); // Start the exploration
    // Recursive function
    void explore(Configuration C, std::list<EventSet> maxEvtHistory, EventSet D, EventSet A, UnfoldingEvent* currentEvt,
                 EventSet prev_enC, std::set<Actor> proc);

    void extend(std::set<Actor> proc, Configuration C, std::list<EventSet> maxEvtHistory, EventSet& ExC, EventSet& enC);
    void remove(UnfoldingEvent* e, Configuration C, EventSet D);
    EventSet KpartialAlt(EventSet D, Configuration C) const;

    void genEventFromCandidate(EventSet& result, Transition t, UnfoldingEvent* preEvt, EventSet U1, EventSet Uc);
    EventSet filter(Configuration C, EventSet U);

    int error_count() { return error_; }
};

} // namespace uc

#endif // UNFOLDINGCHECKER_H
