#ifndef MAIN_INCLUDE_HPP
#define MAIN_INCLUDE_HPP

#include "App/AppSide.h"

using namespace app;

using AppSide = app::AppSide;
const std::unique_ptr<AppSide> app_side = std::unique_ptr<AppSide>(new AppSide());

const std::string ISEND = "Isend";
const std::string IRECEIVE = "Ireceive";
const std::string TEST = "Test";
const std::string WAIT = "Wait";

// enum class TrType {
//     ISend = 0,
//     IReceive,
//     Test,
//     Wait
// };

void TEST_15() {
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
    std::vector<unsigned int> config {9, 9, 9, 9, 9, 9};
    
}

#endif // MAIN_INCLUDE_HPP
