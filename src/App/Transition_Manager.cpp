#include "Transition_Manager.h"
#include "Actor.h"
#include "Mailbox.h"
#include "Config.hpp"

namespace app {

Transition* Transition_Manager::create_transition(int mailbox_id, int communication_id, short type)
{
    return new Transition(mailbox_id, communication_id, TransitionTypeName[type]);
}

void Transition_Manager::checkpoint(int eid, int n_actors, std::vector<Actor> actors, std::vector<Mailbox> mailboxes)
{
    state_t state = std::make_shared<s_state_t>(s_state_t(n_actors, actors, mailboxes));
    auto node = std::pair<int, state_t>(eid, std::move(state));
    states_.emplace(std::move(node));
}

std::vector<int> Transition_Manager::get_enabled_transition(int eid) const
{
    std::vector<int> tr_ids;
    auto it = states_.find(eid);
    if(it != states_.end()) {
        state_t state = it->second;
        tr_ids = get_actors_transitions(state->actors_, state->mailboxes_);
    }
    return tr_ids;
}

std::vector<int> Transition_Manager::get_actors_transitions(std::vector<Actor> const& actors, std::vector<Mailbox> const& mbs) const
{
    std::vector<int> tr_ids;
    return tr_ids;
}

Transition* Transition_Manager::create_transition(short activity, int access_variable) {
    return new Transition(activity, access_variable);
}

} // namespace app

