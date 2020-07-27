#ifndef MAILBOX_H
#define MAILBOX_H

#include <array>
#include "Transition.h"

namespace app {

struct Communication {
    int actorId   = -1;
    int commId    = -1;
    std::string status = "pending";
};

class Mailbox {
public:
    int id                 = 0;
    unsigned int nbSend    = 0;
    unsigned int nbReceive = 0;

    std::array<Communication, 20> sendList;
    std::array<Communication, 20> receiveList;
    void update(const Transition& t);
    bool checkComm(Transition t);
    bool operator<(const Mailbox& other) const;

    explicit Mailbox(int i) : id(i) {}
    Mailbox() = default;
};

} // namespace app

#endif // MAILBOX_H
