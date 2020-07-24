#ifndef MAIN_INCLUDE_HPP
#define MAIN_INCLUDE_HPP

#include "App/AppSide.h"
//#include "App/Actor.h"

using namespace app;

using AppSide = app::AppSide;
std::unique_ptr<AppSide> app_side = std::unique_ptr<AppSide>(new AppSide());

enum class TrType {
    ISend = 0,
    IReceive,
    Test,
    Wait
};

void TEST_15() {
    // the first simix model -> 6 traces
    // Transition (maiboxid, commid, type)

    app_side->initialize();

    // p0
    auto tr0_0 = app_side->create_transition(1, 1, static_cast<short>(TrType::ISend));
    auto tr0_1 = app_side->create_transition(1, 1, static_cast<short>(TrType::Wait));
    // p1
    auto tr1_0 = app_side->create_transition(1, 1, static_cast<short>(TrType::ISend));
    auto tr1_1 = app_side->create_transition(1, 1, static_cast<short>(TrType::Wait));
    // p2
    auto tr2_0 = app_side->create_transition(1, 1, static_cast<short>(TrType::IReceive));
    auto tr2_1 = app_side->create_transition(1, 1, static_cast<short>(TrType::Wait));
    auto tr2_2 = app_side->create_transition(1, 2, static_cast<short>(TrType::IReceive));
    auto tr2_3 = app_side->create_transition(1, 2, static_cast<short>(TrType::Wait));
    // p3
    auto tr3_0 = app_side->create_transition(1, 1, static_cast<short>(TrType::ISend));
    auto tr3_1 = app_side->create_transition(1, 1, static_cast<short>(TrType::Wait));

    // actors
    auto actor_0 = app_side->create_actor(0, std::move(*tr0_0), std::move(*tr0_1));
    auto actor_1 = app_side->create_actor(1, std::move(*tr1_0), std::move(*tr1_1));
    auto actor_2 = app_side->create_actor(2, std::move(*tr2_0), std::move(*tr2_1), std::move(*tr2_2), std::move(*tr2_3));
    auto actor_3 = app_side->create_actor(3, std::move(*tr3_0), std::move(*tr3_1));
    app_side->add_to_actors(std::move(*actor_0), std::move(*actor_1), std::move(*actor_2), std::move(*actor_3));

    // mailbox
//    app->add_to_mailbox_list(1);

    // config
    std::vector<unsigned int> config {9, 9, 9, 9, 9, 9};

//    make_test(app, config, 59);
}

#endif // MAIN_INCLUDE_HPP
