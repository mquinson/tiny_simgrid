#include "Transition.h"

namespace app
{

    Transition::Transition(int read_write, int access_var) : read_write(read_write), access_var(access_var)
    {
    }

    Transition::Transition(int mbId, int commId, const std::string &type) : mailbox_id(mbId), commId(commId), type(type)
    {
    }

    bool Transition::operator<(const Transition &other) const
    {
        return ((this->id < other.id) || (this->actor_id < other.actor_id));
    }

    bool Transition::isDependent(const Transition &other) const
    {
        // two transitions are in the same actor => dependent (causality dependence)
        if (this->actor_id == other.actor_id)
            return true;

        if (this->type == "Isend")
        {
            if (other.type == "Isend" && (this->mailbox_id == other.mailbox_id))
                return true;
        }

        else if (this->type == "Ireceive")
        {
            if (other.type == "Ireceive" && (this->mailbox_id == other.mailbox_id))
                return true;
        }

        else if (this->type == "Lock" && other.type == "Lock" && this->mutexID == other.mutexID)
            return true;
        else if (this->type == "Unlock")
        {
            if (other.type == "Mwait" || other.type == "Mtest")
                return true;
        }

        // for read - write model
        else
        {

            // if at least one write transition  => dependent
            if ((this->access_var == other.access_var) && ((this->read_write == 1) || (other.read_write == 1)))
                return true;
        }

        return false;
    }

} // namespace app
