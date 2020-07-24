#ifndef ACTOR_MANAGER_H
#define ACTOR_MANAGER_H

#include <vector>
#include "Actor.h"
#include "Config.hpp"

namespace app {

class Actor_Manager
{
public:
    Actor_Manager() = default;

    template<typename... Ts>
    static Actor* create_actor(int actor_id, Ts&&... ts) {
        std::vector<Transition> vec_tr;
        unpack_params(vec_tr, std::forward<Ts>(ts)...);
        return (new Actor(actor_id, vec_tr));
    }

    template<typename... Ts>
    void add_to_actors(Ts&&... ts) {
        std::vector<Actor> vec_ac;
        unpack_params(vec_ac, std::forward<Ts>(ts)...);
        actors_.clear();
        actors_ = std::move(vec_ac);
    }

private:
    std::vector<Actor> actors_;

};

} // namespace app

#endif // ACTOR_MANAGER_H
