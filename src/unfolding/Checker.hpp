#ifndef CHECKER_H
#define CHECKER_H

namespace tiny_simgrid {
namespace mc {

class Checker
{
public:
    Checker() = default;
    ~Checker() = default;
    virtual void run() = 0;
    virtual int get_error_count() = 0;
};

} // namespace mc
} // namespace tiny_simgrid

#endif // CHECKER_H
