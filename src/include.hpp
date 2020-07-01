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
    State s                        = stateStack.back();
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

#endif // INCLUDE_HPP
