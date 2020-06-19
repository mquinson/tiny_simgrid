#ifndef MAILBOX_H
#define MAILBOX_H

#include <iostream>
#include <array>
#include "../unfolding/transition.h"

using namespace std;

struct Communication {
    int actorId {-1};
    int commId {-1};
    string status {"pending"};
};

class Mailbox
{
public:
    Mailbox() = default;
    Mailbox(int i) : id(i) {}

    int id {0};
    unsigned int nbSend {0};
    unsigned int nbReceive {0};

    std::array<Communication, 20> sendList;
    std::array<Communication, 20> receiveList;
    void update(Transition t);
    bool checkComm(Transition t);
    bool operator<(const Mailbox& other) const { return (this->id < other.id); }
};

#endif // MAILBOX_H
