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

void TEST_1()
{
    // the first example (in the paper)
    // Transition(read_write, access_variable)

    std::vector<S_TRANSITION_PARAMS_2> p0 = {{1, 0}}; // P0: write x
    std::vector<S_TRANSITION_PARAMS_2> p1 = {{0, 0}}; // P1: read x
    std::vector<S_TRANSITION_PARAMS_2> p2 = {{0, 0}}; // P2: read x

    app_side->create_actor(0, p0);
    app_side->create_actor(1, p1);
    app_side->create_actor(2, p2);

    checker_side->run(app_side);
}

void TEST_2()
{
    // the second example

    std::vector<S_TRANSITION_PARAMS_2> p0 = {{1, 0}};         // P0: write X
    std::vector<S_TRANSITION_PARAMS_2> p1 = {{1, 1}, {1, 0}}; // P1: write Y, P1: write X

    app_side->create_actor(1, p0);
    app_side->create_actor(2, p1);

    checker_side->run(app_side);
}

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

void TEST_4()
{
    // the fourth example - 6 traces
    // Transition(read_write, access_variable)

    std::vector<S_TRANSITION_PARAMS_2> p0 = {{1, 0}}; // P0: write X
    std::vector<S_TRANSITION_PARAMS_2> p1 = {{1, 0}}; // P1: write Y
    std::vector<S_TRANSITION_PARAMS_2> p2 = {{1, 0}}; // P2: write Z

    app_side->create_actor(0, p0);
    app_side->create_actor(1, p1);
    app_side->create_actor(2, p2);

    checker_side->run(app_side);
}

void TEST_5()
{
    // the fifth example - 4 traces

    std::vector<S_TRANSITION_PARAMS_2> p0 = {{1, 0}, {1, 1}}; // P0: write X
    std::vector<S_TRANSITION_PARAMS_2> p1 = {{1, 0}, {1, 1}}; // P1: write Y

    app_side->create_actor(0, p0);
    app_side->create_actor(1, p1);

    checker_side->run(app_side);
}

void TEST_6()
{
    // 6th example - 3 traces
    // Transition(read_write, access_variable)

    std::vector<S_TRANSITION_PARAMS_2> p0 = {{1, 0}, {1, 1}}; // P0: write X
    std::vector<S_TRANSITION_PARAMS_2> p1 = {{1, 1}, {1, 0}}; // P1: write Y

    app_side->create_actor(0, p0);
    app_side->create_actor(1, p1);

    checker_side->run(app_side);
}

