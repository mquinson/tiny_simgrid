#include "Transition.h"

namespace app {

Transition::Transition(int read_write, int access_var)
{
    this->read_write = read_write;
    this->access_var = access_var;
}

Transition::Transition(int mbId, int commId, std::string type)
{
    this->mailbox_id = mbId;
    this->commId     = commId;
    this->type       = type;
}

bool Transition::operator<(const Transition& other) const
{

    return ((this->id < other.id) || (this->actor_id < other.actor_id));
}

//bool Transition::operator==(const Transition& other)
//{

//    return ((this->id == other.id) && (this->actor_id == other.actor_id));
//}

bool Transition::isDependent(Transition other)
{
    // two transitions are in the same actor => dependent (causality dependence)
    if (this->actor_id == other.actor_id)
        return true;

    if (this->type == "Isend") {
        if (other.type == "Isend" && (this->mailbox_id == other.mailbox_id))
            return true;
    }

    else if (this->type == "Ireceive") {
        if (other.type == "Ireceive" && (this->mailbox_id == other.mailbox_id))
            return true;
    }

    else if (this->type == "Lock" && other.type == "Lock" && this->mutexID == other.mutexID)
        return true;
    else if (this->type == "Unlock") {
        if (other.type == "Mwait" || other.type == "Mtest")
            return true;
    }

    // for read - write model
    else {

        // if at least one write transition  => dependent
        if (this->access_var == other.access_var)
            if ((this->read_write == 1) || (other.read_write == 1))
                return true;
    }

    return false;
}

} // namespace app
