#include "CheckerSide.hpp"

namespace tiny_simgrid {
namespace api {

void CheckerSide::set_mc_params (AppSide* app, std::vector<unsigned int> configs, unsigned int expected_events) {
    auto remote_ = new RemoteSimulation(app);
    auto model_checker = std::unique_ptr<ModelChecker>(new ModelChecker(std::unique_ptr<RemoteSimulation>(remote_)));
    model_checker_ = std::move(model_checker);

    create_checker(configs, expected_events);
}

void CheckerSide::create_checker(std::vector<unsigned int> configs, unsigned int expected_events) {
    using UnfoldingChecker = tiny_simgrid::mc::UnfoldingChecker;
    auto unfolding = new UnfoldingChecker();
    unfolding->set_uc_params(configs, expected_events);

    model_checker_->set_checker(std::unique_ptr<Checker>(unfolding));
}

void CheckerSide::run() const {
    model_checker_->get_ckecker()->run();
}

int CheckerSide::get_error_count() const {
    return model_checker_->get_error_count();
}

} // namespace api
} // namespace tiny_simgrid
