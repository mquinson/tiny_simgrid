#ifndef APPSIDE_H
#define APPSIDE_H

#include <iostream>
#include <vector>
#include <memory>
#include "StateManager.h"

namespace app
{
    typedef struct TRANSITION_PARAMS_2 
    {
        int read_write;
        int access_var;
    } S_TRANSITION_PARAMS_2;

    typedef struct TRANSITION_PARAMS_3 
    {
        int mailbox_id;
        int communication_id;
        const std::string &type;
    } S_TRANSITION_PARAMS_3;

    class AppSide
    {
    public:
        explicit AppSide();
        AppSide(const AppSide &) = delete;
        AppSide &operator=(AppSide const &) = delete;
        AppSide(AppSide &&) = default;
        ~AppSide() = default;

        // TODO: eliminate it
        void initialize(std::deque<Actor> const &actors, std::deque<Mailbox> const &mbs)
        {
            actors_ = std::make_shared<std::deque<Actor>>(actors);
            mailboxes_ = std::make_shared<std::deque<Mailbox>>(mbs);
        }

        /* ACTOR */
        void create_actor(int actor_id, std::vector<S_TRANSITION_PARAMS_2> tr_params);
        void create_actor(int actor_id, std::vector<S_TRANSITION_PARAMS_3> tr_params);

        /* TRANSITION */
        bool check_dependency(std::string const& tr_tag0, std::string const& tr_tag1) const;

        /* MAILBOX */
        void create_mailbox(std::vector<int> mb_ids);

        /* STATE */
        int create_state(std::deque<Actor>&& actors, std::deque<Mailbox>&& mailboxes); 
        int execute_transition(int state_id, std::string const &transition_tag) const;
        std::deque<std::string> get_all_tr0_tags(int state_id) const;
        std::deque<std::string> get_enabled_transitions(int sid) const;

    private:
        std::shared_ptr<std::deque<Actor>> actors_;
        std::shared_ptr<std::deque<Mailbox>> mailboxes_;
        std::shared_ptr<StateManager> state_manager_;
    };

} // namespace app

#endif // APPSIDE_H
