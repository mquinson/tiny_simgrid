#ifndef MAIN_INCLUDE_HPP
#define MAIN_INCLUDE_HPP

#include "App/AppSide.h"
#include "Unfolding/CheckerSide.h"

const std::string ISEND = "Isend";
const std::string IRECEIVE = "Ireceive";
const std::string TEST = "Test";
const std::string WAIT = "Wait";

using S_TRANSITION_PARAMS_2 = app::S_TRANSITION_PARAMS_2;
using S_TRANSITION_PARAMS_3 = app::S_TRANSITION_PARAMS_3;

using AppSide = app::AppSide;
std::shared_ptr<AppSide> app_side = std::make_shared<AppSide>();

using CheckerSide = uc::CheckerSide;
std::shared_ptr<CheckerSide> checker_side = std::make_shared<CheckerSide>();

void TEST_3()
{
    // the third example - 1 trace
    // Transition(read_write, access_variable)

    std::vector<S_TRANSITION_PARAMS_2> p0 = {{1, 0}}; // P0: write X
    std::vector<S_TRANSITION_PARAMS_2> p1 = {{1, 1}}; // P1: write Y
    std::vector<S_TRANSITION_PARAMS_2> p2 = {{1, 2}}; // P2: write Z

    app_side->create_actor(0, p0);
    app_side->create_actor(1, p1);
    app_side->create_actor(2, p2);

    checker_side->run(app_side);
}

void TEST_8()
{
    // mutex example - 1 traces
    // Transition(read_write, access_variable)

    std::vector<S_TRANSITION_PARAMS_2> p0 = {{2, 0}, {3, 0}};
    std::vector<S_TRANSITION_PARAMS_2> p1 = {{2, 0}, {3, 0}};

    app_side->create_actor(0, p0);
    app_side->create_actor(1, p1);

    checker_side->run(app_side);
}

void TEST_9()
{
    // mutex example - 1 trace
    // Transition(read_write, access_variable)

    std::vector<S_TRANSITION_PARAMS_2> p0 = {{0, 0}, {2, 1}, {3, 1}};
    std::vector<S_TRANSITION_PARAMS_2> p1 = {{2, 1}, {3, 1}};

    app_side->create_actor(0, p0);
    app_side->create_actor(1, p1);

    checker_side->run(app_side);
}

void TEST_11()
{
    // the first simix model -> 2 traces
    // Transition (maiboxid, commid, type)

    std::vector<S_TRANSITION_PARAMS_3> p0 = {{1, 1, ISEND}, {1, 1, WAIT}};
    std::vector<S_TRANSITION_PARAMS_3> p1 = {{1, 1, ISEND}};
    std::vector<S_TRANSITION_PARAMS_3> p2 = {{1, 1, IRECEIVE}};

    app_side->create_actor(0, p0);
    app_side->create_actor(1, p1);
    app_side->create_actor(2, p2);

    app_side->create_mailbox({1});

    checker_side->run(app_side);
}

void TEST_12()
{
    // the 2nd simix model -> 1 trace
    // Transition (maiboxid, commid, type)

    std::vector<S_TRANSITION_PARAMS_3> p0 = {{1, 1, ISEND}, {1, 1, WAIT}};
    std::vector<S_TRANSITION_PARAMS_3> p1 = {{2, 1, ISEND}};
    std::vector<S_TRANSITION_PARAMS_3> p2 = {{1, 1, IRECEIVE}};

    app_side->create_actor(0, p0);
    app_side->create_actor(1, p1);
    app_side->create_actor(2, p2);

    app_side->create_mailbox({1});

    checker_side->run(app_side);
}

void TEST_14()
{
    // the first simix model -> 2 traces

    std::vector<S_TRANSITION_PARAMS_3> p0 = {{1, 1, ISEND}, {1, 1, WAIT}};
    std::vector<S_TRANSITION_PARAMS_3> p1 = {{1, 1, ISEND}, {1, 1, WAIT}};
    std::vector<S_TRANSITION_PARAMS_3> p2 = {{1, 1, IRECEIVE}, {1, 1, WAIT}, {1, 1, IRECEIVE}, {1, 1, WAIT}};

    app_side->create_actor(0, p0);
    app_side->create_actor(1, p1);
    app_side->create_actor(2, p2);

    app_side->create_mailbox({1});

    checker_side->run(app_side);
}

void TEST_15()
{
    // the first simix model -> 6 traces
    // Transition (maiboxid, commid, type)

    std::vector<S_TRANSITION_PARAMS_3> p0 = {{1, 1, ISEND}, {1, 1, WAIT}};
    std::vector<S_TRANSITION_PARAMS_3> p1 = {{1, 1, ISEND}, {1, 1, WAIT}};
    std::vector<S_TRANSITION_PARAMS_3> p2 = {{1, 1, IRECEIVE}, {1, 1, WAIT}, {1, 2, IRECEIVE}, {1, 2, WAIT}};
    std::vector<S_TRANSITION_PARAMS_3> p3 = {{1, 1, ISEND}, {1, 1, WAIT}};

    app_side->create_actor(0, p0);
    app_side->create_actor(1, p1);
    app_side->create_actor(2, p2);
    app_side->create_actor(3, p3);

    app_side->create_mailbox({1});

    checker_side->run(app_side);
}

void TEST_17()
{
    //  3 traces
    // Transition (maiboxid, commid, type)

    std::vector<S_TRANSITION_PARAMS_3> p0 = {{1, 1, ISEND}, {1, 1, TEST}}; 
    std::vector<S_TRANSITION_PARAMS_3> p1 = {{1, 1, ISEND}};
    std::vector<S_TRANSITION_PARAMS_3> p2 = {{1, 1, IRECEIVE}};

    app_side->create_actor(0, p0);
    app_side->create_actor(1, p1);
    app_side->create_actor(2, p2);

    app_side->create_mailbox({1});

    checker_side->run(app_side);
}

void TEST_23()
{ 
    // 18 traces
    // Transition (maiboxid, commid, type)
    
    std::vector<S_TRANSITION_PARAMS_3> p0 = {{1, 1, IRECEIVE}, {1, 1, TEST}};
    std::vector<S_TRANSITION_PARAMS_3> p1 = {{1, 1, ISEND}, {1, 1, TEST}};
    std::vector<S_TRANSITION_PARAMS_3> p2 = {{1, 1, ISEND}, {1, 1, TEST}};
    std::vector<S_TRANSITION_PARAMS_3> p3 = {{1, 1, ISEND}, {1, 1, TEST}};

    app_side->create_actor(0, p0);
    app_side->create_actor(1, p1);
    app_side->create_actor(2, p2);
    app_side->create_actor(3, p3);

    app_side->create_mailbox({1});

    checker_side->run(app_side);
}


#endif // MAIN_INCLUDE_HPP
