#ifndef TRANSITION_MANAGER_H
#define TRANSITION_MANAGER_H

#include <map>
#include <vector>
#include <memory>
#include "Transition.h"

namespace app {

class Actor;
class Mailbox;
enum class TransitionType;

typedef struct s_state {
    int n_actors_ = 0;
    std::vector<Actor> actors_;
    std::vector<Mailbox> mailboxes_;
    s_state(int n_actors, std::vector<Actor> actors, std::vector<Mailbox> mailboxes) :
        n_actors_(n_actors), actors_(std::move(actors)), mailboxes_(std::move(mailboxes)) {
    };
} s_state_t;
typedef std::shared_ptr<s_state_t> state_t;

class Transition_Manager
{
public:
    Transition_Manager() = default;
    Transition_Manager(const Transition_Manager&) = default;
    Transition_Manager& operator=(const Transition_Manager&) = default;
    Transition_Manager(Transition_Manager&&) = default;
    ~Transition_Manager() = default;

    static Transition* create_transition(short activity, int access_variable);
    static Transition* create_transition(int mailbox_id, int communication_id, short type);
    void checkpoint(int eid, int n_actors, std::vector<Actor> actors, std::vector<Mailbox> mailboxes);
    std::vector<int> get_enabled_transition(int eid) const;

private:
    std::map<int, state_t> states_;
    std::vector<int> get_actors_transitions(std::vector<Actor>& actors, std::vector<Mailbox>& mbs) const;

};

} // namespace app

#endif // TRANSITION_MANAGER_H
