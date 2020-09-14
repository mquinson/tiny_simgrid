#include "Actor.h"

namespace app
{

    Actor::Actor(int id, std::vector<Transition> trans) : id(id), nb_trans(trans.size())
    {
        for (unsigned int i = 0; i < this->nb_trans; i++)
        {
            this->trans.push_back(trans[i]);
            this->trans[i].id = i;
            this->trans[i].actor_id = id;
            this->trans[i].set_tr_tag(id, i);
        }
    }

    Actor::Actor(int id, unsigned int nb_trans, std::array<Transition, 30> &trans) : id(id), nb_trans(nb_trans)
    {
        for (unsigned int i = 0; i < nb_trans; i++)
        {
            this->trans.push_back(trans[i]);
            this->trans[i].id = i;
            this->trans[i].actor_id = id;
            this->trans[i].set_tr_tag(id, i);
        }
    }

} // namespace app
