#ifndef UNFOLDINGCHECKER_H
#define UNFOLDINGCHECKER_H

#include "list"
#include "Global.hpp"

namespace uc
{

    using Actor = app::Actor;
    using Transition = app::Transition;
    using Mailbox = app::Mailbox;

    class UnfoldingChecker
    {
        unsigned long expandedStatesCount_ = 0;
        // int Mode = 1; // Mode = 1 is a mutexed model
        std::vector<unsigned int> confs_expected_;
        bool confs_check_ = false;
        int error_ = 0;
        unsigned int expected_events_ = 0;

    public:
        UnfoldingChecker() = default;
        UnfoldingChecker(std::vector<unsigned int> confs, unsigned int expected_events) : confs_expected_(confs), confs_check_(true), expected_events_(expected_events) {}
        UnfoldingChecker(const UnfoldingChecker &) = default;
        UnfoldingChecker &operator=(UnfoldingChecker const &) = default;
        UnfoldingChecker(UnfoldingChecker &&) = default;
        ~UnfoldingChecker() = default;

        void explore(State *state); // Start the exploration
        // Recursive function
        void explore(Configuration C, std::list<EventSet> maxEvtHistory, EventSet D, EventSet A, UnfoldingEvent *currentEvt,
                     EventSet prev_enC, std::deque<Actor> proc);

        void explore(std::deque<Actor> actors, std::deque<Mailbox> mailboxes, std::shared_ptr<AppSide> app_side = nullptr);
        void extend(std::deque<Actor> proc, Configuration C, std::list<EventSet> maxEvtHistory, EventSet &ExC, EventSet &enC) const;
        void remove(UnfoldingEvent *e, Configuration C, EventSet D);
        EventSet KpartialAlt(EventSet D, Configuration C) const;

        void genEventFromCandidate(EventSet &result, Transition t, UnfoldingEvent *preEvt, EventSet U1, EventSet Uc);
        EventSet filter(Configuration C, EventSet U);

        int error_count() { return error_; }
    };

} // namespace uc

#endif // UNFOLDINGCHECKER_H
