#ifndef INCLUDE_HPP
#define INCLUDE_HPP

#include <list>
#include <memory>
#include <cstring>
#include <iostream>

#include "App/Actor.h"
#include "App/AppSide.h"
#include "Api/CheckerSide.hpp"

using TransitionActivity = tiny_simgrid::app::AppSide::TransitionActivity;
using TransitionType = tiny_simgrid::app::AppSide::TransitionType;
using AppSide = tiny_simgrid::app::AppSide;
using CheckerSide = tiny_simgrid::api::CheckerSide;
static int nbInt = 0;

std::unique_ptr<AppSide> app = std::unique_ptr<AppSide>(new AppSide());

void make_test(const std::unique_ptr<tiny_simgrid::app::AppSide>& app, const std::vector<unsigned int>& configs, int expected_events)
{
    auto checker_side = new CheckerSide();
    checker_side->set_mc_params(app.get(), configs, expected_events);
    auto error_count = checker_side->run();
    if(error_count > 0) {
        std::cerr << "\n\nSOMETHING WENT WRONG. Error count: " << error_count << "\n";
        exit(EXIT_FAILURE);
    }
}

void exhautiveExplore(std::list<State> stateStack, std::list<Transition> transList)
{
    State s = stateStack.back();
    std::set<Transition> trans_set = s.getEnabledTransition();
    if (trans_set.empty()) {
        nbInt++;
        std::cout << " \n Interleaving  " << nbInt << ":  ";
        for (auto t : transList)
            std::cout << "(t_" << t.id << ",p_" << t.actor_id << "-" << t.type << " )   ";

        stateStack.pop_back();
    } else {
        for (auto t : trans_set) {
            std::list<Transition> transList1 = transList;
            transList1.push_back(t);

            State s1 = s.execute(t);
            stateStack.push_back(s1);
            exhautiveExplore(stateStack, transList1);
        }
    }
}

void TEST_1 () {
    auto tr_0 = app->create_transition(TransitionActivity::write, 0);
    auto tr_1 = app->create_transition(TransitionActivity::read, 0);
    auto tr_2 = app->create_transition(TransitionActivity::read, 0);
    // actors
    auto actor_0 = app->create_actor(0, std::move(*tr_0));
    auto actor_1 = app->create_actor(1, std::move(*tr_1));
    auto actor_2 = app->create_actor(2, std::move(*tr_2));
    app->add_to_actor_list(std::move(*actor_0), std::move(*actor_1), std::move(*actor_2));
    // config
    std::vector<unsigned int> config {3, 3, 3, 3};

    make_test(app, config, 20);
}

void TEST_2() {
    // the second example
    auto tr_0 = app->create_transition(TransitionActivity::write, 0); // p0
    auto tr_1 = app->create_transition(TransitionActivity::write, 1); // p1
    auto tr_2 = app->create_transition(TransitionActivity::write, 0); // p1
    // actors
    auto actor_1 = app->create_actor(1, std::move(*tr_0));
    auto actor_2 = app->create_actor(2, std::move(*tr_1), std::move(*tr_2));
    app->add_to_actor_list(std::move(*actor_1), std::move(*actor_2));
    // config
    std::vector<unsigned int> config {3, 3};

    make_test(app, config, 10);
}

void TEST_3() {
    // the third example - 1 trace
    // Transition(read_write, access_variable)
    auto tr_0 = app->create_transition(TransitionActivity::write, 0); // p0
    auto tr_1 = app->create_transition(TransitionActivity::write, 1); // p1
    auto tr_2 = app->create_transition(TransitionActivity::write, 2); // p1
    // actors
    auto actor_0 = app->create_actor(0, std::move(*tr_0));
    auto actor_1 = app->create_actor(1, std::move(*tr_1));
    auto actor_2 = app->create_actor(2, std::move(*tr_2));
    app->add_to_actor_list(std::move(*actor_0), std::move(*actor_1), std::move(*actor_2));
    // config
    std::vector<unsigned int> config {3};

    make_test(app, config, 3);
}

