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

    std::deque<std::string> AppState::get_all_tr0_tags() const
    {
        std::deque<std::string> all_tr0;
        for (auto p:actors_)
        {            
            all_tr0.push_back(p.trans[0].get_tr_tag());
        }
        return all_tr0;
    }

    /* this function execute a transition from a given state, returning a next state*/
    AppState AppState::execute_transition(std::string const& tr_tag)
    {
        auto mailboxs = this->mailboxes_;
        auto actors = this->actors_;

        // update the status of the actors of the State, set "executed" = true for the executing transition (t)
        auto index = 0;
        std::string tr_type {""};
        auto tr_mb_id = -1;
        Transition tr;
        for (auto p:actors)
        {
            auto tr_id = 0;
            auto found = false;
            for(auto t:p.trans)
            {
                if(t.get_tr_tag() == tr_tag)
                {
                    tr = this->actors_[index].trans[tr_id];
                    actors[index].trans[tr_id].executed = true;
                    tr_type = actors[index].trans[tr_id].type;
                    tr_mb_id = actors[index].trans[tr_id].mailbox_id;
                    found = true;
                    break;
                }
                tr_id++;
            }
            if(found)
                break;
            index++;
        }

        /* if t is send or receive transition, then update the mailbox */
        index = 0;
        if (tr_type == "Isend" || tr_type == "Ireceive")
        {
            for (auto mb : mailboxs)
            {
                if (mb.id == tr_mb_id)
                {
                    mailboxs[index].update(tr);
                    break;
                }
                index++;
            }
        }

        return AppState(std::move(actors), std::move(mailboxs));
    }

    std::deque<std::string> AppState::get_enabled_transitions()
    {
        std::deque<Transition> trans_set;
        for (auto p : this->actors_)
            update_transition_set(p, this->mailboxes_, trans_set);

        auto func = [](Transition const &t0, Transition const &t1) {
            return ((t0.id < t1.id) || (t0.actor_id < t1.actor_id));
        };
        std::sort(trans_set.begin(), trans_set.end(), func);

        std::deque<std::string> trans_tags;
        for(auto t:trans_set)
            trans_tags.push_back(t.get_tr_tag());

        return trans_tags;
    }



    // bool Transition::isDependent(const Transition &other) const
    // {
    //     // two transitions are in the same actor => dependent (causality dependence)
    //     if (this->actor_id == other.actor_id)
    //         return true;

    //     if (this->type == "Isend")
    //     {
    //         if (other.type == "Isend" && (this->mailbox_id == other.mailbox_id))
    //             return true;
    //     }

    //     else if (this->type == "Ireceive")
    //     {
    //         if (other.type == "Ireceive" && (this->mailbox_id == other.mailbox_id))
    //             return true;
    //     }

    //     else if (this->type == "Lock" && other.type == "Lock" && this->mutexID == other.mutexID)
    //         return true;
    //     else if (this->type == "Unlock")
    //     {
    //         if (other.type == "Mwait" || other.type == "Mtest")
    //             return true;
    //     }

    //     // for read - write model
    //     else
    //     {

    //         // if at least one write transition  => dependent
    //         if ((this->access_var == other.access_var) && ((this->read_write == 1) || (other.read_write == 1)))
    //             return true;
    //     }

    //     return false;
    // }    

} // namespace app