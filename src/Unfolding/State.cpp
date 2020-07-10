#include "State.h"
#include <iostream>

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

    if (t.type == "Isend" or t.type == "Ireceive")
        for (auto mb : mailboxes_)
            if (mb.id == t.mailbox_id) {
                mail_box.erase(mb);
                mb.update(t);
                mail_box.insert(mb);
                break;
            }

    return State(this->nb_actors_, actors1, mail_box);
}

std::set<Transition> State::getEnabledTransition()
{

    std::set<Transition> trans_set;

    for (auto p : this->actors_)
        for (unsigned long j = 0; j < p.nb_trans; j++)
            if (not p.trans[j].executed) {
                // std::cout<< "hien thi not executed : \n";
                // std::cout<< "actorid =" << p.id <<" type ="<< p.trans[j].type <<"   :\n";

                // if transition is Wait, check it's communication is ready ?
                bool chk = true;
                if (p.trans[j].type == "Wait") {

                    for (auto mb : this->mailboxes_)
                        if (p.trans[j].mailbox_id == mb.id and (not mb.checkComm(p.trans[j])))
                            chk = false;
                    // else std::cout<<"\n" <<  p.trans[j].type <<" " << p.trans[j].id <<" of P" << p.id <<" not ready :\n" ;
                    //	if(chk and p.trans[j].actor_id == 1) std::cout<<" \n thang wait  " << p.trans[j].id <<" cua "
                    //<<p.trans[j].actor_id <<" co enabled \n";
                }

                if (chk)
                    trans_set.insert(p.trans[j]);

                break;
            }

    /*
          std::cout<<"\n enabled transitions : \n";
           for(auto tr : trans_set)
           std::cout<< "actorid =" << tr.actor_id<<" \n id="<< tr.id <<" mailbox="<<tr.mailbox_id<<" comm= " <<tr.commId
           << " type ="<<tr.type <<"\n";
           std::cout<<" \n het ---\n";
  */

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
