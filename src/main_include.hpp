#ifndef MAIN_INCLUDE_HPP
#define MAIN_INCLUDE_HPP

#include "App/AppSide.h"

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

    auto tr_0 = app_side->create_transition(1, 1, static_cast<short>(TrType::ISend)); // p0
    auto tr_1 = app_side->create_transition(1, 1, static_cast<short>(TrType::Wait)); // p0
    auto tr_2 = app_side->create_transition(1, 1, static_cast<short>(TrType::ISend)); // p1
    auto tr_3 = app_side->create_transition(1, 1, static_cast<short>(TrType::Wait)); // p1
    auto tr_4 = app_side->create_transition(1, 1, static_cast<short>(TrType::IReceive)); // p2
    auto tr_5 = app_side->create_transition(1, 1, static_cast<short>(TrType::Wait)); // p2
    auto tr_6 = app_side->create_transition(1, 2, static_cast<short>(TrType::IReceive)); // p2
    auto tr_7 = app_side->create_transition(1, 2, static_cast<short>(TrType::Wait)); // p2
    auto tr_8 = app_side->create_transition(1, 1, static_cast<short>(TrType::ISend)); // p3
    auto tr_9 = app_side->create_transition(1, 1, static_cast<short>(TrType::Wait)); // p3

    // actors
    auto actor_0 = app_side->create_actor(0, std::move(*tr_0), std::move(*tr_1));
//    auto actor_1 = app_side->create_actor(1, std::move(*tr_2), std::move(*tr_3));
//    auto actor_2 = app_side->create_actor(2, std::move(*tr_4), std::move(*tr_5), std::move(*tr_6), std::move(*tr_7));
//    auto actor_3 = app_side->create_actor(3, std::move(*tr_8), std::move(*tr_9));
//    app_side->add_to_actors(std::move(*actor_0), std::move(*actor_1), std::move(*actor_2), std::move(*actor_3));

    // mailbox
//    app->add_to_mailbox_list(1);

    // config
    std::vector<unsigned int> config {9, 9, 9, 9, 9, 9};

//    make_test(app, config, 59);
}

#endif // MAIN_INCLUDE_HPP
