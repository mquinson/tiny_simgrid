#ifndef REMOTESIMULATION_H
#define REMOTESIMULATION_H

#include "../app/actor.h"
#include "../app/AppSide.h"
//#include "../app/"

//using namespace std;

namespace tiny_simgrid {
namespace api {

class RemoteSimulation
{
public:
    explicit RemoteSimulation(std::unique_ptr<tiny_simgrid::app::AppSide> remote) : remote_(std::move(remote)) {}

    RemoteSimulation(RemoteSimulation const&) = delete;
    RemoteSimulation& operator=(RemoteSimulation const&) = delete;
    ~RemoteSimulation() = default;

    inline std::vector<Actor> read_acotr_list() const { return remote_->get_actor_list(); }
    inline std::vector<Mailbox> read_mailbox_list() const { return remote_->get_mailbox_list(); }

private:
    std::unique_ptr<AppSide> remote_;
};

} // namespace mc
} // namespace tiny_simgrid

#endif // REMOTESIMULATION_H
