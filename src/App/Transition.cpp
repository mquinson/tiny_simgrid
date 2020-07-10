#include "Transition.h"

Transition::Transition(int read_write, int access_var)
{
    this->read_write = read_write;
    this->access_var = access_var;
}

Transition::Transition(int mbId, int commId, string type)
{
    this->mailbox_id = mbId;
    this->commId     = commId;
    this->type       = type;
}

bool Transition::operator<(const Transition& other) const
{

    return ((this->id < other.id) || (this->actor_id < other.actor_id));
}
bool Transition::operator==(const Transition& other) const
{

    return ((this->id == other.id) && (this->actor_id == other.actor_id));
}

bool Transition::isDependent(Transition other)
{
    // two transitions are in the same actor => dependent (causality dependence)
    if (this->actor_id == other.actor_id)
        return true;

    if (this->type == "Isend") {
        if (other.type == "Isend" and (this->mailbox_id == other.mailbox_id))
            return true;
    }

    else if (this->type == "Ireceive") {
        if (other.type == "Ireceive" and (this->mailbox_id == other.mailbox_id))
            return true;
    }

    else if (this->type == "Lock" and other.type == "Lock" and this->mutexID == other.mutexID)
        return true;
    else if (this->type == "Unlock") {
        if (other.type == "Mwait" or other.type == "Mtest")
            return true;
    }

    // for read - write model
    else {

        // if at least one write transition  => dependent
        if (this->access_var == other.access_var)
            if ((this->read_write == 1) or (other.read_write == 1))
                return true;
    }

    return false;
}
