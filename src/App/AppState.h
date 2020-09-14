#ifndef APPSTATE_H
#define APPSTATE_H

#include <deque>
#include "Actor.h"
#include "Transition.h"
#include "Mailbox.h"

namespace app
{
    class AppState
    {
    public:
        explicit AppState(std::deque<app::Actor>&& actors, std::deque<app::Mailbox>&& mailboxes) : actors_(std::move(actors)), mailboxes_(std::move(mailboxes)) {}
        AppState(const AppState &) = default;
        AppState &operator=(AppState const &) = default;
        AppState(AppState &&) noexcept = default;
        ~AppState() = default;

        std::deque<Transition> get_enabled_transitions();
        AppState execute_transition(std::string const& tr_tag);

    private:
        std::deque<Actor> actors_;
        std::deque<Mailbox> mailboxes_;
    };

} // namespace app

#endif // APPSTATE_H