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
    Actor() {}

    Actor(int id, unsigned int nb_trans, std::array<Transition, 30>& trans);
    Actor(int id, std::vector<Transition> trans);
    bool operator<(const Actor& other) const;
};

} // namespace app

#endif // ACTOR_H
