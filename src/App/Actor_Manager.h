#ifndef ACTOR_MANAGER_H
#define ACTOR_MANAGER_H

#include <vector>
#include "Actor.h"

namespace app {

class Actor_Manager
{
public:
    Actor_Manager();

    template<typename... Ts>
    /*static */Actor* create_actor(int actor_id, Ts&&... ts);

    Actor* create_actor1(int actor_id, Transition&& tr0, Transition&& tr1) {
        std::vector<Transition> ac;
        ac.push_back(tr0);
        ac.push_back(tr1);
        return new Actor(actor_id, ac);
    }

    template<typename... Ts>
    void add_to_actors(Ts&&... ts);

private:
    std::vector<Actor> actors_;

};

} // namespace app

#endif // ACTOR_MANAGER_H
