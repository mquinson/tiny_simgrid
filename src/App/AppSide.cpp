#include "AppSide.h"

namespace app
{
    bool is_dependent(const Transition &tr0, const Transition &tr1)
    {
        // two transitions are in the same actor => dependent (causality dependence)
        if (tr0.actor_id == tr1.actor_id)
            return true;

        if (tr0.type == "Isend")
        {
            if (tr1.type == "Isend" && (tr0.mailbox_id == tr1.mailbox_id))
                return true;
        }

        else if (tr0.type == "Ireceive")
        {
            if (tr1.type == "Ireceive" && (tr0.mailbox_id == tr1.mailbox_id))
                return true;
        }

        else if ((tr0.type == "Lock") && (tr1.type == "Lock") && (tr0.mutexID == tr1.mutexID))
            return true;
        else if (tr0.type == "Unlock")
        {
            if ((tr1.type == "Mwait") || (tr1.type == "Mtest"))
                return true;
        }
        else // for read - write model
        {
            // if at least one write transition  => dependent
            if ((tr0.access_var == tr1.access_var) && ((tr0.read_write == 1) || (tr1.read_write == 1)))
                return true;
        }

        return false;
    }

    AppSide::AppSide() : actors_(std::make_shared<std::deque<Actor>>()),
                         mailboxes_(std::make_shared<std::deque<Mailbox>>()), 
                         state_manager_(std::make_shared<StateManager>()) 
    {        
        
    }
    
    int AppSide::create_state(std::deque<Actor> &&actors, std::deque<Mailbox> &&mailboxes)
    {
        return state_manager_->create_state(std::forward<std::deque<Actor>>(actors), std::forward<std::deque<Mailbox>>(mailboxes));
    }

    int AppSide::execute_transition(int state_id, std::string const &transition_tag) const
    {
        return state_manager_->execute_transition(state_id, transition_tag);
    }

    std::deque<std::string> AppSide::get_all_tr0_tags(int state_id) const
    {
        return state_manager_->get_all_tr0_tags(state_id);
    }

    std::deque<std::string> AppSide::get_enabled_transitions(int sid) const
    {
        return state_manager_->get_enabled_transitions(sid);
    }

    bool AppSide::check_dependency(std::string const& tr_tag0, std::string const& tr_tag1) const
    {
        Transition tr0;
        Transition tr1;
        bool found_tr0 = false;
        bool found_tr1 = false;

        // Since the dependency check uses some attributes of a Transition that are constant
        // over the run of the algorithm, it remains independent of algorithm's state (or event's state)  
        auto actors = actors_.get();
        for(auto p:*actors)
        {
            for(auto t:p.trans)
            {
                auto tag = t.get_tr_tag();
                if(tag == tr_tag0)
                {
                    found_tr0 = true;
                    tr0 = t;
                }
                if(tag == tr_tag1)
                {
                    found_tr1 = true;
                    tr1 = t;
                }
            }
            if (found_tr0 && found_tr1)
                break;
        }

        return is_dependent(tr0, tr1);
    }

    void AppSide::create_actor(int actor_id, std::vector<S_TRANSITION_PARAMS_2> tr_params)
    {
        std::vector<Transition> trans;
        for (auto i : tr_params)
        {
            auto tr = new Transition(i.read_write, i.access_var);            
            trans.push_back(std::move(*tr));
        }
        auto actor = new Actor(actor_id, trans);
        actors_->push_back(std::move(*actor));
    }

    void AppSide::create_actor(int actor_id, std::vector<S_TRANSITION_PARAMS_3> tr_params)
    {
        std::vector<Transition> trans;
        for (auto i : tr_params)
        {
            auto tr = new Transition(i.mailbox_id, i.communication_id, i.type);
            trans.push_back(std::move(*tr));
        }
        auto actor = new Actor(actor_id, trans);
        actors_->push_back(std::move(*actor));
    }

    void AppSide::create_mailbox(std::vector<int> mb_ids)
    {
        for (auto i : mb_ids)
        {
            auto mb = new Mailbox(i);
            mailboxes_->push_back(std::move(*mb));
        }
    }

} // namespace app
