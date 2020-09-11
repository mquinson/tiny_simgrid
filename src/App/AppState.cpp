#include "AppState.h"
#include <iostream>
#include <algorithm>

namespace app
{
    bool check_transition_type(Transition const &tr, std::deque<app::Mailbox> const &mbs)
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
        for (auto j = 0; j < p.nb_trans; j++)
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
        
    /* this function execute a transition from a given state, returning a next state*/
    AppState AppState::execute_transition(Transition tr)
    {
        auto mailboxs = this->mailboxes_;
        auto actors = this->actors_;

        // update the status of the actors of the State, set "executed" = true for the executing transition (t)
        auto index = 0;
        for (auto p : actors)
        {
            if (p.id == tr.actor_id)
                actors[index].trans[tr.id].executed = true;
            index++;
        }

        /* if t is send or receive transition, then update the mailbox */
        index = 0;
        if (tr.type == "Isend" || tr.type == "Ireceive")
        {
            for (auto mb : mailboxs)
            {
                if (mb.id == tr.mailbox_id)
                {
                    mailboxs[index].update(tr);
                    break;
                }
                index++;
            }
        }

        return AppState(std::move(actors), std::move(mailboxs));
    }

    std::deque<Transition> AppState::get_enabled_transitions()
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

} // namespace app