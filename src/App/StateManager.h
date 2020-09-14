#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <map>
#include "AppState.h"

namespace app
{
    class StateManager
    {
    public:
        explicit StateManager() = default;
        StateManager(const StateManager &) = delete;
        StateManager &operator=(StateManager const &) = delete;
        StateManager(StateManager &&) = delete;
        ~StateManager() = default;

        int create_state(std::deque<Actor>&& actors, std::deque<Mailbox>&& mailboxes); 
        int execute_transition(int state_id, Transition const& tr); 

    private:
        AppState* find_state(int state_id);
        int add_state(AppState&& state);
        static int state_id_;
        std::map<int, AppState> states_;
    };

} // namespace app

#endif // STATEMANAGER_H