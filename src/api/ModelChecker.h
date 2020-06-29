#ifndef MODELCHECKER_H
#define MODELCHECKER_H

//#include "forward.h"

#include <memory>
#include <list>
#include "../unfolding/Checker.h"
#include "RemoteSimulation.hpp"
//#include "../api/Session.h"

namespace tiny_simgrid {
namespace api {

class ModelChecker
{
public:
    explicit ModelChecker(std::unique_ptr<RemoteSimulation> remote_simulation) : remote_simulation_(std::move(remote_simulation)) {}
    ModelChecker(ModelChecker const&) = delete;
    ModelChecker& operator=(ModelChecker const&) = delete;
    ~ModelChecker() = default;

    RemoteSimulation& get_remote_simulation() { return *remote_simulation_; }
    inline int get_error_count() const { return checker_->get_error_count(); };

private:
    std::unique_ptr<Checker> checker_;
    std::unique_ptr<RemoteSimulation> remote_simulation_;
//    void create_checker(tiny_simgrid::api::Session* s);
};

} // namespace api
} // namespace tiny_simgrid

#endif // MODELCHECKER_H

