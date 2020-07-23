#ifndef APPSIDE_H
#define APPSIDE_H

#include <iostream>
#include <vector>
#include <set>
#include "Transition_Manager.h"

using namespace std;

namespace app {

class Actor;
class Mailbox;

class AppSide {
public:
    AppSide();
    AppSide(const AppSide&) = delete;
    AppSide& operator=(AppSide const&) = delete;
    AppSide(AppSide&&) = default;
    ~AppSide() = default;

    template<typename... Ts>
    Actor* create_actor(int actor_id, Ts&&... ts);

//    template<typename... Ts>
//    void add_to_actor_list(Ts&&... ts);

    Transition* create_transition(TransitionActivity activity, int access_variable);
    Transition* create_transition(int mailbox_id, int communication_id, TransitionType type);

    template<typename... Ts>
    void add_to_mailbox_list(Ts... ts);

    void keep_transition(int eid, int n_actors, const std::set<Actor> &actors, const std::set<Mailbox> &mailboxes);
    bool is_transition_dependent(int tid0, int tid1) const;
    void execute_transition(int tid);
    std::vector<int> get_enabled_transition(int eid) const;
    std::string get_transition_type(int tid) const;
    int get_transition_actor_id(int tid) const;
    int get_transition_mailbox_id(int tid) const;
    int get_transition_comm_id(int tid) const;

//    std::vector<Transition> get_all_transitions() const;
//    inline std::vector<Actor> actors_ready_to_run() const { return actors_ready_; }
//    inline std::vector<Actor> actors_ran() const { return actors_ran_; }
//    inline int get_actors_ready_count() const { return actors_ready_.size(); }
//    inline int get_actors_ran_count() const { return actors_ran_.size(); }
    inline std::vector<Mailbox> get_mailbox_list() const { return mailbox_list_; }

private:
//    std::vector<Actor> actors_ready_;
//    std::vector<Actor> actors_ran_;
    std::vector<Mailbox> mailbox_list_;
    std::unique_ptr<Transition_Manager> tr_manager_;

    template<typename T, typename... Rest>
    void unpack_params(std::vector<T>& vec, T&& t, Rest&&... rest) const;

    template<typename T>
    void unpack_params(std::vector<T>& vec, T&& t) const;
};

} // namespace app

#endif // APPSIDE_H
