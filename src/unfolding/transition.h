#ifndef TRANSITION_H
#define TRANSITION_H

#include <iostream>

using namespace std;

namespace mc {

class Transition
{
public:
    Transition() {}
    Transition(int read_write, int access_var) : read_write(read_write), access_var(access_var) {}
    Transition(int mbId, int commId, string type) : mailbox_id(mbId), commId(commId), type(type) {}

    int actor_id {0};
    unsigned int id {0};

    bool executed {false};
    int read_write {0};  // default value is read (= 0), write =1, if mutex lock = 2, unlock = 3
    int access_var {0};  // default this transition access variable 0
    int mailbox_id {-1}; // used to present mailbox id for send and receive transition
    int commId {-1}; // the communication that i concern (used for only send, receive, wait and test operations)
    string type; // Isend, Ireceive, test, wait
    int mutexID {-1}; // the mutex i touch
    int lockId {-1}; // used for Mtest and Mwait

    bool isDependent(Transition other);
    bool operator<(const Transition& other) const;
    bool operator==(const Transition& other) const;

};

} // namespace mc

#endif // TRANSITION_H
