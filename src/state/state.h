#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <set>
#include "../actor/actor.h"
#include "../mailbox/mailbox.h"

using namespace std;

class State
{
public:
    unsigned long nb_actors_ {0};
    std::set<Actor> actors_;
    std::set<Mailbox> mailboxes_;

    State() = default;
    State(unsigned long nb_actors, std::set<Actor> actors, std::set<Mailbox> mailboxes) : nb_actors_(nb_actors), actors_(actors), mailboxes_(mailboxes) {}
    State(std::set<Actor> actors, std::set<Mailbox> mailboxes) : State(actors.size(), actors, mailboxes) {}

    std::set<Transition> getEnabledTransition();
    State execute(Transition t);

    void print();
};

#endif // STATE_H
