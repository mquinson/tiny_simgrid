#include "State.h"
#include <iostream>
#include <algorithm>

using namespace app;

namespace uc {

State::State(unsigned long nb_actor, std::deque<Actor> actors, std::deque<Mailbox> mailboxes)
{
    this->nb_actors_ = nb_actor;
    this->actors_    = actors;
    this->mailboxes_ = mailboxes;
}

/* this function execute a transition from a given state, returning a next state*/
State State::execute(Transition t)
{
    std::deque<Actor> actors/*, actors1*/;
    std::deque<Mailbox> mail_box;

    mail_box = this->mailboxes_;
    actors   = this->actors_;
//    actors1  = this->actors_;

    // update the status of the actors of the State, set "executed" = true for the executing transition (t)

    auto index = 0;
    for (auto p : actors)
    {
        if (p.id == t.actor_id)
            actors[index].trans[t.id].executed = true;
        index++;
    }
    /* if t is send or receive transition, then update the mailbox */

    index = 0;
    if (t.type == "Isend" || t.type == "Ireceive")
    {
        for (auto mb : mail_box)
        {
            if (mb.id == t.mailbox_id)
            {
                mail_box[index].update(t);
                break;
            }
            index++;
        }
    }

//    std::deque<Actor> test_ac = actors;
//    std::deque<Mailbox> test_mb = mail_box;

    return State(this->nb_actors_, actors, mail_box);
}

bool check_transition_type(Transition const& tr, std::deque<app::Mailbox> const &mbs)
{
    bool chk = true;
    if (tr.type == "Wait")
    {
        for (auto mb : mbs)
        {
            if (tr.mailbox_id == mb.id && (!mb.checkComm(tr)))
                chk = false;
        }
    }
    return chk;
}

void update_transition_set(Actor const &p, std::deque<app::Mailbox> const &mbs, std::deque<Transition> &trans_set)
{
    for (auto j=0; j < p.nb_trans; j++)
    {
        if (!p.trans[j].executed)
        {
            auto chk = check_transition_type(p.trans[j], mbs);
            if (chk)
                trans_set.push_back(p.trans[j]);
            break;
        }
    }
}

std::deque<Transition> State::getEnabledTransition()
{
    std::deque<Transition> trans_set;
    for (auto p : this->actors_)
        update_transition_set(p, this->mailboxes_, trans_set);

    auto func = [](Transition const &t0, Transition const &t1) {
        return ((t0.id < t1.id) || (t0.actor_id < t1.actor_id));
    };
    std::sort(trans_set.begin(), trans_set.end(), func);

    return trans_set;
}

void State::print()
{
    std::cout << "s = (";
    for (auto p : this->actors_)
        for (unsigned long j = 0; j < p.nb_trans; j++)
            if (p.trans[j].executed)
                std::cout << "t" << j << "-p" << p.id << " is executed";
    std::cout << ")";
}

} // namespace uc
