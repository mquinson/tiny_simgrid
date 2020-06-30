#ifndef SESSION_H
#define SESSION_H

#include <memory>
#include "RemoteSimulation.hpp"
#include "ModelChecker.h"

namespace tiny_simgrid {
namespace api {

class Session
{
public:
    enum class CheckerType {
        Unfolding = 0
    };

    typedef struct s_mc_params {
        std::vector<unsigned int> config;
        unsigned int expected_events;
    } s_mc_params_t;

    typedef std::unique_ptr<s_mc_params_t> mc_params_t;

    explicit Session(const AppSide& app);
    ~Session() = default;
    Session(Session const&) = delete;
    Session& operator=(Session const&) = delete;
    inline void run() const { model_checker_->get_ckecker()->run(); };
    inline int get_error_count() const { return model_checker_->get_error_count(); }

private:
    std::unique_ptr<ModelChecker> model_checker_;
    void create_checker(const Session& s);
};

} // namespace api
} // namespace tiny_simgrid

#endif // SESSION_H
