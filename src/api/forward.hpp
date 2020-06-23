#ifndef FORWARD_HPP
#define FORWARD_HPP

#include <memory>
#include <list>

#include "../unfolding/Checker.h"
#include "../unfolding/state.h"
#include "../unfolding/configuration.h"
#include "../unfolding/EventSet.h"
#include "../unfolding/UnfoldingEvent.h"
#include "../app/actor.h"

namespace mc {

typedef struct s_explore_params {
    unsigned long nb_actors;
    std::set<Actor> actors;
    std::set<Mailbox> mailboxes;
} s_explore_params_t;

typedef s_explore_params_t* explore_params_t;

}




#endif // FORWARD_HPP
