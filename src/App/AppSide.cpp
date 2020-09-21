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

    bool AppSide::check_transition_dependency(std::string const& tr_tag0, std::string const& tr_tag1) const
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
        add_transition(*actor);
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
        add_transition(*actor);
        actors_->push_back(std::move(*actor));
    }

    std::deque<Actor> AppSide::get_actors()
    {
        auto actors = *(actors_.get());
        return actors;
    }

    std::deque<Mailbox> AppSide::get_mbs()
    {
        auto mbs = *(mailboxes_.get());
        return mbs;
    }

    void AppSide::add_transition(Actor const &actor)
    {
        for (auto t : actor.trans)
        {
            S_TRANSITION_ATTRS attr;
            attr.access_var = t.access_var;
            attr.actor_id = t.actor_id;
            attr.comm_id = t.commId;
            attr.id = t.id;
            attr.lock_id = t.lockId;
            attr.mailbox_id = t.mailbox_id;
            attr.mutex_iD = t.mutexID;
            attr.read_write = t.read_write;
            attr.type = t.type;
            transitions_.insert({t.get_tr_tag(), std::move(attr)});
        }
    }

    bool AppSide::check_transition_type(std::string const& tr_tag, std::vector<std::string> const& type_names)
    {
        bool isEqual = false;
        auto type = get_transition_type(tr_tag);
        for (auto t : type_names)
        {
            if(t == type)
            {
                isEqual = true;
                break;
            }
        }
        return isEqual;
    }

    std::string AppSide::get_transition_type(std::string const& tr_tag)
    {
        auto attr = find_transition_attrs(tr_tag);
        if(attr != nullptr)
        {
            return attr->type;
        }
        return "";
    }

    int AppSide::get_transition_mb_id(std::string const& tr_tag)
    {
        auto attr = find_transition_attrs(tr_tag);
        if(attr != nullptr)
        {
            return attr->mailbox_id;
        }
        return -1;
    }

    int AppSide::get_transition_read_write(std::string const& tr_tag)
    {
        auto attr = find_transition_attrs(tr_tag);
        if(attr != nullptr)
        {
            return attr->read_write;
        }
        return -1;
    }

    int AppSide::get_transition_id(std::string const& tr_tag)
    {
        auto attr = find_transition_attrs(tr_tag);
        if(attr != nullptr)
        {
            return attr->id;
        }
        return -1;
    }

    int AppSide::get_transition_actor_id(std::string const& tr_tag)
    {
        auto attr = find_transition_attrs(tr_tag);
        if (attr != nullptr)
        {
            return attr->actor_id;
        }
        return -1;
    }

    int AppSide::get_transition_comm_id(std::string const &tr_tag)
    {
        auto attr = find_transition_attrs(tr_tag);
        if (attr != nullptr)
        {
            return attr->comm_id;
        }
        return -1;
    }

    // returns (type, (actor_id, mb_id, trans_id))
    std::pair<std::string, std::tuple<int, int, int>> AppSide::get_transition_attrs(std::string const& tr_tag)
    {
        std::pair<std::string, std::tuple<int, int, int>> trans_attrs = std::make_pair("", std::make_tuple(-1, -1, -1));
        auto attr = find_transition_attrs(tr_tag);
        if(attr != nullptr)
        {
            auto type = attr->type;
            auto actor_id = attr->actor_id;
            auto mb_id = attr->mailbox_id;
            auto id = attr->id;

            auto t = std::make_tuple(actor_id, mb_id, id);
            return std::make_pair(type, t);
        }
        return trans_attrs;
    }

    S_TRANSITION_ATTRS* AppSide::find_transition_attrs(std::string const& tr_tag)
    {
        auto pos = transitions_.find(tr_tag);
        if (pos == transitions_.end())
            return nullptr;
        return &(pos->second);
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
