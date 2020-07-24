#include "AppSide.h"

namespace app {

void AppSide::initialize()
{
    ac_manager_ = std::unique_ptr<Actor_Manager>(new Actor_Manager());
    tr_manager_ = std::unique_ptr<Transition_Manager>(new Transition_Manager());
}

Transition *AppSide::create_transition(short activity, int access_variable)
{
    return Transition_Manager::create_transition(activity, access_variable);
}

Transition *AppSide::create_transition(int mailbox_id, int communication_id, short type)
{
    return Transition_Manager::create_transition(mailbox_id, communication_id, type);
}

void AppSide::checkpoint(int eid, int n_actors, const std::set<Actor> &actors, const std::set<Mailbox> &mailboxes)
{
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
