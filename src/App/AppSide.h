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

        /* ACTOR */
        void create_actor(int actor_id, std::vector<S_TRANSITION_PARAMS_2> tr_params);
        void create_actor(int actor_id, std::vector<S_TRANSITION_PARAMS_3> tr_params);

        /* TRANSITION */
        // void checkpoint(int eid, int n_actors, const std::set<Actor> &actors, const std::set<Mailbox> &mailboxes);
        bool is_transition_dependent(int tid0, int tid1) const;
        void execute_transition(int aid, int tid) const;
        std::vector<int> get_enabled_transition(int eid) const;
        std::string get_transition_type(int tid) const;
        int get_transition_actor_id(int tid) const;
        int get_transition_mailbox_id(int tid) const;
        int get_transition_comm_id(int tid) const;

        /* MAILBOX */
        void create_mailbox(std::vector<int> mb_ids);

        /* STATE */
        int create_state(std::deque<Actor>&& actors, std::deque<Mailbox>&& mailboxes); 
        int execute_transition(int state_id, Transition const& tr); 

        /* MAILBOX */
        //    template<typename... Ts>
        //    void add_to_mailbox_list(Ts... ts);
        //    inline std::vector<Mailbox> get_mailbox_list() const { return mailbox_list_; }

    private:
        std::shared_ptr<std::deque<Actor>> actors_;
        std::shared_ptr<std::deque<Mailbox>> mailboxes_;
        std::shared_ptr<StateManager> state_manager_;
    };

} // namespace app

#endif // APPSIDE_H
