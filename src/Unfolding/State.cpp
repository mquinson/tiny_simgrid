#include "State.h"
#include <iostream>

using namespace app;

namespace uc {

State::State(unsigned long nb_actor, std::set<Actor> actors, std::set<Mailbox> mailboxes)
{
    this->nb_actors_ = nb_actor;
    this->actors_    = actors;
    this->mailboxes_ = mailboxes;
}

/* this function execute a transition from a given state, returning a next state*/
State State::execute(Transition t)
{
    std::set<Actor> actors, actors1;
    std::set<Mailbox> mail_box;

    mail_box = this->mailboxes_;
    actors   = this->actors_;
    actors1  = this->actors_;

    // update the status of the actors of the State, set "executed" = true for the executing transition (t)
    for (auto p : actors)
        if (p.id == t.actor_id) {
            actors1.erase(p);
            p.trans[t.id].executed = true;
            actors1.insert(p);
        }
    /* if t is send or receive transition, then update the mailbox */

    if (t.type == "Isend" || t.type == "Ireceive")
        for (auto mb : mailboxes_)
            if (mb.id == t.mailbox_id) {
                mail_box.erase(mb);
                mb.update(t);
                mail_box.insert(mb);
                break;
            }

//    std::set<Actor> test_ac = actors1;

    return State(this->nb_actors_, actors1, mail_box);
}

std::set<Transition> State::getEnabledTransition()
{

    std::set<Transition> trans_set;

    for (auto p : this->actors_)
        for (unsigned long j = 0; j < p.nb_trans; j++)
            if (!p.trans[j].executed) {
                bool chk = true;
                if (p.trans[j].type == "Wait") {

                    for (auto mb : this->mailboxes_)
                        if (p.trans[j].mailbox_id == mb.id && (!mb.checkComm(p.trans[j])))
                            chk = false;
                }

                if (chk)
                    trans_set.insert(p.trans[j]);

                break;
            }

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
