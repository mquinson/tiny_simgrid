#include "AppSide.h"
#include "Transition.h"
#include "Actor.h"
#include "Mailbox.h"

namespace app {

const char* ListTypeName[] = {"transition", "actor", "mailbox"};
const char* TransitionTypeName[] = {"Isend", "Ireceive", "Test", "Wait"};

Transition* AppSide::create_transition(int mailbox_id, int communication_id, TransitionType type) const {
    return new Transition(mailbox_id, communication_id, TransitionTypeName[static_cast<int>(type)]);
}

std::vector<Transition> AppSide::get_transition_list() const {
    std::vector<Transition> transition_list;
    for(auto it:actors_list_) {
        transition_list.push_back(it.trans[0]);
    }
    return transition_list;
}

Transition* AppSide::create_transition(TransitionActivity activity, int access_variable) const {
    return new Transition(static_cast<int>(activity), access_variable);
}

template<typename... Ts>
Actor* AppSide::create_actor(int actor_id, Ts&&... ts) {
    std::vector<Transition> vec_tr;
    unpack_params(vec_tr, std::forward<Ts>(ts)...);
    return (new Actor(actor_id, vec_tr));
}

template<typename... Ts>
void AppSide::add_to_actor_list(Ts&&... ts) {
    std::vector<Actor> vec_ac;
    unpack_params(vec_ac, std::forward<Ts>(ts)...);
    actors_list_.clear();
    actors_list_ = std::move(vec_ac);
}

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