void TEST_4() {
    // the fourth example - 6 traces
    // Transition(read_write, access_variable)
    auto tr_0 = app->create_transition(TransitionActivity::write, 0); // p0
    auto tr_1 = app->create_transition(TransitionActivity::write, 0); // p1
    auto tr_2 = app->create_transition(TransitionActivity::write, 0); // p1
    // actors
    auto actor_0 = app->create_actor(0, std::move(*tr_0));
    auto actor_1 = app->create_actor(1, std::move(*tr_1));
    auto actor_2 = app->create_actor(2, std::move(*tr_2));
    app->add_to_actor_list(std::move(*actor_0), std::move(*actor_1), std::move(*actor_2));
    // config
    std::vector<unsigned int> config {3, 3, 3, 3, 3, 3};

    make_test(app, config, 27);
}

void TEST_5() {
    auto tr_0 = app->create_transition(TransitionActivity::write, 0); // p0
    auto tr_1 = app->create_transition(TransitionActivity::write, 1); // p0
    auto tr_2 = app->create_transition(TransitionActivity::write, 0); // p1
    auto tr_3 = app->create_transition(TransitionActivity::write, 1); // p1
    // actors
    auto actor_0 = app->create_actor(0, std::move(*tr_0), std::move(*tr_1));
    auto actor_1 = app->create_actor(1, std::move(*tr_2), std::move(*tr_3));
    app->add_to_actor_list(std::move(*actor_0), std::move(*actor_1));
    // config
    std::vector<unsigned int> config {4, 4, 4, 4};

    make_test(app, config, 16);
}

void TEST_6() {
    // 6th example - 3 traces
    // Transition(read_write, access_variable)
    auto tr_0 = app->create_transition(TransitionActivity::write, 0); // p0
    auto tr_1 = app->create_transition(TransitionActivity::write, 1); // p0
    auto tr_2 = app->create_transition(TransitionActivity::write, 1); // p1
    auto tr_3 = app->create_transition(TransitionActivity::write, 0); // p1
    // actors
    auto actor_0 = app->create_actor(0, std::move(*tr_0), std::move(*tr_1));
    auto actor_1 = app->create_actor(1, std::move(*tr_2), std::move(*tr_3));
    app->add_to_actor_list(std::move(*actor_0), std::move(*actor_1));
    // config
    std::vector<unsigned int> config {4, 4, 4};

    make_test(app, config, 16);
}

void TEST_7() {
    // 7th example - 4 traces
    // Transition(read_write, access_variable)
    auto tr_0 = app->create_transition(TransitionActivity::write, 0); // p0
    auto tr_1 = app->create_transition(TransitionActivity::write, 1); // p1
    auto tr_2 = app->create_transition(TransitionActivity::write, 1); // p2
    auto tr_3 = app->create_transition(TransitionActivity::write, 0); // p2
    // actors
    auto actor_0 = app->create_actor(0, std::move(*tr_0));
    auto actor_1 = app->create_actor(1, std::move(*tr_1));
    auto actor_2 = app->create_actor(2, std::move(*tr_2), std::move(*tr_3));
    app->add_to_actor_list(std::move(*actor_0), std::move(*actor_1), std::move(*actor_2));
    // config
    std::vector<unsigned int> config {4, 4, 4, 4};

    make_test(app, config, 27);
}

void TEST_8() {
    // mutex example - 1 traces
    // Transition(read_write, access_variable)
    auto tr_0 = app->create_transition(TransitionActivity::mutex_lock, 0); // p0
    auto tr_1 = app->create_transition(TransitionActivity::mutex_unlock, 0); // p0
    auto tr_2 = app->create_transition(TransitionActivity::mutex_lock, 0); // p1
    auto tr_3 = app->create_transition(TransitionActivity::mutex_unlock, 0); // p1
    // actors
    auto actor_0 = app->create_actor(0, std::move(*tr_0), std::move(*tr_1));
    auto actor_1 = app->create_actor(1, std::move(*tr_2), std::move(*tr_3));
    app->add_to_actor_list(std::move(*actor_0), std::move(*actor_1));
    // config
    std::vector<unsigned int> config {2};

    make_test(app, config, 2);
}

