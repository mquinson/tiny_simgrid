#ifndef CHECKERSIDE_HPP
#define CHECKERSIDE_HPP

#include <memory>
#include "Session.h"
#include "../unfolding/UnfoldingChecker.h"

namespace tiny_simgrid {
namespace api {

class CheckerSide {
public:
    explicit CheckerSide();
    ~CheckerSide() = default;
    CheckerSide(const CheckerSide&) = delete;
    CheckerSide& operator=(const CheckerSide&) = delete;

//    typedef struct s_mc_params {
//        std::vector<unsigned int> config;
//        unsigned int expected_events  ;
//    } s_mc_params_t;
//    typedef std::unique_ptr<s_mc_params_t> mc_params_t;

//    void set_mc_parameters(mc_params_t mc_params);

    void initialize(AppSide& app, std::vector<unsigned int> configs, unsigned int expected_events) {
        session_ = std::unique_ptr<Session>(new Session(app));
        create_checker(configs, expected_events);
    }

private:
    std::unique_ptr<Session> session_;
    void create_checker(std::vector<unsigned int> configs, unsigned int expected_events) {
        auto checker = new mc::UnfoldingChecker(*session_);
//        session_.get
    }
};


} // namespace mc
} // namespace tiny_simgrid

#endif // CHECKERSIDE_HPP