void TEST_7()
{
    // 7th example - 4 traces
    // Transition(read_write, access_variable)

    std::vector<S_TRANSITION_PARAMS_2> p0 = {{1, 0}};
    std::vector<S_TRANSITION_PARAMS_2> p1 = {{1, 1}};
    std::vector<S_TRANSITION_PARAMS_2> p2 = {{1, 1}, {1, 0}};

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

void TEST_10()
{
    // 3 traces
    // Transition(read_write, access_variable)

    std::vector<S_TRANSITION_PARAMS_2> p0 = {{1, 0}, {1, 0}};
    std::vector<S_TRANSITION_PARAMS_2> p1 = {{1, 1}, {1, 0}};

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

void TEST_13()
{
    // the first simix model -> 2 traces

    std::vector<S_TRANSITION_PARAMS_3> p0 = {{1, 1, "Isend"}, {1, 1, "Wait"}};
    std::vector<S_TRANSITION_PARAMS_3> p1 = {{1, 1, "Isend"}, {1, 1, "Wait"}};
    std::vector<S_TRANSITION_PARAMS_3> p2 = {{1, 1, "Ireceive"}, {1, 1, "Wait"}};

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

void TEST_16()
{
    std::vector<S_TRANSITION_PARAMS_3> p0 = {{1, 1, "Ireceive"}, {1, 1, "Wait"}, {1, 2, "Ireceive"}, {1, 2, "Wait"}, {1, 3, "Ireceive"}, {1, 3, "Wait"}};
    std::vector<S_TRANSITION_PARAMS_3> p1 = {{1, 1, "Isend"}, {1, 1, "Wait"}};
    std::vector<S_TRANSITION_PARAMS_3> p2 = {{1, 1, "Isend"}, {1, 1, "Wait"}};
    std::vector<S_TRANSITION_PARAMS_3> p3 = {{1, 1, "Isend"}, {1, 1, "Wait"}};

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

void TEST_18()
{
    std::vector<S_TRANSITION_PARAMS_3> p0 = {{1, 1, "Ireceive"}, {1, 1, "Test"}, {1, 2, "Ireceive"}, {1, 2, "Test"}, {1, 3, "Ireceive"}, {1, 3, "Test"}};
    std::vector<S_TRANSITION_PARAMS_3> p1 = {{1, 1, "Isend"}, {1, 1, "Test"}};
    std::vector<S_TRANSITION_PARAMS_3> p2 = {{1, 1, "Isend"}, {1, 1, "Test"}};
    std::vector<S_TRANSITION_PARAMS_3> p3 = {{1, 1, "Isend"}, {1, 1, "Test"}};

    app_side->create_actor(0, p0);
    app_side->create_actor(1, p1);
    app_side->create_actor(2, p2);
    app_side->create_actor(3, p3);

    app_side->create_mailbox({1});

    checker_side->run(app_side);
}

void TEST_19()
{
    std::vector<S_TRANSITION_PARAMS_3> p0 = {{1, 2, "Ireceive"}, {1, 2, "Test"}};
    std::vector<S_TRANSITION_PARAMS_3> p1 = {{1, 1, "Isend"}, {1, 1, "Test"}};
    std::vector<S_TRANSITION_PARAMS_3> p2 = {{1, 1, "Isend"}, {1, 1, "Test"}};

    app_side->create_actor(0, p0);
    app_side->create_actor(1, p1);
    app_side->create_actor(2, p2);

    app_side->create_mailbox({1});

    checker_side->run(app_side);
}

void TEST_20()
{
    std::vector<S_TRANSITION_PARAMS_3> p0 = {{1, 1, "Ireceive"}, {1, 1, "Test"}, {1, 2, "Ireceive"}, {1, 2, "Test"}};
    std::vector<S_TRANSITION_PARAMS_3> p1 = {{1, 1, "Isend"}, {1, 1, "Test"}};
    std::vector<S_TRANSITION_PARAMS_3> p2 = {{1, 1, "Isend"}, {1, 1, "Test"}};

    app_side->create_actor(0, p0);
    app_side->create_actor(1, p1);
    app_side->create_actor(2, p2);

    app_side->create_mailbox({1});

    checker_side->run(app_side);
}

void TEST_21()
{
    std::vector<S_TRANSITION_PARAMS_3> p0 = {{1, 1, "Ireceive"}, {1, 1, "Test"}, {1, 2, "Ireceive"}, {1, 2, "Test"}};
    std::vector<S_TRANSITION_PARAMS_3> p1 = {{1, 1, "Isend"}, {1, 1, "Test"}};
    std::vector<S_TRANSITION_PARAMS_3> p2 = {{1, 1, "Isend"}, {1, 1, "Test"}};
    std::vector<S_TRANSITION_PARAMS_3> p3 = {{1, 1, "Isend"}, {1, 1, "Test"}};

    app_side->create_actor(0, p0);
    app_side->create_actor(1, p1);
    app_side->create_actor(2, p2);
    app_side->create_actor(3, p3);

    app_side->create_mailbox({1});

    checker_side->run(app_side);
}

void TEST_22()
{
    std::vector<S_TRANSITION_PARAMS_3> p0 = {{1, 1, "Ireceive"}, {1, 1, "Test"}, {1, 2, "Ireceive"}, {1, 2, "Test"}, {1, 3, "Ireceive"}, {1, 3, "Test"}, {1, 3, "Ireceive"}, {1, 3, "Test"}};
    std::vector<S_TRANSITION_PARAMS_3> p1 = {{1, 1, "Isend"}, {1, 1, "Test"}};
    std::vector<S_TRANSITION_PARAMS_3> p2 = {{1, 1, "Isend"}, {1, 1, "Test"}};
    std::vector<S_TRANSITION_PARAMS_3> p3 = {{1, 1, "Isend"}, {1, 1, "Test"}};
    std::vector<S_TRANSITION_PARAMS_3> p4 = {{1, 1, "localComp"}, {1, 1, "Isend"}, {1, 1, "Test"}};

    app_side->create_actor(0, p0);
    app_side->create_actor(1, p1);
    app_side->create_actor(2, p2);
    app_side->create_actor(3, p3);
    app_side->create_actor(4, p4);

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

void TEST_24()
{
    // 8 traces
    // transition (maiboxid, commid, type)

    std::vector<S_TRANSITION_PARAMS_3> p0 = {{1, 1, "Ireceive"}};
    std::vector<S_TRANSITION_PARAMS_3> p1 = {{1, 2, "Ireceive"}, {1, 2, "Test"}};
    std::vector<S_TRANSITION_PARAMS_3> p2 = {{1, 3, "Isend"}};
    std::vector<S_TRANSITION_PARAMS_3> p3 = {{1, 4, "localComp"}, {1, 4, "Isend"}};

    app_side->create_actor(0, p0);
    app_side->create_actor(1, p1);
    app_side->create_actor(2, p2);
    app_side->create_actor(3, p3);

    app_side->create_mailbox({1});

    checker_side->run(app_side);
}

void TEST_25()
{
    // master- slaver 4 nodes
    // master node

    std::vector<S_TRANSITION_PARAMS_3> p0 = {{2, 1, "Isend"}, {3, 2, "Isend"}, {4, 3, "Isend"}, {2, 1, "Wait"}, {3, 2, "Wait"}, {4, 3, "Wait"}, {1, 4, "Ireceive"}, {1, 4, "Wait"}, {1, 5, "Ireceive"}, {1, 5, "Wait"}, {1, 6, "Ireceive"}, {1, 6, "Wait"}};
    std::vector<S_TRANSITION_PARAMS_3> p1 = {{2, 1, "Ireceive"}, {2, 1, "Wait"}, {0, 0, "localComp"}, {1, 2, "Isend"}, {1, 2, "Wait"}};
    std::vector<S_TRANSITION_PARAMS_3> p2 = {{3, 1, "Ireceive"}, {3, 1, "Wait"}, {0, 0, "localComp"}, {1, 2, "Isend"}, {1, 2, "Wait"}};
    std::vector<S_TRANSITION_PARAMS_3> p3 = {{4, 1, "Ireceive"}, {4, 1, "Wait"}, {0, 0, "localComp"}, {1, 2, "Isend"}, {1, 2, "Wait"}};

    app_side->create_actor(0, p0);
    app_side->create_actor(1, p1);
    app_side->create_actor(2, p2);
    app_side->create_actor(3, p3);

    app_side->create_mailbox({1, 2, 3, 4});

    checker_side->run(app_side);
}

void TEST_26()
{
    // master- slaver 3 nodes
    // master node
    // Transition (maiboxid, commid, type)

    std::vector<S_TRANSITION_PARAMS_3> p0 = {{2, 1, "Isend"}, {3, 2, "Isend"}, {2, 1, "Wait"}, {3, 2, "Wait"}, {1, 3, "Ireceive"}, {1, 3, "Wait"}, {1, 4, "Ireceive"}, {1, 4, "Wait"}};
    std::vector<S_TRANSITION_PARAMS_3> p1 = {{2, 1, "Ireceive"}, {2, 1, "Wait"}, {0, 0, "localComp"}, {1, 2, "Isend"}, {1, 2, "Wait"}};
    std::vector<S_TRANSITION_PARAMS_3> p2 = {{3, 1, "Ireceive"}, {3, 1, "Wait"}, {0, 0, "localComp"}, {1, 2, "Isend"}, {1, 2, "Wait"}};

    app_side->create_actor(0, p0);
    app_side->create_actor(1, p1);
    app_side->create_actor(2, p2);

    app_side->create_mailbox({1, 2, 3});

    checker_side->run(app_side);
}

void TEST_28()
{
    // dtg benchmark
    // Transition (maiboxid, commid, type)

    std::vector<S_TRANSITION_PARAMS_3> p0 = {{1, 1, "Ireceive"}, {1, 1, "Wait"}, {5, 2, "Isend"}, {5, 2, "Wait"}, {1, 3, "Ireceive"}, {1, 3, "Wait"}};
    std::vector<S_TRANSITION_PARAMS_3> p1 = {{1, 1, "Isend"}, {1, 1, "Wait"}, {4, 2, "Isend"}, {4, 2, "Wait"}};
    std::vector<S_TRANSITION_PARAMS_3> p2 = {{3, 1, "Ireceive"}, {3, 1, "Wait"}, {1, 2, "Isend"}, {1, 2, "Wait"}};
    std::vector<S_TRANSITION_PARAMS_3> p3 = {{4, 1, "Ireceive"}, {4, 1, "Wait"}, {5, 2, "Ireceive"}, {5, 2, "Wait"}};
    std::vector<S_TRANSITION_PARAMS_3> p4 = {{3, 1, "Isend"}, {3, 1, "Wait"}};

    app_side->create_actor(0, p0);
    app_side->create_actor(1, p1);
    app_side->create_actor(2, p2);
    app_side->create_actor(3, p3);
    app_side->create_actor(4, p4);

    app_side->create_mailbox({1, 2, 3, 4, 5});

    checker_side->run(app_side);
}

void TEST_29()
{
    std::vector<S_TRANSITION_PARAMS_3> p0 = {{2, 1, "Isend"}, {2, 1, "Wait"}, {0, 2, "Ireceive"}, {0, 2, "Wait"}, {1, 3, "Isend"}, {1, 3, "Wait"}};
    std::vector<S_TRANSITION_PARAMS_3> p1 = {{1, 1, "Ireceive"}, {1, 1, "Wait"}, {0, 2, "Isend"}, {0, 2, "Wait"}};
    std::vector<S_TRANSITION_PARAMS_3> p2 = {{2, 1, "Ireceive"}, {2, 1, "Wait"}};

    app_side->create_actor(0, p0);
    app_side->create_actor(1, p1);
    app_side->create_actor(2, p2);

    app_side->create_mailbox({0, 1, 2});

    checker_side->run(app_side);
}

void TEST_30()
{
    std::vector<S_TRANSITION_PARAMS_3> p0 = {{0, 1, "Ireceive"}, {0, 1, "Wait"}, {1, 2, "Isend"}, {1, 2, "Wait"}};
    std::vector<S_TRANSITION_PARAMS_3> p1 = {{1, 1, "Ireceive"}, {1, 1, "Wait"}, {0, 2, "Isend"}, {0, 2, "Wait"}};

    app_side->create_actor(0, p0);
    app_side->create_actor(1, p1);

    app_side->create_mailbox({0, 1});

    checker_side->run(app_side);
}

void TEST_31()
{
    std::vector<S_TRANSITION_PARAMS_3> p0 = {{0, 1, "Ireceive"}, {0, 2, "Ireceive"}, {0, 1, "Wait"}, {0, 2, "Wait"}, {1, 3, "Isend"}, {1, 3, "Wait"}};
    std::vector<S_TRANSITION_PARAMS_3> p1 = {{0, 1, "Isend"}, {2, 2, "Isend"}, {0, 1, "Wait"}, {2, 2, "Wait"}, {1, 3, "Ireceive"}, {1, 3, "Wait"}, {0, 4, "Isend"}, {0, 4, "Wait"}};
    std::vector<S_TRANSITION_PARAMS_3> p2 = {{2, 1, "Ireceive"}, {2, 1, "Wait"}};

    app_side->create_actor(0, p0);
    app_side->create_actor(1, p1);
    app_side->create_actor(2, p2);

    app_side->create_mailbox({0, 1, 2});

    checker_side->run(app_side);
}

void TEST_32()
{
    std::vector<S_TRANSITION_PARAMS_3> p0 = {{0, 1, "Ireceive"}, {1, 2, "Isend"}, {1, 2, "Wait"}, {0, 1, "Wait"}};
    std::vector<S_TRANSITION_PARAMS_3> p1 = {{1, 1, "Ireceive"}, {1, 1, "Wait"}, {0, 2, "Isend"}, {0, 2, "Wait"}};

    app_side->create_actor(0, p0);
    app_side->create_actor(1, p1);

    app_side->create_mailbox({0, 1});

    checker_side->run(app_side);
}

void TEST_33()
{
    std::vector<S_TRANSITION_PARAMS_3> p0 = {{0, 1, "Ireceive"}, {0, 1, "Wait"}, {1, 2, "Isend"}, {1, 2, "Wait"}, {0, 3, "Ireceive"}, {0, 3, "Wait"}};
    std::vector<S_TRANSITION_PARAMS_3> p1 = {{0, 1, "Isend"}, {0, 1, "Wait"}, {1, 2, "Ireceive"}, {1, 2, "Wait"}};
    std::vector<S_TRANSITION_PARAMS_3> p2 = {{0, 0, "Isend"}, {0, 0, "Wait"}};

    app_side->create_actor(0, p0);
    app_side->create_actor(1, p1);
    app_side->create_actor(2, p2);

    app_side->create_mailbox({0, 1, 2});

    checker_side->run(app_side);
}

// forte paper
void TEST_34()
{
    std::vector<S_TRANSITION_PARAMS_3> p0 = {{0, 1, "Ireceive"}, {0, 2, "Ireceive"}, {0, 2, "Test"}};
    std::vector<S_TRANSITION_PARAMS_3> p1 = {{0, 1, "Isend"}};
    std::vector<S_TRANSITION_PARAMS_3> p2 = {{0, 0, "localComp"}, {0, 1, "Isend"}};

    app_side->create_actor(0, p0);
    app_side->create_actor(1, p1);
    app_side->create_actor(2, p2);

    app_side->create_mailbox({0});

    checker_side->run(app_side);
}

std::pair<double, double> run_test(int test_number)
{
    clock_t begin = clock();
    switch (test_number)
    {
    case 1:
        TEST_1();
        break;

    case 2:
        TEST_2();
        break;

    case 3:
        TEST_3();
        break;

    case 4:
        TEST_4();
        break;

    case 5:
        TEST_5();
        break;

    case 6:
        TEST_6();
        break;

    case 7:
        TEST_7();
        break;

    case 8:
        TEST_8();
        break;

    case 9:
        TEST_9();
        break;

    case 10:
        TEST_10();
        break;

    case 11:
        TEST_11();
        break;

    case 12:
        TEST_12();
        break;

    case 13:
        TEST_13();
        break;

    case 14:
        TEST_14();
        break;

    case 15:
        TEST_15();
        break;

    case 16:
        TEST_16();
        break;

    case 17:
        TEST_17();
        break;

    case 18:
        TEST_18();
        break;

    case 19:
        TEST_19();
        break;

    case 20:
        TEST_20();
        break;

    case 21:
        TEST_21();
        break;

    case 22:
        TEST_22();
        break;

    case 23:
        TEST_23();
        break;

    case 24:
        TEST_24();
        break;

    case 25:
        TEST_25();
        break;

    case 26:
        TEST_26();
        break;

    case 28:
        TEST_28();
        break;

    case 29:
        TEST_29();
        break;

    case 30:
        TEST_30();
        break;

    case 31:
        TEST_31();
        break;

    case 32:
        TEST_32();
        break;

    case 33:
        TEST_33();
        break;

    case 34:
        TEST_34();
        break;

    default:
        break;
    }
    clock_t end = clock();    
    double elapsed_min  = double(end - begin) / (60 * CLOCKS_PER_SEC);
    double elapsed_secs = double(end - begin) / (CLOCKS_PER_SEC);
    return std::make_pair(elapsed_secs, elapsed_min);
}

#endif // MAIN_INCLUDE_HPP
