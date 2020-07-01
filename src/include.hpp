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

#endif // INCLUDE_HPP
