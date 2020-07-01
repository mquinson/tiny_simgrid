#include "RemoteSimulation.hpp"

namespace tiny_simgrid {
namespace api {

RemoteSimulation::RemoteSimulation(AppSide* app_side) {
    auto app = std::unique_ptr<AppSide>(app_side);
    app_side_ = std::move(app);
}

std::vector<Actor> RemoteSimulation::read_acotr_list() {
    return app_side_->get_actor_list();
}

std::vector<Mailbox> RemoteSimulation::read_mailbox_list() {
    return app_side_->get_mailbox_list();
}


} // namespace mc
} // namespace tiny_simgrid
