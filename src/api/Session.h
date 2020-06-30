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
    explicit Session(const AppSide& app);
    ~Session() = default;
    Session(Session const&) = delete;
    Session& operator=(Session const&) = delete;
    inline void run() const { model_checker_->get_ckecker()->run(); };
    inline int get_error_count() const { return model_checker_->get_error_count(); };

private:
    std::unique_ptr<ModelChecker> model_checker_;
    void create_checker(const Session& s);
};

} // namespace api
} // namespace tiny_simgrid

#endif // SESSION_H