void TEST_9() {
    // mutex example - 1 trace
    // Transition(read_write, access_variable)
    auto tr_0 = app->create_transition(TransitionActivity::read, 0); // p0
    auto tr_1 = app->create_transition(TransitionActivity::mutex_lock, 1); // p0
    auto tr_2 = app->create_transition(TransitionActivity::mutex_unlock, 1); // p0
    auto tr_3 = app->create_transition(TransitionActivity::mutex_lock, 1); // p1
    auto tr_4 = app->create_transition(TransitionActivity::mutex_unlock, 1); // p1
    // actors
    auto actor_0 = app->create_actor(0, std::move(*tr_0), std::move(*tr_1), std::move(*tr_2));
    auto actor_1 = app->create_actor(1, std::move(*tr_3), std::move(*tr_4));
    app->add_to_actor_list(std::move(*actor_0), std::move(*actor_1));
    // config
    std::vector<unsigned int> config {2};

    make_test(app, config, 2);
}

void TEST_10() {
    // 3 traces
    // Transition(read_write, access_variable)
    auto tr_0 = app->create_transition(TransitionActivity::write, 0); // p0
    auto tr_1 = app->create_transition(TransitionActivity::write, 0); // p0
    auto tr_2 = app->create_transition(TransitionActivity::write, 1); // p1
    auto tr_3 = app->create_transition(TransitionActivity::write, 0); // p1
    // actors
    auto actor_0 = app->create_actor(0, std::move(*tr_0), std::move(*tr_1));
    auto actor_1 = app->create_actor(1, std::move(*tr_2), std::move(*tr_3));
    app->add_to_actor_list(std::move(*actor_0), std::move(*actor_1));
    // config
    std::vector<unsigned int> config {4, 4, 4};

    make_test(app, config, 18);
}

void TEST_11() {
    // the first simix model -> 2 traces
    // Transition (maiboxid, commid, type)
    auto tr_0 = app->create_transition(1, 1, TransitionType::Isend); // p0
    auto tr_1 = app->create_transition(1, 1, TransitionType::wait); // p0
    auto tr_2 = app->create_transition(1, 1, TransitionType::Isend); // p1
    auto tr_3 = app->create_transition(1, 1, TransitionType::Ireceive); // p2

    // actors
    auto actor_0 = app->create_actor(0, std::move(*tr_0), std::move(*tr_1));
    auto actor_1 = app->create_actor(1, std::move(*tr_2));
    auto actor_2 = app->create_actor(2, std::move(*tr_3));
    app->add_to_actor_list(std::move(*actor_0), std::move(*actor_1), std::move(*actor_2));

    // mailbox
    app->add_to_mailbox_list(1);

    // config
    std::vector<unsigned int> config {4, 3};

    make_test(app, config, 9);
}

void TEST_12() {
    // the 2nd simix model -> 1 trace
    // Transition (maiboxid, commid, type)
    auto tr_0 = app->create_transition(1, 1, TransitionType::Isend); // p0
    auto tr_1 = app->create_transition(1, 1, TransitionType::wait); // p0
    auto tr_2 = app->create_transition(2, 1, TransitionType::Isend); // p1
    auto tr_3 = app->create_transition(1, 1, TransitionType::Ireceive); // p2

    // actors
    auto actor_0 = app->create_actor(0, std::move(*tr_0), std::move(*tr_1));
    auto actor_1 = app->create_actor(1, std::move(*tr_2));
    auto actor_2 = app->create_actor(2, std::move(*tr_3));
    app->add_to_actor_list(std::move(*actor_0), std::move(*actor_1), std::move(*actor_2));

    // mailbox
    app->add_to_mailbox_list(1);

    // config
    std::vector<unsigned int> config {4};

    make_test(app, config, 4);
}

