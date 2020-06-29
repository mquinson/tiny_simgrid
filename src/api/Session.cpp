#include "Session.h"

namespace tiny_simgrid {
namespace api {

using namespace tiny_simgrid::app;

Session::Session(AppSide app)
{
    auto remote_ = new RemoteSimulation(std::unique_ptr<AppSide>(new AppSide(app)));
    auto model_checker = std::unique_ptr<ModelChecker>(new ModelChecker(std::unique_ptr<RemoteSimulation>(remote_)));
    model_checker_ = std::move(model_checker);
}

} // namespace api
} // namespace tiny_simgrid
