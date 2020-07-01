#ifndef MAILBOX_H
#define MAILBOX_H

#include <iostream>
#include <array>
#include "../Unfolding/Transition.h"

using namespace std;
using namespace tiny_simgrid::mc;

namespace tiny_simgrid {
namespace app {

struct Communication {
    int actorId {-1};
    int commId {-1};
    string status {"pending"};
};

class Mailbox
{
public:
    explicit Mailbox(int i) : id(i) {}

    int id {0};
    unsigned int nbSend {0};
    unsigned int nbReceive {0};

    std::array<Communication, 20> sendList;
    std::array<Communication, 20> receiveList;
    void update(Transition t);
    bool checkComm(Transition t);
    bool operator<(const Mailbox& other) const { return (this->id < other.id); }
};

} // namespace app
} // namespace tiny_simgrid

#endif // MAILBOX_H
