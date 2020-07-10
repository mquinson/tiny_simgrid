#ifndef STATE_H
#define STATE_H

#include <set>
#include "../App/Actor.h"
#include "../App/Mailbox.h"

class State {
public:
    unsigned long nb_actors_ = 0;
    std::set<Actor> actors_;
    std::set<Mailbox> mailboxes_;

    State() = default;
    State(unsigned long nb_actors_, std::set<Actor> actors_, std::set<Mailbox> mailboxes_);
    State(std::set<Actor> actors, std::set<Mailbox> mailboxes) : State(actors.size(), actors, mailboxes) {}

    std::set<Transition> getEnabledTransition();
    State execute(Transition t);

    void print();
};

#endif // STATE_H
