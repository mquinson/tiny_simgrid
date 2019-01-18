
#include "UnfoldingChecker.hpp"

#include <iostream>
#include <set>
#include <queue>
#include <list>
#include<string>
#include<math.h>

#include <unistd.h>

using namespace std;

static int nbInt =0;
void exhautiveExplore(std::list<State > stateStack,  std::list<Transition> transList) {
    State	s = stateStack.back();
    std::set<Transition> trans_set =  s.getEnabledTransition();
    if(trans_set.empty()){
    	nbInt++;
    	std::cout<<" \n Interleaving  " << nbInt << ":  ";
    	for (auto t : transList)  std::cout <<"(t_" <<t.id  <<",p_" << t.actor_id << " )   ";

    	stateStack.pop_back();
    }
    else{
    	for (auto t : trans_set)
    	{
    	  std::list<Transition> transList1 = transList;
    	  transList1.push_back(t);


    	  State s1 =  s.execute(t);
    	  stateStack.push_back(s1);
    	  exhautiveExplore(stateStack,transList1);

    	}

    }


}

int main() {

	  clock_t begin = clock();

	nb_events = 0;
	UnfoldingChecker UC;
	EventSet A, D;
	EventSet prev_exC;
	Configuration C;
	State *initState;
	std::set<Actor> actor_set;
	std::set<Mailbox> mailboxes;
	std::list<State> stateStack;
	std::list<Transition> transList;

	// keep history of maximal event when exploring C
	std::list<set<int> > maxEventHis;

    int example = 1;
    std::cout << " enter example:";
    //std::cin >> example;

	switch (example) {
	case 1: { // the first example (in the paper)
		// Transition(read_write, access_variable)

        actor_set.insert(Actor(1, {Transition(1, 0)}));
        actor_set.insert(Actor(2, {Transition(0, 0)}));
        actor_set.insert(Actor(3, {Transition(0, 0)}));

		Mailbox mailbox1;
		mailboxes.insert(mailbox1);

		initState = new State(3, actor_set, mailboxes);

		initState->initialState = true;
		UnfoldingEvent *e = new UnfoldingEvent();
		e->appState = *initState;

		EventSet emptyS;
		std::list<EventSet> maxEvtHistory;
		maxEvtHistory.push_back(emptyS);
		UC.explore(C, maxEvtHistory, D, A, e, prev_exC, actor_set);

	}
		break;

	case 2: { // the second example
		Transition t1(1, 0);
		Transition t2(1, 1);
		Transition t3(1, 0);

		std::array<Transition, 30> trans1, trans2, trans3;
		trans1[0] = t1;
		trans2[0] = t2;
		trans2[1] = t3;
		Actor actor1(1, 1, trans1);
		Actor actor2(2, 2, trans2);

		actor_set.insert(actor1);
		actor_set.insert(actor2);

		Mailbox mailbox1;
		mailboxes.insert(mailbox1);

		initState = new State(2, actor_set, mailboxes);

		initState->initialState = true;
		UnfoldingEvent *e = new UnfoldingEvent();
		e->appState = *initState;

		EventSet emptyS;
		std::list<EventSet> maxEvtHistory;
		maxEvtHistory.push_back(emptyS);
		UC.explore(C, maxEvtHistory, D, A, e, prev_exC, actor_set);
	}
		break;

	case 3: { //the third example
		Transition t1(1, 0);
		Transition t2(1, 1);
		Transition t3(1, 2);

		std::array<Transition, 30> trans1, trans2, trans3;
		trans1[0] = t1;
		trans2[0] = t2;
		trans3[0] = t3;
		Actor actor1(1, 1, trans1);
		Actor actor2(2, 1, trans2);
		Actor actor3(3, 1, trans3);

		actor_set.insert(actor1);
		actor_set.insert(actor2);
		actor_set.insert(actor3);

		Mailbox mailbox1;
		mailboxes.insert(mailbox1);

		initState = new State(3, actor_set, mailboxes);

		initState->initialState = true;
		UnfoldingEvent *e = new UnfoldingEvent();
		e->appState = *initState;

		EventSet emptyS;
		std::list<EventSet> maxEvtHistory;
		maxEvtHistory.push_back(emptyS);
		UC.explore(C, maxEvtHistory, D, A, e, prev_exC, actor_set);
	}
		break;

	case 4: { //the fourth example
		Transition t1(1, 0);
		Transition t2(1, 0);
		Transition t3(1, 0);

		std::array<Transition, 30> trans1, trans2, trans3;
		trans1[0] = t1;
		trans2[0] = t2;
		trans3[0] = t3;
		Actor actor1(1, 1, trans1);
		Actor actor2(2, 1, trans2);
		Actor actor3(3, 1, trans3);

		actor_set.insert(actor1);
		actor_set.insert(actor2);
		actor_set.insert(actor3);

		Mailbox mailbox1;
		mailboxes.insert(mailbox1);

		initState = new State(3, actor_set, mailboxes);

		initState->initialState = true;
		UnfoldingEvent *e = new UnfoldingEvent();
		e->appState = *initState;

		EventSet emptyS;
		std::list<EventSet> maxEvtHistory;
		maxEvtHistory.push_back(emptyS);
		UC.explore(C, maxEvtHistory, D, A, e, prev_exC, actor_set);
	}
		break;

	case 5: { // the fifth example
		Transition t1(1, 0);
		Transition t2(1, 1);

		Transition t3(1, 0);
		Transition t4(1, 1);

		std::array<Transition, 30> trans1, trans2, trans3;
		trans1[0] = t1;
		trans1[1] = t2;

		trans2[0] = t3;
		trans2[1] = t4;
		Actor actor1(1, 2, trans1);
		Actor actor2(2, 2, trans2);

		actor_set.insert(actor1);
		actor_set.insert(actor2);

		Mailbox mailbox1;
		mailboxes.insert(mailbox1);

		initState = new State(2, actor_set, mailboxes);

		initState->initialState = true;
		UnfoldingEvent *e = new UnfoldingEvent();
		e->appState = *initState;

		EventSet emptyS;
		std::list<EventSet> maxEvtHistory;
		maxEvtHistory.push_back(emptyS);
		UC.explore(C, maxEvtHistory, D, A, e, prev_exC, actor_set);

	}
		break;

	case 6: { // 6th example
		Transition t1(1, 0);
		Transition t2(1, 1);

		Transition t3(1, 1);
		Transition t4(1, 0);

		std::array<Transition, 30> trans1, trans2, trans3;
		trans1[0] = t1;
		trans1[1] = t2;

		trans2[0] = t3;
		trans2[1] = t4;
		Actor actor1(1, 2, trans1);
		Actor actor2(2, 2, trans2);

		actor_set.insert(actor1);
		actor_set.insert(actor2);

		Mailbox mailbox1;
		mailboxes.insert(mailbox1);

		initState = new State(2, actor_set, mailboxes);

		initState->initialState = true;
		UnfoldingEvent *e = new UnfoldingEvent();
		e->appState = *initState;

		EventSet emptyS;
		std::list<EventSet> maxEvtHistory;
		maxEvtHistory.push_back(emptyS);
		UC.explore(C, maxEvtHistory, D, A, e, prev_exC, actor_set);
	}
		break;

	case 7: { //7th example
		Transition t1(1, 0);
		Transition t2(1, 1);
		Transition t3(1, 1);
		Transition t4(1, 0);

		std::array<Transition, 30> trans1, trans2, trans3;
		trans1[0] = t1;
		trans2[0] = t2;
		trans3[0] = t3;
		trans3[1] = t4;

		Actor actor1(1, 1, trans1);
		Actor actor2(2, 1, trans2);
		Actor actor3(3, 2, trans3);

		actor_set.insert(actor1);
		actor_set.insert(actor2);
		actor_set.insert(actor3);

		Mailbox mailbox1;
		mailboxes.insert(mailbox1);
		initState = new State(3, actor_set, mailboxes);

		initState->initialState = true;
		UnfoldingEvent *e = new UnfoldingEvent();
		e->appState = *initState;

		EventSet emptyS;
		std::list<EventSet> maxEvtHistory;
		maxEvtHistory.push_back(emptyS);
		UC.explore(C, maxEvtHistory, D, A, e, prev_exC, actor_set);
	}
		break;

	case 8: { // mutex example
		Transition t1(2, 0);
		Transition t2(3, 0);

		Transition t3(2, 0);
		Transition t4(3, 0);

		std::array<Transition, 30> trans1, trans2;
		trans1[0] = t1;
		trans1[1] = t2;

		trans2[0] = t3;
		trans2[1] = t4;
		Actor actor2(2, 2, trans2);
		Actor actor1(1, 2, trans1);

		actor_set.insert(actor1);
		actor_set.insert(actor2);

		Mailbox mailbox1;
		mailboxes.insert(mailbox1);
		initState = new State(2, actor_set, mailboxes);

		initState->initialState = true;
		UnfoldingEvent *e = new UnfoldingEvent();
		e->appState = *initState;

		EventSet emptyS;
		std::list<EventSet> maxEvtHistory;
		maxEvtHistory.push_back(emptyS);
		UC.explore(C, maxEvtHistory, D, A, e, prev_exC, actor_set);
	}
		break;

	case 9: { // mutex example
		Transition t0(0, 0);

		Transition t1(2, 1);
		Transition t2(3, 1);

		Transition t3(2, 1);
		Transition t4(3, 1);

		std::array<Transition, 30> trans1, trans2;
		trans1[0] = t0;
		trans1[1] = t1;
		trans1[2] = t2;

		trans2[0] = t3;
		trans2[1] = t4;
		Actor actor1(1, 3, trans1);

		Actor actor2(2, 2, trans2);

		actor_set.insert(actor1);
		actor_set.insert(actor2);

		Mailbox mailbox1;
		mailboxes.insert(mailbox1);
		initState = new State(2, actor_set, mailboxes);

		initState->initialState = true;
		UnfoldingEvent *e = new UnfoldingEvent();
		e->appState = *initState;

		EventSet emptyS;
		std::list<EventSet> maxEvtHistory;
		maxEvtHistory.push_back(emptyS);
		UC.explore(C, maxEvtHistory, D, A, e, prev_exC, actor_set);
	}
		break;

	case 10: {
		Transition t1(1, 0);
		Transition t2(1, 0);

		Transition t3(1, 1);
		Transition t4(1, 0);

		std::array<Transition, 30> trans1, trans2, trans3;
		trans1[0] = t1;
		trans1[1] = t2;

		trans2[0] = t3;
		trans2[1] = t4;
		Actor actor1(1, 2, trans1);
		Actor actor2(2, 2, trans2);

		actor_set.insert(actor1);
		actor_set.insert(actor2);

		Mailbox mailbox1;
		mailboxes.insert(mailbox1);
		initState = new State(2, actor_set, mailboxes);

		initState->initialState = true;
		UnfoldingEvent *e = new UnfoldingEvent();
		e->appState = *initState;

		EventSet emptyS;
		std::list<EventSet> maxEvtHistory;
		maxEvtHistory.push_back(emptyS);
		UC.explore(C, maxEvtHistory, D, A, e, prev_exC, actor_set);
	}
		break;

	case 11: { // the first simix model -> 2 traces

		//transition (maiboxid, commid, type)

		Transition t1(1, 1, "Isend");
		Transition t2(1, 1, "Wait");
		Transition t3(1, 1, "Isend");
		Transition t4(1, 1, "Ireceive");

		std::array<Transition, 30> trans1, trans2, trans3;
		trans1[0] = t1;
		trans1[1] = t2;

		trans2[0] = t3;
		trans3[0] = t4;

		Actor actor1(1, 2, trans1);
		Actor actor2(2, 1, trans2);
		Actor actor3(3, 1, trans3);

		actor_set.insert(actor1);
		actor_set.insert(actor2);
		actor_set.insert(actor3);

		Mailbox mailbox1;
		mailbox1.id = 1;
		mailboxes.insert(mailbox1);

		initState = new State(3, actor_set, mailboxes);

		initState->initialState = true;
		UnfoldingEvent *e = new UnfoldingEvent();
		e->appState = *initState;

		EventSet emptyS;
		std::list<EventSet> maxEvtHistory;
		maxEvtHistory.push_back(emptyS);
		UC.explore(C, maxEvtHistory, D, A, e, prev_exC, actor_set);

	}
		break;

	case 12: { // the 2nd simix model -> 1 trace

		//transition (maiboxid, commid, type)

		Transition t1(1, 1, "Isend");
		Transition t2(1, 1, "Wait");
		Transition t3(2, 1, "Isend");
		Transition t4(1, 1, "Ireceive");

		std::array<Transition, 30> trans1, trans2, trans3;
		trans1[0] = t1;
		trans1[1] = t2;

		trans2[0] = t3;
		trans3[0] = t4;

		Actor actor1(1, 2, trans1);
		Actor actor2(2, 1, trans2);
		Actor actor3(3, 1, trans3);

		actor_set.insert(actor1);
		actor_set.insert(actor2);
		actor_set.insert(actor3);

		Mailbox mailbox1;
		mailbox1.id = 1;

		Mailbox mailbox2;
		mailbox2.id = 2;

		mailboxes.insert(mailbox1);
		mailboxes.insert(mailbox2);

		initState = new State(3, actor_set, mailboxes);

		initState->initialState = true;
		UnfoldingEvent *e = new UnfoldingEvent();
		e->appState = *initState;

		EventSet emptyS;
		std::list<EventSet> maxEvtHistory;
		maxEvtHistory.push_back(emptyS);
		UC.explore(C, maxEvtHistory, D, A, e, prev_exC, actor_set);

	}
		break;

	case 13: { // the first simix model -> 2 traces

		//transition (maiboxid, commid, type)

		Transition t1(1, 1, "Isend");
		Transition t2(1, 1, "Wait");

		Transition t3(1, 1, "Isend");
		Transition t4(1, 1, "Wait");

		Transition t5(1, 1, "Ireceive");
		Transition t6(1, 1, "Wait");

		std::array<Transition, 30> trans1, trans2, trans3;
		trans1[0] = t1;
		trans1[1] = t2;

		trans2[0] = t3;
		trans2[1] = t4;

		trans3[0] = t5;
		trans3[1] = t6;

		//Actor(id, number of Transition, transition array )

		Actor actor1(1, 2, trans1);
		Actor actor2(2, 2, trans2);
		Actor actor3(3, 2, trans3);

		actor_set.insert(actor1);
		actor_set.insert(actor2);
		actor_set.insert(actor3);

		Mailbox mailbox1;
		mailbox1.id = 1;
		mailboxes.insert(mailbox1);

		initState = new State(3, actor_set, mailboxes);

		initState->initialState = true;
		UnfoldingEvent *e = new UnfoldingEvent();
		e->appState = *initState;

		EventSet emptyS;
		std::list<EventSet> maxEvtHistory;
		maxEvtHistory.push_back(emptyS);
		UC.explore(C, maxEvtHistory, D, A, e, prev_exC, actor_set);

	}
		break;

	case 14: { // the first simix model -> 2 traces

		//transition (maiboxid, commid, type)

		Transition t1(1, 1, "Isend");
		Transition t2(1, 1, "Wait");

		Transition t3(1, 1, "Isend");
		Transition t4(1, 1, "Wait");

		Transition t5(1, 1, "Ireceive");
		Transition t6(1, 1, "Wait");

		Transition t7(1, 1, "Ireceive");
		Transition t8(1, 1, "Wait");

		std::array<Transition, 30> trans1, trans2, trans3;
		trans1[0] = t1;
		trans1[1] = t2;

		trans2[0] = t3;
		trans2[1] = t4;

		trans3[0] = t5;
		trans3[1] = t6;

		trans3[2] = t7;
		trans3[3] = t8;

		//Actor(id, number of Transition, transition array )

		Actor actor1(1, 2, trans1);
		Actor actor2(2, 2, trans2);
		Actor actor3(3, 4, trans3);

		actor_set.insert(actor1);
		actor_set.insert(actor2);
		actor_set.insert(actor3);

		Mailbox mailbox1;
		mailbox1.id = 1;
		mailboxes.insert(mailbox1);

		initState = new State(3, actor_set, mailboxes);

		initState->initialState = true;
		UnfoldingEvent *e = new UnfoldingEvent();
		e->appState = *initState;

		EventSet emptyS;
		std::list<EventSet> maxEvtHistory;
		maxEvtHistory.push_back(emptyS);
		UC.explore(C, maxEvtHistory, D, A, e, prev_exC, actor_set);

	}
		break;

	case 15: { // the first simix model -> 6 traces

		//transition (maiboxid, commid, type)

		Transition t1(1, 1, "Isend");
		Transition t2(1, 1, "Wait");

		Transition t3(1, 1, "Isend");
		Transition t4(1, 1, "Wait");

		Transition t5(1, 1, "Ireceive");
		Transition t6(1, 1, "Wait");

		Transition t7(1, 1, "Ireceive");
		Transition t8(1, 1, "Wait");

		Transition t9(1, 1, "Isend");
		Transition t10(1, 1, "Wait");

		std::array<Transition, 30> trans1, trans2, trans3, trans4;
		trans1[0] = t1;
		trans1[1] = t2;

		trans2[0] = t3;
		trans2[1] = t4;

		trans3[0] = t5;
		trans3[1] = t6;

		trans3[2] = t7;
		trans3[3] = t8;

		trans4[0] = t9;
		trans4[1] = t10;

		//Actor(id, number of Transition, transition array )

		Actor actor1(1, 2, trans1);
		Actor actor2(2, 2, trans2);
		Actor actor3(3, 4, trans3);
		Actor actor4(4, 2, trans3);

		actor_set.insert(actor1);
		actor_set.insert(actor2);
		actor_set.insert(actor3);
		actor_set.insert(actor4);

		Mailbox mailbox1;
		mailbox1.id = 1;
		mailboxes.insert(mailbox1);

		initState = new State(4, actor_set, mailboxes);

		initState->initialState = true;
		UnfoldingEvent *e = new UnfoldingEvent();
		e->appState = *initState;

		EventSet emptyS;
		std::list<EventSet> maxEvtHistory;
		maxEvtHistory.push_back(emptyS);
		UC.explore(C, maxEvtHistory, D, A, e, prev_exC, actor_set);

	}
		break;

	case 16: { // the first simix model -> 6 traces

		//transition (maiboxid, commid, type)
		Transition t1(1, 1, "Ireceive");
		Transition t2(1, 1, "Wait");

		Transition t3(1, 2, "Ireceive");
		Transition t4(1, 2, "Wait");

		Transition t5(1, 3, "Ireceive");
		Transition t6(1, 3, "Wait");

		Transition t7(1, 1, "Isend");
		Transition t8(1, 1, "Wait");

		Transition t9(1, 1, "Isend");
		Transition t10(1, 1, "Wait");

		Transition t11(1, 1, "Isend");
		Transition t12(1, 1, "Wait");

		std::array<Transition, 30> trans1, trans2, trans3, trans4;
		trans1[0] = t1;
		trans1[1] = t2;
		trans1[2] = t3;
		trans1[3] = t4;
		trans1[4] = t5;
		trans1[5] = t6;

		trans2[0] = t7;
		trans2[1] = t8;

		trans3[0] = t9;
		trans3[1] = t10;

		trans4[0] = t11;
		trans4[1] = t12;

		//Actor(id, number of Transition, transition array )

		Actor actor1(1, 6, trans1);
		Actor actor2(2, 2, trans2);
		Actor actor3(3, 2, trans3);
		Actor actor4(4, 2, trans3);

		actor_set.insert(actor1);
		actor_set.insert(actor2);
		actor_set.insert(actor3);
		actor_set.insert(actor4);

		Mailbox mailbox1;
		mailbox1.id = 1;


		mailboxes.insert(mailbox1);
		//mailboxes.insert(mailbox2);
		//mailboxes.insert(mailbox3);

		initState = new State(4, actor_set, mailboxes);

		initState->initialState = true;
		UnfoldingEvent *e = new UnfoldingEvent();
		e->appState = *initState;

		EventSet emptyS;
		std::list<EventSet> maxEvtHistory;
		maxEvtHistory.push_back(emptyS);
		UC.explore(C, maxEvtHistory, D, A, e, prev_exC, actor_set);

	}
		break;

		// INCLUDING TEST ACTION

	case 17: { //  3 traces

		//transition (maiboxid, commid, type)

		Transition t1(1, 1, "Isend");
		Transition t2(1, 1, "Test");

		Transition t3(1, 1, "Isend");

		Transition t4(1, 1, "Ireceive");

		std::array<Transition, 30> trans1, trans2, trans3;
		trans1[0] = t1;
		trans1[1] = t2;

		trans2[0] = t3;
		trans3[0] = t4;

		Actor actor2(2, 2, trans1);
		Actor actor1(1, 1, trans2);
		Actor actor3(3, 1, trans3);

		actor_set.insert(actor1);
		actor_set.insert(actor2);
		actor_set.insert(actor3);

		Mailbox mailbox1;
		mailbox1.id = 1;

		Mailbox mailbox2;
		mailbox2.id = 2;

		mailboxes.insert(mailbox1);
		mailboxes.insert(mailbox2);

		initState = new State(3, actor_set, mailboxes);

		initState->initialState = true;
		UnfoldingEvent *e = new UnfoldingEvent();
		e->appState = *initState;

		EventSet emptyS;
		std::list<EventSet> maxEvtHistory;
		maxEvtHistory.push_back(emptyS);
		UC.explore(C, maxEvtHistory, D, A, e, prev_exC, actor_set);

	}
		break;


	case 18: { //18 traces

		//transition (maiboxid, commid, type)
		Transition t1(1, 1, "Ireceive");
		Transition t2(1, 1, "Test");

		Transition t3(1, 2, "Ireceive");
		Transition t4(1, 2, "Test");

		Transition t5(1, 3, "Ireceive");
		Transition t6(1, 3, "Test");

		Transition t7(1, 1, "Isend");
		Transition t8(1, 1, "Test");

		Transition t9(1, 1, "Isend");
		Transition t10(1, 1, "Test");

		Transition t11(1, 1, "Isend");
		Transition t12(1, 1, "Test");

		std::array<Transition, 30> trans1, trans2, trans3, trans4;
		trans1[0] = t1;
		trans1[1] = t2;
		trans1[2] = t3;
		trans1[3] = t4;
		trans1[4] = t5;
		trans1[5] = t6;

		trans2[0] = t7;
		trans2[1] = t8;

		trans3[0] = t9;
		trans3[1] = t10;

		trans4[0] = t11;
		trans4[1] = t12;

		//Actor(id, number of Transition, transition array )

		Actor actor1(1, 6, trans1);
		Actor actor2(2, 2, trans2);
		Actor actor3(3, 2, trans3);
		Actor actor4(4, 2, trans3);

		actor_set.insert(actor1);
		actor_set.insert(actor2);
		actor_set.insert(actor3);
		actor_set.insert(actor4);

		Mailbox mailbox1;
		mailbox1.id = 1;


		mailboxes.insert(mailbox1);
		//mailboxes.insert(mailbox2);
		//mailboxes.insert(mailbox3);

		initState = new State(4, actor_set, mailboxes);

		initState->initialState = true;
		UnfoldingEvent *e = new UnfoldingEvent();
		e->appState = *initState;



		EventSet emptyS;
		std::list<EventSet> maxEvtHistory;
		maxEvtHistory.push_back(emptyS);


		UC.explore(C, maxEvtHistory, D, A, e, prev_exC, actor_set);

	}
		break;

	case 19: { // 6 traces

			//transition (maiboxid, commid, type)
			Transition t1(1, 1, "Ireceive");
			Transition t2(1, 1, "Test");



			Transition t7(1, 1, "Isend");
			Transition t8(1, 1, "Test");

			Transition t9(1, 1, "Isend");
			Transition t10(1, 1, "Test");



			std::array<Transition, 30> trans1, trans2, trans3, trans4;
			trans1[0] = t1;
			trans1[1] = t2;



			trans2[0] = t7;
			trans2[1] = t8;

			trans3[0] = t9;
			trans3[1] = t10;



			//Actor(id, number of Transition, transition array )

			Actor actor1(1, 2, trans1);
			Actor actor2(2, 2, trans2);
			Actor actor3(3, 2, trans3);

			actor_set.insert(actor1);
			actor_set.insert(actor2);
			actor_set.insert(actor3);

			Mailbox mailbox1;
			mailbox1.id = 1;



			mailboxes.insert(mailbox1);
			//mailboxes.insert(mailbox2);
			//mailboxes.insert(mailbox3);

			initState = new State(3, actor_set, mailboxes);

			initState->initialState = true;
			UnfoldingEvent *e = new UnfoldingEvent();
			e->appState = *initState;


			EventSet emptyS;
			std::list<EventSet> maxEvtHistory;
			maxEvtHistory.push_back(emptyS);


			UC.explore(C, maxEvtHistory, D, A, e, prev_exC, actor_set);

		}
			break;

	case 20: { // 6 traces

			//transition (maiboxid, commid, type)
			Transition t1(1, 1, "Ireceive");
			Transition t2(1, 1, "Test");

			Transition t3(1, 2, "Ireceive");
			Transition t4(1, 2, "Test");


			Transition t7(1, 1, "Isend");
			Transition t8(1, 1, "Test");

			Transition t9(1, 1, "Isend");
			Transition t10(1, 1, "Test");



			std::array<Transition, 30> trans1, trans2, trans3, trans4;
			trans1[0] = t1;
			trans1[1] = t2;
			trans1[2] = t3;
			trans1[3] = t4;

			trans2[0] = t7;
			trans2[1] = t8;

			trans3[0] = t9;
			trans3[1] = t10;



			//Actor(id, number of Transition, transition array )

			Actor actor1(1, 4, trans1);
			Actor actor2(2, 2, trans2);
			Actor actor3(3, 2, trans3);
			Actor actor4(4, 2, trans3);

			actor_set.insert(actor1);
			actor_set.insert(actor2);
			actor_set.insert(actor3);

			Mailbox mailbox1;
			mailbox1.id = 1;



			mailboxes.insert(mailbox1);
			//mailboxes.insert(mailbox2);
			//mailboxes.insert(mailbox3);

			initState = new State(3, actor_set, mailboxes);

			initState->initialState = true;
			UnfoldingEvent *e = new UnfoldingEvent();
			e->appState = *initState;


			EventSet emptyS;
			std::list<EventSet> maxEvtHistory;
			maxEvtHistory.push_back(emptyS);

			UC.explore(C, maxEvtHistory, D, A, e, prev_exC, actor_set);

		}
			break;



	case 21: { //18 traces

		//transition (maiboxid, commid, type)
		Transition t1(1, 1, "Ireceive");
		Transition t2(1, 1, "Test");

		Transition t3(1, 2, "Ireceive");
		Transition t4(1, 2, "Test");


		Transition t7(1, 1, "Isend");
		Transition t8(1, 1, "Test");

		Transition t9(1, 1, "Isend");
		Transition t10(1, 1, "Test");

		Transition t11(1, 1, "Isend");
		Transition t12(1, 1, "Test");

		std::array<Transition, 30> trans1, trans2, trans3, trans4;
		trans1[0] = t1;
		trans1[1] = t2;
		trans1[2] = t3;
		trans1[3] = t4;


		trans2[0] = t7;
		trans2[1] = t8;

		trans3[0] = t9;
		trans3[1] = t10;

		trans4[0] = t11;
		trans4[1] = t12;

		//Actor(id, number of Transition, transition array )

		Actor actor1(1, 4, trans1);
		Actor actor2(2, 2, trans2);
		Actor actor3(3, 2, trans3);
		Actor actor4(4, 2, trans3);

		actor_set.insert(actor1);
		actor_set.insert(actor2);
		actor_set.insert(actor3);
		actor_set.insert(actor4);

		Mailbox mailbox1;
		mailbox1.id = 1;


		mailboxes.insert(mailbox1);
		//mailboxes.insert(mailbox2);
		//mailboxes.insert(mailbox3);

		initState = new State(4, actor_set, mailboxes);

		initState->initialState = true;
		UnfoldingEvent *e = new UnfoldingEvent();
		e->appState = *initState;


		EventSet emptyS;
		std::list<EventSet> maxEvtHistory;
		maxEvtHistory.push_back(emptyS);

		UC.explore(C, maxEvtHistory, D, A, e, prev_exC, actor_set);

	}
		break;


	case 22: {

		//transition (maiboxid, commid, type)
		Transition t1(1, 1, "Ireceive");
		Transition t2(1, 1, "Test");

		Transition t3(1, 2, "Ireceive");
		Transition t4(1, 2, "Test");

		Transition t5(1, 3, "Ireceive");
		Transition t6(1, 3, "Test");

		Transition t7(1, 3, "Ireceive");
		Transition t8(1, 3, "Test");

		Transition t9(1, 1, "Isend");
		Transition t10(1, 1, "Test");

		Transition t11(1, 1, "Isend");
		Transition t12(1, 1, "Test");

		Transition t13(1, 1, "Isend");
		Transition t14(1, 1, "Test");

		Transition t15(1, 1, "localComp");
		Transition t16(1, 1, "Isend");
		Transition t17(1, 1, "Test");

		std::array<Transition, 30> trans1, trans2, trans3, trans4, trans5;
		trans1[0] = t1;
		trans1[1] = t2;
		trans1[2] = t3;
		trans1[3] = t4;
		trans1[4] = t5;
		trans1[5] = t6;
		trans1[7] = t7;
		trans1[8] = t8;


		trans2[0] = t9;
		trans2[1] = t10;

		trans3[0] = t11;
		trans3[1] = t12;

		trans4[0] = t13;
		trans4[1] = t14;


		trans5[0] = t15;
		trans5[1] = t16;
		trans5[2] = t17;


		//Actor(id, number of Transition, transition array )

		Actor actor1(1, 8, trans1);
		Actor actor2(2, 2, trans2);
		Actor actor3(3, 2, trans3);
		Actor actor4(4, 2, trans3);
		Actor actor5(5, 3, trans5);


		actor_set.insert(actor1);
		actor_set.insert(actor2);
		actor_set.insert(actor3);
		actor_set.insert(actor4);
		actor_set.insert(actor5);


		Mailbox mailbox1;
		mailbox1.id = 1;


		mailboxes.insert(mailbox1);
		//mailboxes.insert(mailbox2);
		//mailboxes.insert(mailbox3);

		initState = new State(5, actor_set, mailboxes);

		initState->initialState = true;
		UnfoldingEvent *e = new UnfoldingEvent();
		e->appState = *initState;
		IntSet *setInt = new IntSet();

		EventSet emptyS;
		std::list<EventSet> maxEvtHistory;
		maxEvtHistory.push_back(emptyS);

		UC.explore(C, maxEvtHistory, D, A, e, prev_exC, actor_set);

	}
		break;


	case 23: { //18 traces

			//transition (maiboxid, commid, type)
			Transition t1(1, 1, "Ireceive");
			Transition t2(1, 1, "Test");



			Transition t7(1, 1, "Isend");
			Transition t8(1, 1, "Test");

			Transition t9(1, 1, "Isend");
			Transition t10(1, 1, "Test");

			Transition t11(1, 1, "Isend");
			Transition t12(1, 1, "Test");

			std::array<Transition, 30> trans1, trans2, trans3, trans4;
			trans1[0] = t1;
			trans1[1] = t2;


			trans2[0] = t7;
			trans2[1] = t8;

			trans3[0] = t9;
			trans3[1] = t10;

			trans4[0] = t11;
			trans4[1] = t12;

			//Actor(id, number of Transition, transition array )

			Actor actor1(1, 2, trans1);
			Actor actor2(2, 2, trans2);
			Actor actor3(3, 2, trans3);
			Actor actor4(4, 2, trans3);

			actor_set.insert(actor1);
			actor_set.insert(actor2);
			actor_set.insert(actor3);
			actor_set.insert(actor4);

			Mailbox mailbox1;
			mailbox1.id = 1;


			mailboxes.insert(mailbox1);
			//mailboxes.insert(mailbox2);
			//mailboxes.insert(mailbox3);

			initState = new State(4, actor_set, mailboxes);

			initState->initialState = true;
			UnfoldingEvent *e = new UnfoldingEvent();
			e->appState = *initState;

			EventSet emptyS;
			std::list<EventSet> maxEvtHistory;
			maxEvtHistory.push_back(emptyS);

			UC.explore(C, maxEvtHistory, D, A, e, prev_exC, actor_set);

		}
			break;



	case 24: { //18 traces

		//transition (maiboxid, commid, type)
				Transition t1(1, 1, "Ireceive");

				Transition t3(1, 2, "Ireceive");
				Transition t4(1, 2, "Test");

				Transition t5(1, 3, "Isend");

				Transition t7(1, 4, "localComp");
				Transition t8(1, 4, "Isend");



				std::array<Transition, 30> trans1, trans2, trans3, trans4, trans5;
				trans1[0] = t1;

				trans2[0] = t3;
				trans2[1] = t4;



				trans3[0] = t5;

				trans4[0] = t7;
				trans4[1] = t8;



				//Actor(id, number of Transition, transition array )

				Actor actor1(1, 1, trans1);

				Actor actor2(2, 2, trans2);

				Actor actor3(3, 1, trans3);
				Actor actor4(4, 2, trans4);


				actor_set.insert(actor1);
				actor_set.insert(actor2);
				actor_set.insert(actor3);
				actor_set.insert(actor4);


				Mailbox mailbox1;
				mailbox1.id = 1;


				mailboxes.insert(mailbox1);
				//mailboxes.insert(mailbox2);
				//mailboxes.insert(mailbox3);

				initState = new State(4, actor_set, mailboxes);

				initState->initialState = true;
				UnfoldingEvent *e = new UnfoldingEvent();
				e->appState = *initState;
				IntSet *setInt = new IntSet();

				EventSet emptyS;
				std::list<EventSet> maxEvtHistory;
				maxEvtHistory.push_back(emptyS);

				UC.explore(C, maxEvtHistory, D, A, e, prev_exC, actor_set);

		}
			break;


	case 25: { //

				//transition (maiboxid, commid, type)

				Transition t1(0, 0, "localComp");

				// Master sends subtask to all clients

				Transition t2(2, 1, "Isend");
				Transition t3(2, 1, "Wait");

				Transition t4(3, 2, "Isend");
				Transition t5(3, 2, "Wait");

				Transition t6(4, 3, "Isend");
				Transition t7(4, 3, "Wait");

				// Master receives subtask to all clients

				Transition t8(1, 4, "Ireceive");
				Transition t9(1, 4, "Wait");

				Transition t10(1, 5, "Ireceive");
				Transition t11(1, 5, "Wait");

				Transition t12(1, 6, "Ireceive");
				Transition t13(1, 6, "Wait");

				Transition t14(0, 0, "localComp");


				// client receives a subtask from the master
				//transition (maiboxid, commid, type)

				Transition t15(2, 1, "Ireceive");
				Transition t16(2, 1, "Wait");
				// after that he computes
				Transition t17(0, 0, "localComp");
				// then send back to the master
				Transition t18(1, 2, "Isend");
				Transition t19(1, 2, "Wait");

				// the same process for other clients

				Transition t20(3, 1, "Ireceive");
				Transition t21(3, 1, "Wait");
				// after that he computes
				Transition t22(0, 0, "localComp");
				// then send back to the master
				Transition t23(1, 2, "Isend");
				Transition t24(1, 2, "Wait");


				Transition t25(4, 1, "Ireceive");
				Transition t26(4, 1, "Wait");
				// after that he computes
				Transition t27(0, 0, "localComp");
				// then send back to the master
				Transition t28(1, 2, "Isend");
				Transition t29(1, 2, "Wait");

				std::array<Transition, 30> trans1, trans2, trans3, trans4;
				trans1[0] = t1;
				trans1[1] = t2;
				trans1[2] = t3;
				trans1[3] = t4;
				trans1[4] = t5;
				trans1[5] = t6;
				trans1[6] = t7;
				trans1[7] = t8;
				trans1[8] = t9;
				trans1[9] = t10;
				trans1[10] = t11;
				trans1[11] = t12;
				trans1[12] = t13;
				trans1[13] = t14;




				trans2[0] = t15;
				trans2[1] = t16;
				trans2[2] = t17;
				trans2[3] = t18;
				trans2[4] = t19;



				trans3[0] = t20;
				trans3[1] = t21;
				trans3[2] = t22;
				trans3[3] = t23;
				trans3[4] = t24;


				trans4[0] = t25;
				trans4[1] = t26;
				trans4[2] = t27;
				trans4[3] = t28;
				trans4[4] = t29;

				//Actor(id, number of Transition, transition array )

				Actor actor1(1, 14, trans1);
				Actor actor2(2, 5, trans2);
				Actor actor3(3, 5, trans3);
				Actor actor4(4, 5, trans4);

				actor_set.insert(actor1);
				actor_set.insert(actor2);
				actor_set.insert(actor3);
				actor_set.insert(actor4);

				Mailbox mailbox1,mailbox2,mailbox3,mailbox4;
				mailbox1.id = 1;
				mailbox2.id = 2;
				mailbox3.id = 3;
				mailbox4.id = 4;




				mailboxes.insert(mailbox1);
				mailboxes.insert(mailbox2);
				mailboxes.insert(mailbox3);
				mailboxes.insert(mailbox4);

				initState = new State(4, actor_set, mailboxes);

				initState->initialState = true;
				UnfoldingEvent *e = new UnfoldingEvent();
				e->appState = *initState;

				EventSet emptyS;
				std::list<EventSet> maxEvtHistory;
				maxEvtHistory.push_back(emptyS);
				UC.explore(C, maxEvtHistory, D, A, e, prev_exC, actor_set);


				std::cout<<"\n explore full state space :\n";

				State initState1(4, actor_set, mailboxes);
				initState1.initialState = true;
				stateStack.push_back(initState1);
				//exhautiveExplore(stateStack,transList);



			}
				break;

	case 26: { //  master- slaver

					//transition (maiboxid, commid, type)

					//Transition t1(0, 0, "localComp");

					// Master sends subtask to all clients

					Transition t0(2, 1, "Isend");
					Transition t1(2, 1, "Wait");

					Transition t2(3, 2, "Isend");
					Transition t3(3, 2, "Wait");


					// Master receives subtask to all clients

					Transition t4(1, 4, "Ireceive");
					Transition t5(1, 4, "Wait");

					Transition t6(1, 5, "Ireceive");
					Transition t7(1, 5, "Wait");

					//Transition t10(0, 0, "localComp");


					// client receives a subtask from the master
					//transition (maiboxid, commid, type)

					Transition t15(2, 1, "Ireceive");
					Transition t16(2, 1, "Wait");
					// after that he computes
					Transition t17(0, 0, "localComp");
					// then send back to the master
					Transition t18(1, 2, "Isend");
					Transition t19(1, 2, "Wait");

					// the same process for other clients

					Transition t20(3, 1, "Ireceive");
					Transition t21(3, 1, "Wait");
					// after that he computes
					Transition t22(0, 0, "localComp");
					// then send back to the master
					Transition t23(1, 2, "Isend");
					Transition t24(1, 2, "Wait");




					std::array<Transition, 30> trans1, trans2, trans3, trans4;
					trans1[0] = t0;
					trans1[1] = t1;
					trans1[2] = t2;
					trans1[3] = t3;
					trans1[4] = t4;
					trans1[5] = t5;
					trans1[6] = t6;
					trans1[7] = t7;




					trans2[0] = t15;
					trans2[1] = t16;
					trans2[2] = t17;
					trans2[3] = t18;
					trans2[4] = t19;



					trans3[0] = t20;
					trans3[1] = t21;
					trans3[2] = t22;
					trans3[3] = t23;
					trans3[4] = t24;



					//Actor(id, number of Transition, transition array )

					Actor actor1(1, 8, trans1);
					Actor actor2(2, 5, trans2);
					Actor actor3(3, 5, trans3);

					actor_set.insert(actor1);
					actor_set.insert(actor2);
					actor_set.insert(actor3);

					Mailbox mailbox1,mailbox2,mailbox3,mailbox4;
					mailbox1.id = 1;
					mailbox2.id = 2;
					mailbox3.id = 3;




					mailboxes.insert(mailbox1);
					mailboxes.insert(mailbox2);
					mailboxes.insert(mailbox3);

					initState = new State(3, actor_set, mailboxes);

					initState->initialState = true;
					UnfoldingEvent *e = new UnfoldingEvent();
					e->appState = *initState;

					EventSet emptyS;
					std::list<EventSet> maxEvtHistory;
					maxEvtHistory.push_back(emptyS);
					//UC.explore(C, maxEvtHistory, D, A, e, prev_exC, actor_set);


					std::cout<<"\n explore full state space :\n";

					State initState1(4, actor_set, mailboxes);
					initState1.initialState = true;
					stateStack.push_back(initState1);
					exhautiveExplore(stateStack,transList);



				}
					break;

	case 27: { // the first simix model -> 2 traces

			//transition (maiboxid, commid, type)

			Transition t1(1, 1, "Isend");
			Transition t2(1, 1, "Wait");


			Transition t5(1, 1, "Ireceive");
			Transition t6(1, 1, "Wait");

			std::array<Transition, 30> trans1, trans2, trans3;
			trans1[0] = t1;
			trans1[1] = t2;


			trans2[0] = t5;
			trans2[1] = t6;

			//Actor(id, number of Transition, transition array )

			Actor actor1(1, 2, trans1);
			Actor actor2(2, 2, trans2);

			actor_set.insert(actor1);
			actor_set.insert(actor2);

			Mailbox mailbox1;
			mailbox1.id = 1;
			mailboxes.insert(mailbox1);

			initState = new State(2, actor_set, mailboxes);

			initState->initialState = true;
			UnfoldingEvent *e = new UnfoldingEvent();
			e->appState = *initState;

			EventSet emptyS;
			std::list<EventSet> maxEvtHistory;
			maxEvtHistory.push_back(emptyS);
			UC.explore(C, maxEvtHistory, D, A, e, prev_exC, actor_set);

			std::cout<<"\n explore full state space :\n";

			State initState1(4, actor_set, mailboxes);
			initState1.initialState = true;
			stateStack.push_back(initState1);
			exhautiveExplore(stateStack,transList);




		}
			break;

	case 28: { // dtg benchmark

						//transition (maiboxid, commid, type)
						//node 0
						Transition t0(1, 1, "Ireceive");
						Transition t1(1, 1, "Wait");

						Transition t2(5, 2, "Isend");
						Transition t3(5, 2, "Wait");

						Transition t4(1, 3, "Ireceive");
						Transition t5(1, 3, "Wait");

						// node1

						Transition t6(1, 1, "Isend");
						Transition t7(1, 1, "Wait");


						Transition t8(4, 2, "Isend");
						Transition t9(4, 2, "Wait");

						//node 2
						Transition t10(3, 1, "Ireceive");
						Transition t11(3, 1, "Wait");

						Transition t12(1, 2, "Isend");
						Transition t13(1, 2, "Wait");

						//node 3

						Transition t14(4, 1, "Ireceive");
						Transition t15(4, 1, "Wait");

						Transition t16(5, 2, "Ireceive");
						Transition t17(5, 2, "Wait");


						// node 5


						Transition t18(3, 1, "Isend");
						Transition t19(3, 1, "Wait");




						std::array<Transition, 30> trans1, trans2, trans3, trans4,trans5 ;
						trans1[0] = t0;
						trans1[1] = t1;
						trans1[2] = t2;
						trans1[3] = t3;
						trans1[4] = t4;
						trans1[5] = t5;



						trans2[0] = t6;
						trans2[1] = t7;
						trans2[2] = t8;
						trans2[3] = t9;



						trans3[0] = t10;
						trans3[1] = t11;
						trans3[2] = t12;
						trans3[3] = t13;


						trans4[0] = t14;
						trans4[1] = t15;
						trans4[2] = t16;
						trans4[3] = t17;

						trans5[0] = t18;
						trans5[1] = t19;


						//Actor(id, number of Transition, transition array )

						Actor actor1(1, 6, trans1);
						Actor actor2(2, 4, trans2);
						Actor actor3(3, 4, trans3);
						Actor actor4(4, 4, trans4);
						Actor actor5(5, 2, trans5);

						actor_set.insert(actor1);
						actor_set.insert(actor2);
						actor_set.insert(actor3);
						actor_set.insert(actor4);
						actor_set.insert(actor5);


						Mailbox mailbox1,mailbox2,mailbox3,mailbox4, mailbox5 ;
						mailbox1.id = 1;
						mailbox2.id = 2;
						mailbox3.id = 3;
						mailbox4.id = 4;
						mailbox5.id = 5;



						mailboxes.insert(mailbox1);
						mailboxes.insert(mailbox2);
						mailboxes.insert(mailbox3);
						mailboxes.insert(mailbox4);
						mailboxes.insert(mailbox5);

						initState = new State(5, actor_set, mailboxes);

						initState->initialState = true;
						UnfoldingEvent *e = new UnfoldingEvent();
						e->appState = *initState;

						EventSet emptyS;
						std::list<EventSet> maxEvtHistory;
						maxEvtHistory.push_back(emptyS);
						UC.explore(C, maxEvtHistory, D, A, e, prev_exC, actor_set);


						std::cout<<"\n explore full state space :\n";

						State initState1(5, actor_set, mailboxes);
						initState1.initialState = true;
						stateStack.push_back(initState1);
						//exhautiveExplore(stateStack,transList);



					}
						break;

	case 29: { /*		complex-deadlock
  if (nprocs < 3)
    {
      printf ("not enough tasks\n");
    }
  else if (rank == 0)
    {
      memset (buf0, 0, buf_size);

      zero_to_two = 1;

      MPI_Send (&zero_to_two, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);

      MPI_Recv (buf1, buf_size, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);

      MPI_Send (buf0, buf_size, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }
  else if (rank == 1)
    {
      memset (buf1, 1, buf_size);

      MPI_Recv (buf0, buf_size, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

      MPI_Send (buf1, buf_size, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
  else if (rank == 2)
    {

      MPI_Recv (&zero_to_two, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    } */
		//transition (maiboxid, commid, type)
			//node 0


			Transition t0(2, 1, "Isend");
			Transition t1(2, 1, "Wait");

			Transition t2(0, 2, "Ireceive");
			Transition t3(0, 2, "Wait");

			Transition t4(1, 3, "Isend");
			Transition t5(1, 3, "Wait");


			// node1

			Transition t6(1, 1, "Ireceive");
			Transition t7(1, 1, "Wait");

			Transition t8(0, 2, "Isend");
			Transition t9(0, 2, "Wait");

			//node 2
			Transition t10(2, 1, "Ireceive");
			Transition t11(2, 1, "Wait");







			std::array<Transition, 30> trans1, trans2, trans3, trans4,trans5 ;
			trans1[0] = t0;
			trans1[1] = t1;
			trans1[2] = t2;
			trans1[3] = t3;
			trans1[4] = t4;
			trans1[5] = t5;



			trans2[0] = t6;
			trans2[1] = t7;
			trans2[2] = t8;
			trans2[3] = t9;



			trans3[0] = t10;
			trans3[1] = t11;



			//Actor(id, number of Transition, transition array )

			Actor actor1(1, 6, trans1);
			Actor actor2(2, 4, trans2);
			Actor actor3(3, 2, trans3);


			actor_set.insert(actor1);
			actor_set.insert(actor2);
			actor_set.insert(actor3);


			Mailbox mailbox0,mailbox1,mailbox2;
			mailbox0.id = 0;
			mailbox1.id = 1;
			mailbox2.id = 2;



			mailboxes.insert(mailbox0);
			mailboxes.insert(mailbox1);
			mailboxes.insert(mailbox2);


			initState = new State(3, actor_set, mailboxes);

			initState->initialState = true;
			UnfoldingEvent *e = new UnfoldingEvent();
			e->appState = *initState;

			EventSet emptyS;
			std::list<EventSet> maxEvtHistory;
			maxEvtHistory.push_back(emptyS);
		UC.explore(C, maxEvtHistory, D, A, e, prev_exC, actor_set);


			std::cout<<"\n explore full state space :\n";

			State initState1(3, actor_set, mailboxes);
			initState1.initialState = true;
			stateStack.push_back(initState1);
			//exhautiveExplore(stateStack,transList);



						}
							break;

	case 30: { /*		wait-deadlock
if (nprocs < 2)
    {
      printf ("not enough tasks\n");
    }
  else if (rank == 0)
    {
      memset (buf0, 0, buf_size);

      MPI_Irecv (buf1, buf_size, MPI_INT, 1, 0, MPI_COMM_WORLD, &req);

      MPI_Wait (&req, &status);

      MPI_Send (buf0, buf_size, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }
  else if (rank == 1)
    {
      memset (buf1, 1, buf_size);

      MPI_Irecv (buf0, buf_size, MPI_INT, 0, 0, MPI_COMM_WORLD, &req);

      MPI_Wait (&req, &status);

      MPI_Send (buf1, buf_size, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
*/
		//transition (maiboxid, commid, type)
			//node 0
			Transition t0(0, 1, "Ireceive");
			Transition t1(0, 1, "Wait");


			Transition t2(1, 2, "Isend");
			Transition t3(1, 2, "Wait");


			// node1

			Transition t4(1, 1, "Ireceive");
			Transition t5(1, 1, "Wait");

			Transition t6(0, 2, "Isend");
			Transition t7(0, 2, "Wait");




			std::array<Transition, 30> trans1, trans2, trans3, trans4,trans5 ;
			trans1[0] = t0;
			trans1[1] = t1;
			trans1[2] = t2;
			trans1[3] = t3;



			trans2[0] = t4;
			trans2[1] = t5;
			trans2[2] = t6;
			trans2[3] = t7;




			//Actor(id, number of Transition, transition array )

			Actor actor1(1, 4, trans1);
			Actor actor2(2, 4, trans2);


			actor_set.insert(actor1);
			actor_set.insert(actor2);


			Mailbox mailbox0,mailbox1,mailbox2;
			mailbox0.id = 0;
			mailbox1.id = 1;



			mailboxes.insert(mailbox0);
			mailboxes.insert(mailbox1);


			initState = new State(2, actor_set, mailboxes);

			initState->initialState = true;
			UnfoldingEvent *e = new UnfoldingEvent();
			e->appState = *initState;

			EventSet emptyS;
			std::list<EventSet> maxEvtHistory;
			maxEvtHistory.push_back(emptyS);
			//UC.explore(C, maxEvtHistory, D, A, e, prev_exC, actor_set);


			std::cout<<"\n explore full state space :\n";

			State initState1(3, actor_set, mailboxes);
			initState1.initialState = true;
			stateStack.push_back(initState1);
			exhautiveExplore(stateStack,transList);

						}
							break;

	case 31: { /*		waitall-deadlock
 if (nprocs < 3)
    {
      printf ("not enough tasks\n");
    }
  else if (rank == 0)
    {
      MPI_Irecv (buf0, buf_size, MPI_INT, 1, 0, MPI_COMM_WORLD, &reqs[0]);

      MPI_Irecv (buf1, buf_size, MPI_INT, 1, 0, MPI_COMM_WORLD, &reqs[1]);

      MPI_Waitall (2, reqs, statuses);

      MPI_Send (buf1, buf_size, MPI_INT, 1, 1, MPI_COMM_WORLD);
    }
  else if (rank == 1)
    {
      memset (buf0, 0, buf_size);

      MPI_Isend (buf0, buf_size, MPI_INT, 0, 0, MPI_COMM_WORLD, &reqs[0]);

      MPI_Isend (buf0, buf_size, MPI_INT, 2, 1, MPI_COMM_WORLD, &reqs[1]);

      MPI_Waitall (2, reqs, statuses);

      MPI_Recv (buf1, buf_size, MPI_INT, 0, 1, MPI_COMM_WORLD, statuses);

      MPI_Send (buf0, buf_size, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
  else if (rank == 2)
    {
      MPI_Recv (buf1, buf_size, MPI_INT, 1, 1, MPI_COMM_WORLD, statuses);
    }
 */
		//transition (maiboxid, commid, type)
			//node 0



			Transition t0(0, 1, "Ireceive");
			Transition t1(0, 2, "Ireceive");

			Transition t2(0, 1, "Wait");
			Transition t3(0, 2, "Wait");

			Transition t4(1, 3, "Isend");
			Transition t5(1, 3, "Wait");


			// node1


			Transition t6(0, 1, "Isend");
			Transition t7(2, 2, "Isend");

			Transition t8(0, 1, "Wait");
			Transition t9(2, 2, "Wait");

			Transition t10(1, 3, "Ireceive");
			Transition t11(1, 3, "Wait");

			Transition t12(0, 4, "Isend");
			Transition t13(0, 4, "Wait");


			//node 2
			Transition t14(2, 1, "Ireceive");
			Transition t15(2, 1, "Wait");

			std::array<Transition, 30> trans1, trans2, trans3, trans4,trans5 ;
			trans1[0] = t0;
			trans1[1] = t1;
			trans1[2] = t2;
			trans1[3] = t3;
			trans1[4] = t4;
			trans1[5] = t5;



			trans2[0] = t6;
			trans2[1] = t7;
			trans2[2] = t8;
			trans2[3] = t9;
			trans2[4] = t10;
			trans2[5] = t11;
			trans2[6] = t12;
			trans2[7] = t13;

			trans3[0] = t14;
			trans3[1] = t15;

			//Actor(id, number of Transition, transition array )

			Actor actor1(0, 6, trans1);
			Actor actor2(1, 8, trans2);
			Actor actor3(2, 2, trans3);


			actor_set.insert(actor1);
			actor_set.insert(actor2);
			actor_set.insert(actor3);


			Mailbox mailbox0,mailbox1,mailbox2;
			mailbox0.id = 0;
			mailbox1.id = 1;
			mailbox2.id = 2;



			mailboxes.insert(mailbox0);
			mailboxes.insert(mailbox1);
			mailboxes.insert(mailbox2);


			initState = new State(3, actor_set, mailboxes);

			initState->initialState = true;
			UnfoldingEvent *e = new UnfoldingEvent();
			e->appState = *initState;

			EventSet emptyS;
			std::list<EventSet> maxEvtHistory;
			maxEvtHistory.push_back(emptyS);
			UC.explore(C, maxEvtHistory, D, A, e, prev_exC, actor_set);


			std::cout<<"\n explore full state space :\n";

			State initState1(3, actor_set, mailboxes);
			initState1.initialState = true;
			stateStack.push_back(initState1);
			//exhautiveExplore(stateStack,transList);



						}
							break;




	case 32: { /*		no-error-wait-any_src
 if (nprocs < 2)
    {
      printf ("not enough tasks\n");
    }
  else if (rank == 0)
    {
      memset (buf0, 0, buf_size);
      MPI_Irecv (buf1, buf_size, MPI_INT,  MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &req);

      MPI_Send (buf0, buf_size, MPI_INT, 1, 0, MPI_COMM_WORLD);

      MPI_Wait (&req, &status);
    }
  else if (rank == 1)
    {
      memset (buf1, 1, buf_size);

      MPI_Irecv (buf0, buf_size, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &req);

      MPI_Wait (&req, &status);

      MPI_Send (buf1, buf_size, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

*/
		//transition (maiboxid, commid, type)
			//node 0
			Transition t0(0, 1, "Ireceive");
			Transition t1(1, 2, "Isend");
			Transition t2(1, 2, "Wait");
			Transition t3(0, 1, "Wait");

			// node1

			Transition t4(1, 1, "Ireceive");
			Transition t5(1, 1, "Wait");

			Transition t6(0, 2, "Isend");
			Transition t7(0, 2, "Wait");




			std::array<Transition, 30> trans1, trans2, trans3, trans4,trans5 ;
			trans1[0] = t0;
			trans1[1] = t1;
			trans1[2] = t2;
			trans1[3] = t3;



			trans2[0] = t4;
			trans2[1] = t5;
			trans2[2] = t6;
			trans2[3] = t7;




			//Actor(id, number of Transition, transition array )

			Actor actor1(1, 4, trans1);
			Actor actor2(2, 4, trans2);


			actor_set.insert(actor1);
			actor_set.insert(actor2);


			Mailbox mailbox0,mailbox1,mailbox2;
			mailbox0.id = 0;
			mailbox1.id = 1;



			mailboxes.insert(mailbox0);
			mailboxes.insert(mailbox1);


			initState = new State(2, actor_set, mailboxes);

			initState->initialState = true;
			UnfoldingEvent *e = new UnfoldingEvent();
			e->appState = *initState;

			EventSet emptyS;
			std::list<EventSet> maxEvtHistory;
			maxEvtHistory.push_back(emptyS);
			//UC.explore(C, maxEvtHistory, D, A, e, prev_exC, actor_set);


			std::cout<<"\n explore full state space :\n";

			State initState1(2, actor_set, mailboxes);
			initState1.initialState = true;
			stateStack.push_back(initState1);
			exhautiveExplore(stateStack,transList);


						}
							break;

	case 33: { /*		send-neighbors
*/

		//transition (maiboxid, commid, type)
			//node 0

			Transition t0(1, 1, "Isend");
			Transition t1(2, 2, "Isend");
			Transition t2(0, 3, "Ireceive");
			Transition t3(0, 4, "Ireceive");


			Transition t4(1, 1, "Wait");
			Transition t5(2, 2, "Wait");
			Transition t6(0, 3, "Wait");
			Transition t7(0, 4, "Wait");

			// node1

			Transition t8(0, 1, "Isend");
			Transition t9(2, 2, "Isend");
			Transition t10(1, 3, "Ireceive");
			Transition t11(1, 4, "Ireceive");


			Transition t12(0, 1, "Wait");
			Transition t13(2, 2, "Wait");
			Transition t14(1, 3, "Wait");
			Transition t15(1, 4, "Wait");

			//node 2

			Transition t16(0, 1, "Isend");
			Transition t17(1, 2, "Isend");
			Transition t18(2, 3, "Ireceive");
			Transition t19(2, 4, "Ireceive");


			Transition t20(0, 1, "Wait");
			Transition t21(1, 2, "Wait");
			Transition t22(2, 3, "Wait");
			Transition t23(2, 4, "Wait");



			std::array<Transition, 30> trans1, trans2, trans3, trans4,trans5 ;
			trans1[0] = t0;
			trans1[1] = t1;
			trans1[2] = t2;
			trans1[3] = t3;



			trans1[4] = t4;
			trans1[5] = t5;
			trans1[6] = t6;
			trans1[7] = t7;



			trans2[0] = t8;
			trans2[1] = t9;
			trans2[2] = t10;
			trans2[3] = t11;



			trans2[4] = t12;
			trans2[5] = t13;
			trans2[6] = t14;
			trans2[7] = t15;



			trans3[0] = t16;
			trans3[1] = t17;
			trans3[2] = t18;
			trans3[3] = t19;
			trans3[4] = t20;
			trans3[5] = t21;
			trans3[6] = t22;
			trans3[7] = t23;

			//Actor(id, number of Transition, transition array )

			Actor actor1(1, 8, trans1);
			Actor actor2(2, 8, trans2);
			Actor actor3(3, 8, trans3);


			actor_set.insert(actor1);
			actor_set.insert(actor2);
			actor_set.insert(actor3);


			Mailbox mailbox0,mailbox1,mailbox2;
			mailbox0.id = 0;
			mailbox1.id = 1;
			mailbox2.id = 2;



			mailboxes.insert(mailbox0);
			mailboxes.insert(mailbox1);
			mailboxes.insert(mailbox2);


			initState = new State(3, actor_set, mailboxes);

			initState->initialState = true;
			UnfoldingEvent *e = new UnfoldingEvent();
			e->appState = *initState;

			EventSet emptyS;
			std::list<EventSet> maxEvtHistory;
			maxEvtHistory.push_back(emptyS);
			UC.explore(C, maxEvtHistory, D, A, e, prev_exC, actor_set);


			std::cout<<"\n explore full state space :\n";

			State initState1(3, actor_set, mailboxes);
			initState1.initialState = true;
			stateStack.push_back(initState1);
			//exhautiveExplore(stateStack,transList);


						}
							break;

	case 34: { /*send-neighbors
*/

		//transition (maiboxid, commid, type)
			//node 0

			Transition t0(1, 1, "Isend");
			Transition t1(3, 2, "Isend");
			Transition t2(0, 3, "Ireceive");
			Transition t3(0, 4, "Ireceive");


			Transition t4(1, 1, "Wait");
			Transition t5(3, 2, "Wait");
			Transition t6(0, 3, "Wait");
			Transition t7(0, 4, "Wait");

			// node1

			Transition t8(0, 1, "Isend");
			Transition t9(2, 2, "Isend");
			Transition t10(1, 3, "Ireceive");
			Transition t11(1, 4, "Ireceive");


			Transition t12(0, 1, "Wait");
			Transition t13(2, 2, "Wait");
			Transition t14(1, 3, "Wait");
			Transition t15(1, 4, "Wait");

			//node 2

			Transition t16(3, 1, "Isend");
			Transition t17(1, 2, "Isend");
			Transition t18(2, 3, "Ireceive");
			Transition t19(2, 4, "Ireceive");


			Transition t20(3, 1, "Wait");
			Transition t21(1, 2, "Wait");
			Transition t22(2, 3, "Wait");
			Transition t23(2, 4, "Wait");


			//node 3

			Transition t24(0, 1, "Isend");
			Transition t25(2, 2, "Isend");
			Transition t26(3, 3, "Ireceive");
			Transition t27(3, 4, "Ireceive");


			Transition t28(0, 1, "Wait");
			Transition t29(2, 2, "Wait");
			Transition t30(3, 3, "Wait");
			Transition t31(3, 4, "Wait");





			std::array<Transition, 30> trans1, trans2, trans3, trans4,trans5 ;
			trans1[0] = t0;
			trans1[1] = t1;
			trans1[2] = t2;
			trans1[3] = t3;
			trans1[4] = t4;
			trans1[5] = t5;
			trans1[6] = t6;
			trans1[7] = t7;



			trans2[0] = t8;
			trans2[1] = t9;
			trans2[2] = t10;
			trans2[3] = t11;
			trans2[4] = t12;
			trans2[5] = t13;
			trans2[6] = t14;
			trans2[7] = t15;



			trans3[0] = t16;
			trans3[1] = t17;
			trans3[2] = t18;
			trans3[3] = t19;
			trans3[4] = t20;
			trans3[5] = t21;
			trans3[6] = t22;
			trans3[7] = t23;

			trans4[0] = t24;
			trans4[1] = t25;
			trans4[2] = t26;
			trans4[3] = t27;
			trans4[4] = t28;
			trans4[5] = t29;
			trans4[6] = t30;
			trans4[7] = t31;


			//Actor(id, number of Transition, transition array )

			Actor actor1(1, 8, trans1);
			Actor actor2(2, 8, trans2);
			Actor actor3(3, 8, trans3);
			Actor actor4(4, 8, trans4);


			actor_set.insert(actor1);
			actor_set.insert(actor2);
			actor_set.insert(actor3);
			actor_set.insert(actor4);


			Mailbox mailbox0,mailbox1,mailbox2, mailbox3;
			mailbox0.id = 0;
			mailbox1.id = 1;
			mailbox2.id = 2;
			mailbox3.id = 3;



			mailboxes.insert(mailbox0);
			mailboxes.insert(mailbox1);
			mailboxes.insert(mailbox2);
			mailboxes.insert(mailbox3);


			initState = new State(4, actor_set, mailboxes);

			initState->initialState = true;
			UnfoldingEvent *e = new UnfoldingEvent();
			e->appState = *initState;

			EventSet emptyS;
			std::list<EventSet> maxEvtHistory;
			maxEvtHistory.push_back(emptyS);
			UC.explore(C, maxEvtHistory, D, A, e, prev_exC, actor_set);


			std::cout<<"\n explore full state space :\n";

			State initState1(4, actor_set, mailboxes);
			initState1.initialState = true;
			stateStack.push_back(initState1);
			//exhautiveExplore(stateStack,transList);


						}
							break;

	}
	  clock_t end = clock();
	  double elapsed_secs = double(end - begin) / ( 60*CLOCKS_PER_SEC);

	  std::cout<<" Time in second= " <<  double(end - begin) / (CLOCKS_PER_SEC) << "  \n";
      std::cout<<" Time in minutes= " << elapsed_secs << "  \n";

	std::cout << " \n main() finished ";
	return 0;
}

