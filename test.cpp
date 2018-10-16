//============================================================================
// Name        : test.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================



#include "UnfoldingChecker.hpp"

#include <iostream>
#include <set>
#include <queue>
#include <list>
#include<string>
#include<math.h>

#include <unistd.h>

using namespace std;



int main() {


	nb_events = 0;
	UnfoldingChecker UC;
	EventSet A, D;
	EventSet prev_exC;
	Configuration C;
	State *initState;
	std::set<Actor> actor_set;
	std::set<Mailbox> mailboxes;

	// keep history of maximal event when exploring C
	std::list<set<int> > maxEventHis;

	int example = 0;
	std::cout << " enter example:";
	std::cin >> example;

	switch (example) {
	case 1: { // the first example (in the paper)
		// Transition(read_write, access_variable)
		Transition t1(1, 0);
		Transition t2(0, 0);
		Transition t3(0, 0);





/*

		t2.actor_id = 3;
		EventSet cause1, s1 ,s3;


		UnfoldingEvent *ee = new UnfoldingEvent(1, t1, cause1);
		UnfoldingEvent *ee1 = new UnfoldingEvent(2, t1, cause1);

		UnfoldingEvent *ee2 = new UnfoldingEvent(2, t2, cause1);


		s1.insert(ee);

		s3.insert(ee1);
		if (s1 == s3) std::cout <<" \n hai cai bang nhau ";
		std::cout<<"\n hien s1 ";
		for(auto it: s1.events_)   it->print();


		s1.insert(ee1);
		std::cout<<"\n hien s1 sau insert ";
		for(auto it: s1.events_)   it->print();
		s1.erase(ee1);
		std::cout<<"\n hien s1 sau erase ";
	for(auto it: s1.events_)it->print();
	std::cout<<"\n het hien thi sau erase";


		s1 = s1.plus(ee1);
		std::cout<<"\n hien s1 sau plus ";

		for(auto it: s1.events_)   it->print();


		EventSet s2 ; s2 = s1;
		std::cout<<"\n hien s2 ";

		for(auto it: s2.events_)   it->print();

		s2 = s2.plus(ee2);
		std::cout<<"\n hien s2 ";

		for(auto it: s2.events_)   it->print();

		s3 = s2; s3.erase(ee2);

		std::cout<<"\n sau khi erase s2 la  ";

			for(auto it: s2.events_)   it->print();

			std::cout<<"\n sau khi erase s3 la  ";

					for(auto it: s3.events_)   it->print();

			std::list<EventSet> l;
			EventSet es1, es2;
			es1.insert(ee);
			es2.insert(ee2);
			l.push_back(es1);
			l.push_back(es2);

			std::cout<<"\n hien thi list   ";

			for(auto it: l)
			{	std::cout<<" \n hien thi :";
				for(auto it1: it.events_)it1->print();
			}
			std::cout<<"\n sau khi erase s2 la  ";



			std::cout<<" \nhet ";			std::cout<<" \nhet ";
			std::cout<<" \nhet ";
			std::cout<<" \nhet ";

		usleep(300000000);

*/






		std::array<Transition, 10> trans1, trans2, trans3;
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

	case 2: { // the second example
		Transition t1(1, 0);
		Transition t2(1, 1);
		Transition t3(1, 0);

		std::array<Transition, 10> trans1, trans2, trans3;
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

		std::array<Transition, 10> trans1, trans2, trans3;
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

		std::array<Transition, 10> trans1, trans2, trans3;
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

		std::array<Transition, 10> trans1, trans2, trans3;
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

		std::array<Transition, 10> trans1, trans2, trans3;
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

		std::array<Transition, 10> trans1, trans2, trans3;
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

		std::array<Transition, 10> trans1, trans2;
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

		std::array<Transition, 10> trans1, trans2;
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

		std::array<Transition, 10> trans1, trans2, trans3;
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

		std::array<Transition, 10> trans1, trans2, trans3;
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

		std::array<Transition, 10> trans1, trans2, trans3;
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

		std::array<Transition, 10> trans1, trans2, trans3;
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

		std::array<Transition, 10> trans1, trans2, trans3;
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

		std::array<Transition, 10> trans1, trans2, trans3, trans4;
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

		std::array<Transition, 10> trans1, trans2, trans3, trans4;
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

		std::array<Transition, 10> trans1, trans2, trans3;
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

		std::array<Transition, 10> trans1, trans2, trans3, trans4;
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



			std::array<Transition, 10> trans1, trans2, trans3, trans4;
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



			std::array<Transition, 10> trans1, trans2, trans3, trans4;
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

		std::array<Transition, 10> trans1, trans2, trans3, trans4;
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

		std::array<Transition, 10> trans1, trans2, trans3, trans4, trans5;
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

			std::array<Transition, 10> trans1, trans2, trans3, trans4;
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



				std::array<Transition, 10> trans1, trans2, trans3, trans4, trans5;
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

	}

	std::cout << " \n main() finished ";
	return 0;
}

