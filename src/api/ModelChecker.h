#ifndef MODELCHECKER_H
#define MODELCHECKER_H

#include <memory>
#include <list>
#include "../unfolding/Checker.hpp"
#include "RemoteSimulation.hpp"

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
    inline void set_checker(std::unique_ptr<Checker> mc) { checker_ = std::move(mc); }
    inline Checker* get_ckecker() const { return checker_.get(); };

private:
    std::unique_ptr<Checker> checker_;
    std::unique_ptr<RemoteSimulation> remote_simulation_;
};

} // namespace api
} // namespace tiny_simgrid

#endif // MODELCHECKER_H

