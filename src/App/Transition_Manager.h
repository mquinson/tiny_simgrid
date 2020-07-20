#ifndef TRANSITION_MANAGER_H
#define TRANSITION_MANAGER_H

#include <map>
#include <memory>
#include <vector>
#include "Transition.h"

namespace app {

class Actor;
class Mailbox;

typedef struct s_state {
    int n_actors_ = 0;
    std::vector<Actor> actors_;
    std::vector<Mailbox> mailboxes_;
    s_state(int n_actors, std::vector<Actor> actors, std::vector<Mailbox> mailboxes) :
        n_actors_(n_actors), actors_(std::move(actors)), mailboxes_(std::move(mailboxes)) {
    };
} s_state_t;

typedef std::unique_ptr<s_state_t> state_t;

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

class Transition_Manager
{
public:
    Transition_Manager() = default;
    Transition_Manager(const Transition_Manager&) = default;
    Transition_Manager& operator=(const Transition_Manager&) = default;
    Transition_Manager(Transition_Manager&&) = default;
    ~Transition_Manager() = default;

    static Transition* create_transition(TransitionActivity activity, int access_variable);
    static Transition* create_transition(int mailbox_id, int communication_id, TransitionType type);
    void keep_transition(int eid, int n_actors, std::vector<Actor> actors, std::vector<Mailbox> mailboxes);

private:
    std::map<int, state_t> states_;
};

} // namespace app

#endif // TRANSITION_MANAGER_H
