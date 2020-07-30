#ifndef ACTOR_H
#define ACTOR_H

#include <array>
#include <vector>
#include "Transition.h"

namespace app {

class Actor
{
public:
    int id                 = 0;
    unsigned long nb_trans = 0;
    std::vector<Transition> trans;
    Actor(int id, unsigned int nb_trans, std::array<Transition, 30>& trans);
    Actor(int id, std::vector<Transition> trans);
    Actor(const Actor&) = default;
    Actor& operator=(Actor const&) = default;
    Actor(Actor&&) = default;
    ~Actor() = default;

    inline bool operator<(const Actor& other) const { return (this->id < other.id); }
};

} // namespace app

#endif // ACTOR_H
