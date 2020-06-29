#ifndef APP_FORWARD_HPP
#define APP_FORWARD_HPP

#include <list>
#include <memory>
#include <cstring>

#include "actor.h"
#include "mailbox.h"
#include "AppSide.h"
//#include "../api/Session.h"
#include "../unfolding/state.h"
#include "../unfolding/UnfoldingEvent.h"
#include "../unfolding/UnfoldingChecker.h"
#include "../unfolding/transition.h"
#include "../unfolding/configuration.h"
#include "../unfolding/EventSet.h"
#include "../unfolding/Checker.h"

using namespace std;

static int nbInt = 0;

enum class ListType {
    transition = 0,
    actor,
    mailbox
};

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

void make_test(const std::unique_ptr<AppSide>& app, const std::vector<unsigned int>& config, const int& event_count)
{
//    using Session = tiny_simgrid::api::Session;
//    auto session_ = std::unique_ptr<Session>(new Session(*app));
//    auto session_ = std::unique_ptr<Session>();

    auto a=20;

//    std::unique_ptr<ModelChecker> model_ckecker_ = std::unique_ptr<ModelChecker>(new ModelChecker());
//    model_ckecker_->setChecker(new UnfoldingChecker(confs, evt_count));



////    UC.explore(new State(actors.size(), actors, mailboxes));

//    auto error_count = model_ckecker_->get_error_count();
//    if (error_count > 0) {
//        std::cerr << "\n\nSOMETHING WENT WRONG. Error count: " << error_count << "\n";
//        exit(EXIT_FAILURE);
//    } else {
//        return true;
//    }
}

#endif // APP_FORWARD_HPP
