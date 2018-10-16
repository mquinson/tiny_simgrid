#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <array>
#include <set>
#include <list>
#include <queue>
using namespace std;



class UnfoldingEvent;
class EventSet;
class Transition;
class Actor;
class IntSet;
extern unsigned int nb_events;
extern unsigned int nb_traces;

extern EventSet U, G, gD;

class Transition {
public:

	int actor_id = 0;
	int id = 0;

	bool executed = false;
	int read_write = 0; // default value is read (= 0), write =1, if mutex lock = 2, unlock = 3
	int access_var = 0; // default this transition access variable 0
	int mailbox_id = -1; // used to present mailbox id for send and receive transition
	int commId = -1; // the communication that i concern (used for only send, receive, wait and test operations)
	string type=""; // Isend, Ireceive, test, wait
	int mutexID = -1; // the mutex i touch
	int lockId = -1; // used for Mtest and Mwait


	bool isDependent(Transition other);
	Transition() {
	}
	;

	bool operator<(const Transition& other) const;
	bool operator==(const Transition& other) const;

	Transition(int read_write, int access_var);
	Transition(int mbId, int commId, string type);

};
class Actor {
public:
	int id = 0;
	int nb_trans = 0;
	std::array<Transition, 10> trans;
	Actor() {
	}
	;
	Actor(int id, int nb_trans, std::array<Transition, 10> &trans);
	bool operator<(const Actor& other) const;

};
/*
class Comunication {
	int comId = -1;
	int id_send;
	int id_receive;

};
*/
struct Comunication {
	int actorId=-1;
	int commId= -1;
	string status="pending";

};

class Mailbox {
public:
	int id=0, nbSend = 0, nbReceive = 0;

	std::array<Comunication, 20> sendList;
	std::array<Comunication, 20> receiveList;
	void update(Transition t);
	bool checkComm(Transition t);
	bool operator<(const Mailbox& other) const;



};

class State {
public:
	int nb_actor = 0;
	bool initialState = false;
	std::set<Actor> actors;
	std::set<Mailbox> mailboxes;

	State() {
	}
	;
	State(int nb_actor, std::set<Actor> actors, std::set<Mailbox> mailboxes);
	std::set<Transition> getEnabledTransition();
	State execute(Transition t);


	void print();
};

class EventSet {
public:
	bool contains(UnfoldingEvent *e);
	UnfoldingEvent* find(UnfoldingEvent *e);
    void  subtruct(EventSet otherSet);
	bool depends(EventSet s2);
	bool isConfig();
	size_t size() const;
	std::set<UnfoldingEvent*> events_;
	bool conflictWithEvt(UnfoldingEvent *e);
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

	EventSet minus(UnfoldingEvent *evt);
	EventSet plus(UnfoldingEvent *);

};

class Configuration: public EventSet {
public:

	EventSet maxEvent; // Events recently added to events_
	EventSet actorMaxEvent; // maximal events of the actors in current configuration
	UnfoldingEvent * lastEvent; // The last added event

	Configuration plus(UnfoldingEvent *);
	void createEvts(Configuration C, EventSet& result, Transition t,
			EventSet causuality_events, EventSet cause,
			EventSet candidateHistory, bool chk, UnfoldingEvent *immPreEvt);
	void updateMaxEvent(UnfoldingEvent *); // update maximal events of the configuration and actors
	UnfoldingEvent * findActorMaxEvt(int actorId); // find maximal event of a Actor whose id = actorId

	UnfoldingEvent * findTestedComm(UnfoldingEvent *testEvt);// find comm tested by action testTrans

};
class IntSet {
public:
	std::set<int> ints;
	IntSet() {
	}
	;
	void insert(int e);
	bool inculude(IntSet other);

};

class UnfoldingEvent {
public:
	int id = -1;
	State appState;
	Transition transition; // The last transition made to reach that state
	EventSet causes;       // used to store directed ancestors of event e
	EventSet conflictEvts; // used for Test and Send/Receive events, storing conflicts events with me (concern the same communication)

	UnfoldingEvent() {
	};

	UnfoldingEvent(int nb_events, Transition t, EventSet causes);

	EventSet getHistory() const;

	bool isConflict(UnfoldingEvent *event , UnfoldingEvent *otherEvent);
	bool concernSameComm(UnfoldingEvent *event , UnfoldingEvent *otherEvent);

	//check otherEvent is in my history ?
	bool inHistory(UnfoldingEvent *otherEvent);

	bool isImmediateConflict(UnfoldingEvent *evt, UnfoldingEvent* otherEvt);
	bool isImmediateConflict1(UnfoldingEvent *evt, UnfoldingEvent* otherEvt);


	bool conflictWithConfig(UnfoldingEvent *event, Configuration config);
	bool operator<(const UnfoldingEvent& other) const;
	bool operator==(const UnfoldingEvent& other) const;
	void print();
};

class UnfoldingChecker {
	EventSet A, D;
	Configuration C;
	unsigned long expandedStatesCount_ = 0;
	int Mode = 1; // Mode = 1 is a mutexed model
//  static Session& getSession();

public:
	void explore(Configuration C, std::list<EventSet> maxEvtHistory, EventSet D,
			EventSet A, UnfoldingEvent *currentEvt, EventSet prev_enC,
			std::set<Actor> proc);

	void extend(std::set<Actor> proc, Configuration C,
			std::list<EventSet> maxEvtHistory, EventSet & ExC, EventSet& enC);
	void remove(UnfoldingEvent *e, Configuration C, EventSet D);
	EventSet computeAlt( EventSet D, Configuration C);
	EventSet KpartialAlt(EventSet D, Configuration C);

	void genEventFromCandidate(EventSet& result, Transition t,
			UnfoldingEvent* preEvt, EventSet U1, EventSet Uc);
	EventSet filter(Configuration C, EventSet U);
//  static Session& session;
};


