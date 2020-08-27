#ifndef STATE_H
#define STATE_H

#include <queue>
#include "../App/Actor.h"
#include "../App/Mailbox.h"

namespace uc {

class State {
public:
    unsigned long nb_actors_ = 0;
    std::deque<app::Actor> actors_;
    std::deque<app::Mailbox> mailboxes_;

    State() = default;
    State(unsigned long nb_actors_, std::deque<app::Actor> actors_, std::deque<app::Mailbox> mailboxes_);
    State(std::deque<app::Actor> actors, std::deque<app::Mailbox> mailboxes) : State(actors.size(), actors, mailboxes) {}
    State(const State&) = default;
    State& operator=(State const&) = default;
    State(State&&) noexcept = default;
    ~State() = default;

    std::deque<app::Transition> getEnabledTransition();
    State execute(app::Transition t);

    void print();
};

} // namespace uc

#endif // STATE_H
