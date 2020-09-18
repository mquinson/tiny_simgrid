#ifndef CHECKERSIDE_H
#define CHECKERSIDE_H

#include "UnfoldingChecker.h"

namespace uc
{
    class CheckerSide
    {
    public:
        explicit CheckerSide() : uc_(std::make_shared<UnfoldingChecker>()) {}
        CheckerSide(const CheckerSide &) = default;
        CheckerSide &operator=(CheckerSide const &) = default;
        CheckerSide(CheckerSide &&) noexcept = default;
        ~CheckerSide() = default;

        void run(std::shared_ptr<AppSide> app_side);

    private:
        std::shared_ptr<UnfoldingChecker> uc_;
    };

} // namespace uc

#endif // CHECKERSIDE_H
