#include "AppSide.h"

namespace app
{

    AppSide::AppSide()
    {
        actors_ = std::make_shared<std::deque<Actor>>();
        mailboxes_ = std::make_shared<std::deque<Mailbox>>();
        state_manager_ = std::make_shared<StateManager>();
    }

    int AppSide::create_state(std::deque<Actor> &&actors, std::deque<Mailbox> &&mailboxes)
    {
        return state_manager_->create_state(std::forward<std::deque<Actor>>(actors), std::forward<std::deque<Mailbox>>(mailboxes));
    }

    int AppSide::execute_transition(int state_id, std::string const &transition_tag)
    {
        return state_manager_->execute_transition(state_id, transition_tag);
    }

    bool AppSide::is_transition_dependent(int tid0, int tid1) const
    {
        return false;
    }

    void AppSide::create_actor(int actor_id, std::vector<S_TRANSITION_PARAMS_2> tr_params) 
    {
        std::vector<Transition> trans;
        for(auto i:tr_params)
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
        for(auto i:tr_params)
        {
            auto tr = new Transition(i.mailbox_id, i.communication_id, i.type);
            trans.push_back(std::move(*tr));
        }
        auto actor = new Actor(actor_id, trans);
        actors_->push_back(std::move(*actor));
    }

    void AppSide::create_mailbox(std::vector<int> mb_ids)
    {
        for (auto i:mb_ids)
        {
            auto mb = new Mailbox(i);
            mailboxes_->push_back(std::move(*mb));
        }
    }

    int AppSide::get_transition_actor_id(int tid) const
    {
        return -1;
    }

    int AppSide::get_transition_mailbox_id(int tid) const
    {
        return -1;
    }

    int AppSide::get_transition_comm_id(int tid) const
    {
        return -1;
    }

    std::vector<int> AppSide::get_enabled_transition(int eid) const
    {
        std::vector<int> ret;
        return ret;
    }

    std::string AppSide::get_transition_type(int tid) const
    {
        return "";
    }

} // namespace app
