#include "StateManager.h"

namespace app
{
    int StateManager::state_id_ = 0;

    std::deque<std::string> StateManager::get_all_tr0_tags(int sid)
    {
        auto state = find_state(sid);
        return state->get_all_tr0_tags(); 
    }

    int StateManager::create_state(std::deque<Actor> &&actors, std::deque<Mailbox> &&mailboxes)
    {
        auto state = new AppState(std::forward<std::deque<Actor>>(actors),
                                  std::forward<std::deque<Mailbox>>(mailboxes));
        auto id = add_state(std::move(*state));
        return id;
    }

    int StateManager::execute_transition(int sid, std::string const &transition_tag)
    {
        auto state = find_state(sid);
        if (state == nullptr)
            return -1;
        auto next_state = state->execute_transition(transition_tag);
        auto id = add_state(std::move(next_state));
        return id;
    }

    std::deque<std::string> StateManager::get_enabled_transitions(int sid)
    {
        std::deque<std::string> enabled_trans;
        auto state = find_state(sid);
        if(state == nullptr)
            return enabled_trans;
        return state->get_enabled_transitions();
    }

    AppState *StateManager::find_state(int sid)
    {
        auto pos = states_.find(sid);
        if (pos == states_.end())
            return nullptr;
        return &(pos->second);
    }

    int StateManager::add_state(AppState &&state)
    {
        states_.insert({state_id_, state});
        auto id = state_id_++;
        return id;
    }

} // namespace app