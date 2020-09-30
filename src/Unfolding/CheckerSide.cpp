#include "CheckerSide.h"

namespace uc 
{
    void CheckerSide::run(std::shared_ptr<AppSide> app_side)
    {
        auto actors = app_side->get_actors();
        auto mbs = app_side->get_mbs();
        uc_->explore(app_side);
    }
} // namespace uc