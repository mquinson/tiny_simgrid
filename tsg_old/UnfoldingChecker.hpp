#include <algorithm>
#include <array>
#include <iostream>
#include <list>
#include <memory>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;

class UnfoldingEvent;
class EventSet;
class Transition;
class Actor;
extern unsigned int nb_events;
extern unsigned int nb_traces;

extern EventSet U, G, gD;

class Transition {
public:
  int actor_id    = 0;
  unsigned int id = 0;

  bool executed  = false;
  int read_write = 0;  // default value is read (= 0), write =1, if mutex lock = 2, unlock = 3
  int access_var = 0;  // default this transition access variable 0
  int mailbox_id = -1; // used to present mailbox id for send and receive transition
  int commId     = -1; // the communication that i concern (used for only send, receive, wait and test operations)
  string type    = ""; // Isend, Ireceive, test, wait
  int mutexID    = -1; // the mutex i touch
  int lockId     = -1; // used for Mtest and Mwait

  bool isDependent(Transition other);
  Transition() {}

  bool operator<(const Transition& other) const;
  bool operator==(const Transition& other) const;

  Transition(int read_write, int access_var);
  Transition(int mbId, int commId, string type);
};
class Actor {
public:
  int id                 = 0;
  unsigned long nb_trans = 0;
  std::vector<Transition> trans;
  Actor() {}

  Actor(int id, unsigned int nb_trans, std::array<Transition, 30>& trans);
  Actor(int id, std::vector<Transition> trans);
  bool operator<(const Actor& other) const;
};
struct Communication {
  int actorId   = -1;
  int commId    = -1;
  string status = "pending";
};

class Mailbox {
public:
  int id                 = 0;
  unsigned int nbSend    = 0;
  unsigned int nbReceive = 0;

  std::array<Communication, 20> sendList;
  std::array<Communication, 20> receiveList;
  void update(Transition t);
  bool checkComm(Transition t);
  bool operator<(const Mailbox& other) const;

  Mailbox(int i) : id(i) {}
  Mailbox() = default;
};

class State {
public:
  unsigned long nb_actors_ = 0;
  std::set<Actor> actors_;
  std::set<Mailbox> mailboxes_;

  State() = default;
  State(unsigned long nb_actors_, std::set<Actor> actors_, std::set<Mailbox> mailboxes_);
  State(std::set<Actor> actors, std::set<Mailbox> mailboxes) : State(actors.size(), actors, mailboxes) {}

  std::set<Transition> getEnabledTransition();
  State execute(Transition t);

  void print();
};

class EventSet {
public:
  bool contains(UnfoldingEvent* e);
  UnfoldingEvent* find(UnfoldingEvent* e);
  void subtruct(EventSet otherSet);
  bool depends(EventSet s2);
  bool isConfig();
  size_t size() const;
  std::set<UnfoldingEvent*> events_;
  bool conflictWithEvt(UnfoldingEvent* e);
  bool isEmptyIntersection(EventSet evtS1, EventSet evtS2);

  static EventSet makeUnion(EventSet s1, EventSet s2);
  static EventSet makeIntersection(EventSet s1, EventSet s2);
  const UnfoldingEvent* first();
  bool empty() const;
  UnfoldingEvent* begin() const;
  UnfoldingEvent* end() const;

  void insert(UnfoldingEvent*);
  void erase(UnfoldingEvent*);
  bool operator==(const EventSet& other) const;

  EventSet minus(UnfoldingEvent* evt);
  EventSet plus(UnfoldingEvent*);
};

class Configuration : public EventSet {
public:
  EventSet maxEvent;         // Events recently added to events_
  EventSet actorMaxEvent;    // maximal events of the actors in current configuration
  UnfoldingEvent* lastEvent; // The last added event

  Configuration plus(UnfoldingEvent*);
  void createEvts(Configuration C, EventSet& result, Transition t, EventSet causuality_events, EventSet cause,
                  EventSet candidateHistory, bool chk, UnfoldingEvent* immPreEvt);
  void updateMaxEvent(UnfoldingEvent*);         // update maximal events of the configuration and actors
  UnfoldingEvent* findActorMaxEvt(int actorId); // find maximal event of a Actor whose id = actorId

  UnfoldingEvent* findTestedComm(UnfoldingEvent* testEvt); // find comm tested by action testTrans
};

class UnfoldingEvent {
public:
  int id = -1;
  State appState;
  Transition transition; // The last transition made to reach that state
  EventSet causes;       // used to store directed ancestors of event e
  EventSet conflictEvts; // used for Test and Send/Receive events, storing conflicts events with me (concern the same
                         // communication)

  UnfoldingEvent(State* s) : appState(*s) {}

  UnfoldingEvent(unsigned int nb_events, Transition t, EventSet causes);

  EventSet getHistory() const;

  bool isConflict(UnfoldingEvent* event, UnfoldingEvent* otherEvent);
  bool concernSameComm(UnfoldingEvent* event, UnfoldingEvent* otherEvent);

  // check otherEvent is in my history ?
  bool inHistory(UnfoldingEvent* otherEvent);

  bool isImmediateConflict(UnfoldingEvent* evt, UnfoldingEvent* otherEvt);
  bool isImmediateConflict1(UnfoldingEvent* evt, UnfoldingEvent* otherEvt);

  bool conflictWithConfig(UnfoldingEvent* event, Configuration config);
  bool operator<(const UnfoldingEvent& other) const;
  bool operator==(const UnfoldingEvent& other) const;
  void print();
};

class UnfoldingChecker {
  unsigned long expandedStatesCount_ = 0;
  // int Mode = 1; // Mode = 1 is a mutexed model
  std::vector<unsigned int> confs_expected_;
  bool confs_check_             = false;
  int error_                    = 0;
  unsigned int expected_events_ = 0;

public:
  UnfoldingChecker() = default;
  UnfoldingChecker(std::vector<unsigned int> confs, unsigned int expected_events)
      : confs_expected_(confs), confs_check_(true), expected_events_(expected_events)
  {
  }

  void explore(State* state); // Start the exploration
  // Recursive function
  void explore(Configuration C, std::list<EventSet> maxEvtHistory, EventSet D, EventSet A, UnfoldingEvent* currentEvt,
               EventSet prev_enC, std::set<Actor> proc);

  void extend(std::set<Actor> proc, Configuration C, std::list<EventSet> maxEvtHistory, EventSet& ExC, EventSet& enC);
  void remove(UnfoldingEvent* e, Configuration C, EventSet D);
  EventSet computeAlt(EventSet D, Configuration C);
  EventSet KpartialAlt(EventSet D, Configuration C);

  void genEventFromCandidate(EventSet& result, Transition t, UnfoldingEvent* preEvt, EventSet U1, EventSet Uc);
  EventSet filter(Configuration C, EventSet U);

  int error_count() { return error_; }
};
