#include "Session.h"
#include "../unfolding/UnfoldingChecker.h"

namespace tiny_simgrid {
namespace api {

Session::Session(AppSide& app)
{
    auto remote_ = new RemoteSimulation(std::unique_ptr<AppSide>(new AppSide(app)));
    auto model_checker = std::unique_ptr<ModelChecker>(new ModelChecker(std::unique_ptr<RemoteSimulation>(remote_)));
    model_checker_ = std::move(model_checker);
//    create_checker(*this);
}

//void Session::create_checker(mc_params_t checker_params) {
//    if(checker_params->checker_type == CheckerType::Unfolding) {

//        auto unfolding_ckecker = new UnfoldingChecker(*this);
//        model_checker_->set_checker(std::unique_ptr<Checker>());
//    }
//}

//const std::vector<unsigned int>& config, int expected_events
//void Session::create_checker(const Session& s) {
//    model_checker_->set_checker(std::unique_ptr<Checker>(new UnfoldingChecker()));
//}

} // namespace api
} // namespace tiny_simgrid
