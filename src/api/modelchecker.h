#ifndef MODELCHECKER_H
#define MODELCHECKER_H

#include "forward.hpp"

namespace mc {

class ModelChecker
{
public:
    explicit ModelChecker();
    void start();
    void shutdown();

private:
    std::unique_ptr<UnfoldingChecker> unfolding_ckecker_;

};

} // namespace api

#endif // MODELCHECKER_H