void TEST_13() {
    // the first simix model -> 2 traces
    // Transition (maiboxid, commid, type)
    auto tr_0 = app->create_transition(1, 1, TransitionType::Isend); // p0
    auto tr_1 = app->create_transition(1, 1, TransitionType::wait); // p0
    auto tr_2 = app->create_transition(1, 1, TransitionType::Isend); // p1
    auto tr_3 = app->create_transition(1, 1, TransitionType::wait); // p1
    auto tr_4 = app->create_transition(1, 1, TransitionType::Ireceive); // p2
    auto tr_5 = app->create_transition(1, 1, TransitionType::wait); // p2

    // actors
    auto actor_0 = app->create_actor(0, std::move(*tr_0), std::move(*tr_1));
    auto actor_1 = app->create_actor(1, std::move(*tr_2), std::move(*tr_3));
    auto actor_2 = app->create_actor(2, std::move(*tr_4), std::move(*tr_5));
    app->add_to_actor_list(std::move(*actor_0), std::move(*actor_1), std::move(*actor_2));

    // mailbox
    app->add_to_mailbox_list(1);

    // config
    std::vector<unsigned int> config {5, 5};

    make_test(app, config, 13);
}

void TEST_14() {
    // the first simix model -> 2 traces
    // Transition (maiboxid, commid, type)

    auto tr_0 = app->create_transition(1, 1, TransitionType::Isend); // p0
    auto tr_1 = app->create_transition(1, 1, TransitionType::wait); // p0
    auto tr_2 = app->create_transition(1, 1, TransitionType::Isend); // p1
    auto tr_3 = app->create_transition(1, 1, TransitionType::wait); // p1
    auto tr_4 = app->create_transition(1, 1, TransitionType::Ireceive); // p2
    auto tr_5 = app->create_transition(1, 1, TransitionType::wait); // p2
    auto tr_6 = app->create_transition(1, 1, TransitionType::Ireceive); // p2
    auto tr_7 = app->create_transition(1, 1, TransitionType::wait); // p2

    // actors
    auto actor_0 = app->create_actor(0, std::move(*tr_0), std::move(*tr_1));
    auto actor_1 = app->create_actor(1, std::move(*tr_2), std::move(*tr_3));
    auto actor_2 = app->create_actor(2, std::move(*tr_4), std::move(*tr_5), std::move(*tr_6), std::move(*tr_7));
    app->add_to_actor_list(std::move(*actor_0), std::move(*actor_1), std::move(*actor_2));

    // mailbox
    app->add_to_mailbox_list(1);

    // config
    std::vector<unsigned int> config {8, 8};

    make_test(app, config, 22);
}

void TEST_15() {
    // the first simix model -> 6 traces
    // Transition (maiboxid, commid, type)
    auto tr_0 = app->create_transition(1, 1, TransitionType::Isend); // p0
    auto tr_1 = app->create_transition(1, 1, TransitionType::wait); // p0
    auto tr_2 = app->create_transition(1, 1, TransitionType::Isend); // p1
    auto tr_3 = app->create_transition(1, 1, TransitionType::wait); // p1
    auto tr_4 = app->create_transition(1, 1, TransitionType::Ireceive); // p2
    auto tr_5 = app->create_transition(1, 1, TransitionType::wait); // p2
    auto tr_6 = app->create_transition(1, 2, TransitionType::Ireceive); // p2
    auto tr_7 = app->create_transition(1, 2, TransitionType::wait); // p2
    auto tr_8 = app->create_transition(1, 1, TransitionType::Isend); // p3
    auto tr_9 = app->create_transition(1, 1, TransitionType::wait); // p3


    // actors
    auto actor_0 = app->create_actor(0, std::move(*tr_0), std::move(*tr_1));
    auto actor_1 = app->create_actor(1, std::move(*tr_2), std::move(*tr_3));
    auto actor_2 = app->create_actor(2, std::move(*tr_4), std::move(*tr_5), std::move(*tr_6), std::move(*tr_7));
    auto actor_3 = app->create_actor(3, std::move(*tr_8), std::move(*tr_9));
    app->add_to_actor_list(std::move(*actor_0), std::move(*actor_1), std::move(*actor_2), std::move(*actor_3));

    // mailbox
    app->add_to_mailbox_list(1);

    // config
    std::vector<unsigned int> config {9, 9, 9, 9, 9, 9};

    make_test(app, config, 59);
}

