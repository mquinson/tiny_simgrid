#ifndef APPSIDE_H
#define APPSIDE_H

#include <iostream>
#include <vector>

using namespace std;

namespace app {

class Transition;
class Actor;
class Mailbox;

class AppSide {
public:
    enum class TransitionActivity {
        read = 0,
        write,
        mutex_lock,
        mutex_unlock
    };

    enum TransitionType {
        Isend = 0,
        Ireceive,
        test,
        wait
    };

    AppSide() = default;
    AppSide(AppSide const&) = default;
    AppSide& operator=(AppSide const&) = default;
    ~AppSide() = default;

    Transition* create_transition(TransitionActivity activity, int access_variable) const;
    Transition* create_transition(int mailbox_id, int communication_id, TransitionType type) const;

    template<typename... Ts>
    Actor* create_actor(int actor_id, Ts&&... ts);

    template<typename... Ts>
    void add_to_actor_list(Ts&&... ts);

    template<typename... Ts>
    void add_to_mailbox_list(Ts... ts);

    std::vector<Transition> get_transition_list() const;
    inline std::vector<Actor> get_actor_list() const { return actors_list_; }
    inline int get_actor_count() const { return actors_list_.size(); }
    inline std::vector<Mailbox> get_mailbox_list() const { return mailbox_list_; }

private:
    std::vector<Actor> actors_list_;
    std::vector<Mailbox> mailbox_list_;

    template<typename T, typename... Rest>
    void unpack_params(std::vector<T>& vec, T&& t, Rest&&... rest) const;

    template<typename T>
    void unpack_params(std::vector<T>& vec, T&& t) const;
};

} // namespace app

#endif // APPSIDE_H
