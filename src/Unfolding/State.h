#ifndef STATE_H
#define STATE_H

#include <set>
#include "../App/Actor.h"
#include "../App/Mailbox.h"

namespace uc {

class State {
public:
    unsigned long nb_actors_ = 0;
    std::set<app::Actor> actors_;
    std::set<app::Mailbox> mailboxes_;

    State() = default;
    State(unsigned long nb_actors_, std::set<app::Actor> actors_, std::set<app::Mailbox> mailboxes_);
    State(std::set<app::Actor> actors, std::set<app::Mailbox> mailboxes) : State(actors.size(), actors, mailboxes) {}
    State(const State&) = default;
    State& operator=(State const&) = default;
    State(State&&) = default;
    ~State() = default;

    std::set<app::Transition> getEnabledTransition();
    State execute(app::Transition t);

    void print();
};

} // namespace uc

#endif // STATE_H
