#include "Transition_Manager.h"
#include "Actor.h"
#include "Mailbox.h"

const char* ListTypeName[] = {"transition", "actor", "mailbox"};
const char* TransitionTypeName[] = {"Isend", "Ireceive", "Test", "Wait"};

namespace app {

Transition* Transition_Manager::create_transition(int mailbox_id, int communication_id, TransitionType type) {
    return new Transition(mailbox_id, communication_id, TransitionTypeName[static_cast<int>(type)]);
}

void Transition_Manager::keep_transition(int eid, int n_actors, std::vector<Actor> actors, std::vector<Mailbox> mailboxes)
{
    state_t state = std::unique_ptr<s_state_t>(new s_state_t(n_actors, actors, mailboxes));
    auto node = std::pair<int, state_t>(eid, std::move(state));
    states_.emplace(std::move(node));
}

Transition* Transition_Manager::create_transition(TransitionActivity activity, int access_variable) {
    return new Transition(static_cast<int>(activity), access_variable);
}

} // namespace app

