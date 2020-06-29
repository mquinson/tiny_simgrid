#include "Checker.h"
#include "../api/Session.h"

namespace tiny_simgrid {
namespace mc {

Checker::Checker(Session& s) {
    session_ = &s;
}

} // namespace mc
} // namespace tiny_simgrid
