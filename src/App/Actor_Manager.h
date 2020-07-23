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
    static Actor* create_actor(int actor_id, Ts&&... ts);

    template<typename... Ts>
    void add_to_actors(Ts&&... ts);

private:
    std::vector<Actor> actors_;

};

} // namespace app

#endif // ACTOR_MANAGER_H
