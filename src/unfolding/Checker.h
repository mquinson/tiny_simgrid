#ifndef CHECKER_H
#define CHECKER_H


class Checker
{
public:
    Checker();
    virtual void run() = 0;
    virtual int get_error_count() = 0;
};

#endif // CHECKER_H
