#ifndef CHECKER_H
#define CHECKER_H

#include <memory>
//#include "../api/Session.h"

namespace tiny_simgrid {
namespace mc {

class Checker
{
public:
//    explicit Checker(tiny_simgrid::api::Session* s) { session_ = std::unique_ptr<tiny_simgrid::api::Session>(s); }
    Checker();
    virtual void run() = 0;
    virtual int get_error_count() = 0;

//    Checker(Checker const&) = delete;
//    Checker& operator=(Checker const&) = delete;
//    virtual ~Checker() = default;

protected:
//    std::unique_ptr<tiny_simgrid::api::Session> session_;

};

} // namespace mc
} // namespace tiny_simgrid

#endif // CHECKER_H
