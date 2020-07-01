#ifndef CHECKERSIDE_HPP
#define CHECKERSIDE_HPP

#include <memory>
#include <vector>
#include "ModelChecker.h"
#include "../unfolding/UnfoldingChecker.h"

namespace tiny_simgrid {
namespace api {

class CheckerSide {
public:
    explicit CheckerSide() = default;
    ~CheckerSide() = default;
    CheckerSide(const CheckerSide&) = delete;
    CheckerSide& operator=(const CheckerSide&) = delete;

    short run() const;
    int get_error_count() const;
    void set_mc_params(AppSide* app, std::vector<unsigned int> configs, unsigned int expected_events);

private:
    std::unique_ptr<ModelChecker> model_checker_;
    void create_checker(std::vector<unsigned int> configs, unsigned int expected_events);
};


} // namespace api
} // namespace tiny_simgrid

#endif // CHECKERSIDE_HPP
