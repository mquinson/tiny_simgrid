#include "AppSide.h"
//#include <algorithm>
#include <array>
#include "Actor.h"
#include "Mailbox.h"

namespace app {

AppSide::AppSide()
{
    tr_manager_ = std::unique_ptr<Transition_Manager>(new Transition_Manager());
}

Transition *AppSide::create_transition(TransitionActivity activity, int access_variable)
{
    return Transition_Manager::create_transition(activity, access_variable);
}

Transition *AppSide::create_transition(int mailbox_id, int communication_id, TransitionType type)
{
    return Transition_Manager::create_transition(mailbox_id, communication_id, type);
}

void AppSide::keep_transition(int eid, int n_actors, const std::set<Actor> &actors, const std::set<Mailbox> &mailboxes)
{
    typedef struct s {
        int id;
        int id1;
        std::unique_ptr<std::vector<int>> idd;
    } s_t;

    s_t id[20];
    for(auto p : actors) {
        s_t s;
        s.id = p.id;
        s.id1 = p.nb_trans;
        std::vector<int> *abc = new std::vector<int>();
        for(int i=0; i<(int)p.trans.size(); i++) {
            abc->push_back(p.trans[i].id);
        }
        s.idd = std::unique_ptr<std::vector<int>>(abc);
//        id.insert(id.end(), std::move(s));
        s_t sec = std::move(s);
    }

//    tr_manager_->keep_transition(eid, n_actors, actors, mailboxes);
}

bool AppSide::is_transition_dependent(int tid0, int tid1) const
{
    return false;
}

void AppSide::execute_transition(int tid)
{

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
    return tr_manager_->get_enabled_transition(eid);
}

string AppSide::get_transition_type(int tid) const
{
    return "";
}

/* this function execute a transition from a given state */
//std::vector<Actor> AppSide::execute(const Transition& tr)
//{
//    std::vector<Actor> updated_actors;
//    auto run_actor = [&](Actor& p) {
//        if(p.id == tr.id) {
//            this->actors_list_.erase();


//            p.trans[tr.id].executed = true;
////            updated_actors.push_back()
//        }
//    };

//    std::for_each();
//    return updated_actors;


//    {
//        std::set<Actor> actors, actors1;
//        std::set<Mailbox> mail_box;

//        mail_box = this->mailboxes_;
//        actors   = this->actors_;
//        actors1  = this->actors_;

//        // update the status of the actors of the State, set "executed" = true for the executing transition (t)
//        for (auto p : actors)
//            if (p.id == t.actor_id) {
//                actors1.erase(p);
//                p.trans[t.id].executed = true;
//                actors1.insert(p);
//            }
//        /* if t is send or receive transition, then update the mailbox */

//        if (t.type == "Isend" or t.type == "Ireceive")
//            for (auto mb : mailboxes_)
//                if (mb.id == t.mailbox_id) {
//                    mail_box.erase(mb);
//                    mb.update(t);
//                    mail_box.insert(mb);
//                    break;
//                }

//        return State(this->nb_actors_, actors1, mail_box);
//    }





//}

//std::vector<Transition> AppSide::get_all_transitions() const {
//    std::vector<Transition> transition_list;
//    for(auto it:actors_ready_) {
//        transition_list.push_back(it.trans[0]);
//    }
//    return transition_list;
//}

template<typename... Ts>
Actor* AppSide::create_actor(int actor_id, Ts&&... ts) {
    std::vector<Transition> vec_tr;
    unpack_params(vec_tr, std::forward<Ts>(ts)...);
    return (new Actor(actor_id, vec_tr));
}

//template<typename... Ts>
//void AppSide::add_to_actor_list(Ts&&... ts) {
//    std::vector<Actor> vec_ac;
//    unpack_params(vec_ac, std::forward<Ts>(ts)...);
//    actors_ready_.clear();
//    actors_ready_ = std::move(vec_ac);
//}

template<typename... Ts>
void AppSide::add_to_mailbox_list(Ts... ts) {
    std::vector<int> vec_mb_id;
    unpack_params(vec_mb_id, std::forward<Ts>(ts)...);
    mailbox_list_.clear();
    for(auto i : vec_mb_id) {
        auto mb = Mailbox(i);
        mailbox_list_.push_back(std::move(mb));
    }
}

template<typename T, typename... Rest>
void AppSide::unpack_params(std::vector<T>& vec, T&& t, Rest&&... rest) const {
    vec.push_back(std::forward<T>(t));
    unpack_params(vec, std::forward<Rest>(rest)...);
}

template<typename T>
void AppSide::unpack_params(std::vector<T>& vec, T&& t) const {
    vec.push_back(std::forward<T>(t));
}


} // namespace app
