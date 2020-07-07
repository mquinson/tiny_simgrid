#include "AppSide.h"

namespace tiny_simgrid {
namespace  app {

const char* ListTypeName[] = {"transition", "actor", "mailbox"};
const char* TransitionTypeName[] = {"Isend", "Ireceive", "Test", "Wait"};

Transition* AppSide::create_transition(int mailbox_id, int communication_id, TransitionType type) const {
    return new Transition(mailbox_id, communication_id, TransitionTypeName[static_cast<int>(type)]);
}

Transition* AppSide::create_transition(TransitionActivity activity, int access_variable) const {
    return new Transition(static_cast<int>(activity), access_variable);
}

} // namespace app
} // namespace tiny_simgrid