void TEST_16() {
    // the first simix model -> 6 traces
    // Transition (maiboxid, commid, type)
    auto tr0_0 = app->create_transition(1, 1, TransitionType::Ireceive); // p0
    auto tr0_1 = app->create_transition(1, 1, TransitionType::wait); // p0
    auto tr0_2 = app->create_transition(1, 2, TransitionType::Ireceive); // p0
    auto tr0_3 = app->create_transition(1, 2, TransitionType::wait); // p0
    auto tr0_4 = app->create_transition(1, 3, TransitionType::Ireceive); // p0
    auto tr0_5 = app->create_transition(1, 3, TransitionType::wait); // p0
    auto tr1_0 = app->create_transition(1, 1, TransitionType::Isend); // p1
    auto tr1_1 = app->create_transition(1, 1, TransitionType::wait); // p1
    auto tr2_0 = app->create_transition(1, 1, TransitionType::Isend); // p2
    auto tr2_1 = app->create_transition(1, 1, TransitionType::wait); // p2
    auto tr3_0 = app->create_transition(1, 1, TransitionType::Isend); // p3
    auto tr3_1 = app->create_transition(1, 1, TransitionType::wait); // p3

    // actors
    auto actor_0 = app->create_actor(0, std::move(*tr0_0), std::move(*tr0_1),
                                     std::move(*tr0_2), std::move(*tr0_3),
                                     std::move(*tr0_4), std::move(*tr0_5));
    auto actor_1 = app->create_actor(1, std::move(*tr1_0), std::move(*tr1_1));
    auto actor_2 = app->create_actor(2, std::move(*tr2_0), std::move(*tr2_1));
    auto actor_3 = app->create_actor(3, std::move(*tr3_0), std::move(*tr3_1));
    app->add_to_actor_list(std::move(*actor_0), std::move(*actor_1), std::move(*actor_2), std::move(*actor_3));

    // mailbox
    app->add_to_mailbox_list(1);

    // config
    std::vector<unsigned int> config {12, 12, 12, 12, 12, 12};

    make_test(app, config, 90);
}

void TEST_17() {
    //  3 traces
    // Transition (maiboxid, commid, type)
    auto tr0_0 = app->create_transition(1, 1, TransitionType::Isend); // p0
    auto tr0_1 = app->create_transition(1, 1, TransitionType::test); // p0
    auto tr1_0 = app->create_transition(1, 1, TransitionType::Isend); // p1
    auto tr2_0 = app->create_transition(1, 1, TransitionType::Ireceive); // p2

    // actors
    auto actor_0 = app->create_actor(0, std::move(*tr0_0), std::move(*tr0_1));
    auto actor_1 = app->create_actor(1, std::move(*tr1_0));
    auto actor_2 = app->create_actor(2, std::move(*tr2_0));
    app->add_to_actor_list(std::move(*actor_0), std::move(*actor_1), std::move(*actor_2));

    // mailbox
    app->add_to_mailbox_list(1);

    // config
    std::vector<unsigned int> config {4, 4, 4};

    make_test(app, config, 14);
}

#endif // INCLUDE_HPP
