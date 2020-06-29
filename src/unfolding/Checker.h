#ifndef CHECKER_H
#define CHECKER_H

#include <memory>

class Session;

namespace tiny_simgrid {
namespace mc {

class Checker
{
public:
    Checker() = default;
    Checker(Session& s);
    ~Checker() = default;
    virtual void run() = 0;
    virtual int get_error_count() = 0;

protected:
    Session& get_session() { return *session_; }

private:
    Session* session_;
};

} // namespace mc
} // namespace tiny_simgrid

#endif // CHECKER_H
