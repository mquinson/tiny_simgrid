#ifndef APPSIDE_H
#define APPSIDE_H

#include <iostream>
#include <vector>
#include <set>
#include "Actor_Manager.h"
#include "Transition_Manager.h"
#include "Mailbox.h"

using namespace std;

namespace app {

class AppSide {
public:
    AppSide() = default;
    AppSide(const AppSide&) = delete;
    AppSide& operator=(AppSide const&) = delete;
    AppSide(AppSide&&) = default;
    ~AppSide() = default;
    void initialize();

    /* ACTOR */    
    template<typename... Ts>
    Actor* create_actor(int actor_id, Ts&&... ts) {
        return Actor_Manager::create_actor(actor_id, std::forward<Ts>(ts)...);
    };

    template<typename... Ts>
    void add_to_actors(Ts&&... ts) {
        ac_manager_->add_to_actors(std::forward<Ts>(ts)...);
    }

    /* TRANSITION */
    Transition* create_transition(short activity, int access_variable);
    Transition* create_transition(int mailbox_id, int communication_id, short type);
    void checkpoint(int eid, int n_actors, const std::set<Actor> &actors, const std::set<Mailbox> &mailboxes);
    bool is_transition_dependent(int tid0, int tid1) const;
    void execute_transition(int tid);
    std::vector<int> get_enabled_transition(int eid) const;
    std::string get_transition_type(int tid) const;
    int get_transition_actor_id(int tid) const;
    int get_transition_mailbox_id(int tid) const;
    int get_transition_comm_id(int tid) const;

    /* MAILBOX */
//    template<typename... Ts>
//    void add_to_mailbox_list(Ts... ts);
//    inline std::vector<Mailbox> get_mailbox_list() const { return mailbox_list_; }

private:
//    std::vector<Mailbox> mailbox_list_;
    std::unique_ptr<Actor_Manager> ac_manager_;
    std::unique_ptr<Transition_Manager> tr_manager_;
};

} // namespace app

#endif // APPSIDE_H
