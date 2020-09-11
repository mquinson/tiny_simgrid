#include "AppSide.h"

namespace app
{

    AppSide::AppSide()
    {
        actors_ = std::make_shared<std::deque<Actor>>();
        mailboxes_ = std::make_shared<std::deque<Mailbox>>();
        state_manager_ = std::make_shared<StateManager>();
    }

    // void AppSide::checkpoint(int eid, int n_actors, const std::set<Actor> &actors, const std::set<Mailbox> &mailboxes)
    // {
    //    typedef struct s {
    //        int id;
    //        int id1;
    //        std::unique_ptr<std::vector<int>> idd;
    //    } s_t;

    //    s_t id[20];
    //    for(auto p : actors) {
    //        s_t s;
    //        s.id = p.id;
    //        s.id1 = p.nb_trans;
    //        std::vector<int> *abc = new std::vector<int>();
    //        for(int i=0; i<(int)p.trans.size(); i++) {
    //            abc->push_back(p.trans[i].id);
    //        }
    //        s.idd = std::unique_ptr<std::vector<int>>(abc);
    ////        id.insert(id.end(), std::move(s));
    //        s_t sec = std::move(s);
    //    }

    //    tr_manager_->keep_transition(eid, n_actors, actors, mailboxes);
    // }

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

    /* this function execute a transition from a given state, returning a next state id*/
    // void AppSide::execute_transition(int aid, int tid) const
    // {
    //     std::deque<Actor> actors;
    //     std::deque<Mailbox> mail_box;

    //     mail_box = this->mailboxes_;
    //     actors   = this->actors_;

    //     // update the status of the actors of the State, set "executed" = true for the executing transition (t)
    //     auto index = 0;
    //     for (auto p : actors)
    //     {
    //         if (p.id == t.actor_id)
    //             actors[index].trans[t.id].executed = true;
    //         index++;
    //     }

    //     /* if t is send or receive transition, then update the mailbox */
    //     index = 0;
    //     if (t.type == "Isend" || t.type == "Ireceive")
    //     {
    //         for (auto mb : mail_box)
    //         {
    //             if (mb.id == t.mailbox_id)
    //             {
    //                 mail_box[index].update(t);
    //                 break;
    //             }
    //             index++;
    //         }
    //     }

    //     return State(this->nb_actors_, actors, mail_box);
    // }

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

    //template<typename... Ts>
    //void AppSide::add_to_mailbox_list(Ts... ts) {
    //    std::vector<int> vec_mb_id;
    //    unpack_params(vec_mb_id, std::forward<Ts>(ts)...);
    //    mailbox_list_.clear();
    //    for(auto i : vec_mb_id) {
    //        auto mb = Mailbox(i);
    //        mailbox_list_.push_back(std::move(mb));
    //    }
    //}

} // namespace app
