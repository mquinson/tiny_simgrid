#include "Transition_Manager.h"
#include "Actor.h"
#include "Mailbox.h"
#include "Config.hpp"

namespace app {

Transition* Transition_Manager::create_transition(int mailbox_id, int communication_id, TransitionType type)
{
    return new Transition(mailbox_id, communication_id, TransitionTypeName[static_cast<int>(type)]);
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

std::vector<int> Transition_Manager::get_actors_transitions(std::vector<Actor> &actors, std::vector<Mailbox> &mbs) const
{
    std::vector<int> tr_ids;
//    for(auto p : actors) {
//        for (auto j=0; j<(int)p.nb_trans; j++) {
//            if (not p.trans[j].executed) {
//                bool check = true;
//                if (p.trans[j].type == WAIT) {
//                    for (auto mb : mbs) {
//                        if (p.trans[j].mailbox_id == mb.id and (not mb.checkComm(p.trans[j]))) {
//                            check = false;
//                            break;
//                        }
//                    }
//                }
//                if (check)
//                    tr_ids.push_back(p.trans[j].id);
//                break;
//            }
//        }
//    }
    return tr_ids;
}

Transition* Transition_Manager::create_transition(TransitionActivity activity, int access_variable) {
    return new Transition(static_cast<int>(activity), access_variable);
}

} // namespace app

