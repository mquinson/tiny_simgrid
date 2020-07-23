#include "Actor_Manager.h"
#include "Config.hpp"

namespace app {

Actor_Manager::Actor_Manager()
{

}

template<typename... Ts>
Actor* Actor_Manager::create_actor(int actor_id, Ts&&... ts) {
    std::vector<Transition> vec_tr;
    unpack_params(vec_tr, std::forward<Ts>(ts)...);
    return (new Actor(actor_id, vec_tr));
}

template<typename... Ts>
void Actor_Manager::add_to_actors(Ts&&... ts)
{
    std::vector<Actor> vec_ac;
    unpack_params(vec_ac, std::forward<Ts>(ts)...);
    actors_.clear();
    actors_ = std::move(vec_ac);
}

} // namespace app
