#ifndef MODELCHECKER_H
#define MODELCHECKER_H

#include "forward.hpp"

namespace mc {

class ModelChecker
{
public:
    ModelChecker(ModelChecker const&) = delete;
    ModelChecker& operator=(ModelChecker const&) = delete;
    explicit ModelChecker();

    void setChecker(Checker* checker) { checker_ = std::unique_ptr<Checker>(checker); }
    // void Session::execute(Transition const& transition);

    int get_error_count() { return checker_->get_error_count(); };

private:
    std::unique_ptr<Checker> checker_;

};

//smx_simcall_t MC_state_choose_request(simgrid::mc::State* state)
//{
//  for (auto& actor : mc_model_checker->get_remote_simulation().actors()) {
//    /* Only consider the actors that were marked as interleaving by the checker algorithm */
//    if (not state->actor_states_[actor.copy.get_buffer()->get_pid()].is_todo())
//      continue;

//    smx_simcall_t res = MC_state_choose_request_for_process(state, actor.copy.get_buffer());
//    if (res)
//      return res;
//  }
//  return nullptr;
//}

//static inline smx_simcall_t MC_state_choose_request_for_process(simgrid::mc::State* state, smx_actor_t actor)


} // namespace api

#endif // MODELCHECKER_H
