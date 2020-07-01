#ifndef REMOTESIMULATION_H
#define REMOTESIMULATION_H

#include <memory>
#include <vector>
#include "../App/Actor.h"
#include "../App/Mailbox.h"
#include "../App/AppSide.h"

using namespace tiny_simgrid::app;

namespace tiny_simgrid {
namespace api {

class RemoteSimulation
{
public:
    explicit RemoteSimulation(AppSide* app_side);
    RemoteSimulation(RemoteSimulation const&) = delete;
    RemoteSimulation& operator=(RemoteSimulation const&) = delete;
    ~RemoteSimulation() = default;

    std::vector<Actor> read_acotr_list();
    std::vector<Mailbox> read_mailbox_list();

private:
    std::unique_ptr<AppSide> app_side_;
};

} // namespace mc
} // namespace tiny_simgrid

#endif // REMOTESIMULATION_H
