#ifndef ACTOR_H
#define ACTOR_H

#include <iostream>
#include <array>
#include <vector>
#include "../transition/transition.h"

using namespace std;

class Actor
{
public:
    Actor();
    Actor(int id, unsigned int nb_trans, std::array<Transition, 30>& trans);
    Actor(int id, std::vector<Transition> trans);

    int id {0};
    unsigned long nb_trans {0};
    std::vector<Transition> trans;
    bool operator <(const Actor& other) const { return (this->id < other.id); }
};

#endif // ACTOR_H
