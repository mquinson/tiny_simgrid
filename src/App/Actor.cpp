#include "Actor.h"

Actor::Actor(int id, std::vector<Transition> trans)
{
    this->id       = id;
    this->nb_trans = trans.size();

    for (unsigned int i = 0; i < this->nb_trans; i++) {
        this->trans.push_back(trans[i]);
        this->trans[i].id       = i;
        this->trans[i].actor_id = id;
    }
}

Actor::Actor(int id, unsigned int nb_trans, std::array<Transition, 30>& trans)
{
    this->id       = id;
    this->nb_trans = nb_trans;

    for (unsigned int i = 0; i < nb_trans; i++) {
        this->trans.push_back(trans[i]);
        this->trans[i].id       = i;
        this->trans[i].actor_id = id;
    }
}

bool Actor::operator<(const Actor& other) const
{
    return (this->id < other.id);
}
