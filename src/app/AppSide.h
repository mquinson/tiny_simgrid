#ifndef APPSIDE_HPP
#define APPSIDE_HPP

#include "app_include.hpp"

namespace tiny_simgrid {
namespace app {

class AppSide {
public:
    enum class TransitionActivity {
        read = 0,
        write,
        mutex_lock,
        mutex_unlock
    } ;

    enum TransitionType {
        Isend = 0,
        Ireceive,
        test,
        wait
    };

    AppSide() = default;
    ~AppSide() = default;

    Transition* create_transition(TransitionActivity activity, int access_variable) const;
    Transition* create_transition(int mailbox_id, int communication_id, TransitionType type) const;

    template<typename... Ts>
    Actor* create_actor(int actor_id, Ts&&... ts) {
        std::vector<Transition> vec_tr;
        unpack_params(vec_tr, std::forward<Ts>(ts)...);
        return (new Actor(actor_id, vec_tr));
    }

    template<typename... Ts>
    void add_to_actor_list(Ts&&... ts) {
        std::vector<Actor> vec_ac;
        unpack_params(vec_ac, std::forward<Ts>(ts)...);
        actors_list_.clear();
        actors_list_ = std::move(vec_ac);
    }

    template<typename... Ts>
    void add_to_mailbox_list(Ts... ts) {
        std::vector<int> vec_mb_id;
        unpack_params(vec_mb_id, std::forward<Ts>(ts)...);
        mailbox_list_.clear();
        for(auto i : vec_mb_id)
            mailbox_list_.push_back(std::move(Mailbox(i)));
    }

//    template<typename... Args>
//    void AppSide::add_to_mailbox_list(const Args&... mailbox_ids) {
//        std::vector<int> mailbox_ids_ = { mailbox_ids... };
//        mailbox_list_.clear();
//        for(auto i : mailbox_ids_) {
//            mailbox_list_.push_back(std::move(new Mailbox(i)));
//        }
//    }

    inline std::vector<Actor> get_actor_list() const { return actors_list_; }
    inline std::vector<Mailbox> get_mailbox_list() const { return mailbox_list_; }

private:
    std::vector<Actor> actors_list_;
    std::vector<Mailbox> mailbox_list_;

    template<typename T, typename... Rest>
    void unpack_params(std::vector<T>& vec, T&& t, Rest&&... rest) {
        vec.push_back(t);
        unpack_params(vec, std::forward<Rest>(rest)...);
    }

    template<typename T>
    void unpack_params(std::vector<T>& vec, T&& t) {
        vec.push_back(t);
    }
};

} // namespace app
} // namespace tiny_simgrid

#endif // APPSIDE_HPP
