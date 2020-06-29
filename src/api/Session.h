#ifndef SESSION_H
#define SESSION_H

#include <memory>
#include "RemoteSimulation.hpp"
#include "ModelChecker.h"
#include "../app/AppSide.h"

//using namespace tiny_simgrid::app;

namespace tiny_simgrid {
namespace api {

class Session
{
public:
//    Session(AppSide app);
    Session() = default;
    ~Session() = default;
//    Session(Session const&) = delete;
//    Session& operator=(Session const&) = delete;

    inline int get_error_count() const { return model_checker_->get_error_count(); };

private:
    std::unique_ptr<ModelChecker> model_checker_;
    inline void create_checker(const Session* s);
};

} // namespace api
} // namespace tiny_simgrid

#endif // SESSION_H
