
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
    	for (auto t : transList)  std::cout <<"(t_" <<t.id  <<",p_" << t.actor_id << "-"<<t.type << " )   ";

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
    std::cin >> example;

	switch (example) {
	case 1: { // the first example (in the paper)
		// Transition(read_write, access_variable)

        actor_set.insert(Actor(0, {Transition(1, 0)}));
        actor_set.insert(Actor(1, {Transition(0, 0)}));
        actor_set.insert(Actor(2, {Transition(0, 0)}));

        initState = new State(3, actor_set, {Mailbox()});

        UnfoldingEvent *e = new UnfoldingEvent(initState);
        UC.explore(C, {EventSet()}, D, A, e, prev_exC, actor_set);
	}
		break;

	case 2: { // the second example
        actor_set.insert(Actor(1, {Transition(1, 0)}));
        actor_set.insert(Actor(2, {Transition(1, 1), Transition(1, 0)}));

        mailboxes.insert(Mailbox());

		initState = new State(2, actor_set, mailboxes);

        UnfoldingEvent *e = new UnfoldingEvent(initState);
        UC.explore(C, {EventSet()}, D, A, e, prev_exC, actor_set);
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

        UnfoldingEvent *e = new UnfoldingEvent(initState);

        UC.explore(C, {EventSet()}, D, A, e, prev_exC, actor_set);
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

        UnfoldingEvent *e = new UnfoldingEvent(initState);

        UC.explore(C, {EventSet()}, D, A, e, prev_exC, actor_set);
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

        UnfoldingEvent *e = new UnfoldingEvent(initState);
        UC.explore(C, {EventSet()}, D, A, e, prev_exC, actor_set);

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

        UnfoldingEvent *e = new UnfoldingEvent(initState);
        UC.explore(C, {EventSet()}, D, A, e, prev_exC, actor_set);
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

        UnfoldingEvent *e = new UnfoldingEvent(initState);
        UC.explore(C, {EventSet()}, D, A, e, prev_exC, actor_set);
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

        UnfoldingEvent *e = new UnfoldingEvent(initState);
        UC.explore(C, {EventSet()}, D, A, e, prev_exC, actor_set);
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

        UnfoldingEvent *e = new UnfoldingEvent(initState);
        UC.explore(C, {EventSet()}, D, A, e, prev_exC, actor_set);
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

        UnfoldingEvent *e = new UnfoldingEvent(initState);
        UC.explore(C, {EventSet()}, D, A, e, prev_exC, actor_set);
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

        UnfoldingEvent *e = new UnfoldingEvent(initState);
        UC.explore(C, {EventSet()}, D, A, e, prev_exC, actor_set);
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

        UnfoldingEvent *e = new UnfoldingEvent(initState);
        UC.explore(C, {EventSet()}, D, A, e, prev_exC, actor_set);
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

        UnfoldingEvent *e = new UnfoldingEvent(initState);
        UC.explore(C, {EventSet()}, D, A, e, prev_exC, actor_set);
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

        UnfoldingEvent *e = new UnfoldingEvent(initState);
        UC.explore(C, {EventSet()}, D, A, e, prev_exC, actor_set);

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

        UnfoldingEvent *e = new UnfoldingEvent(initState);
        UC.explore(C, {EventSet()}, D, A, e, prev_exC, actor_set);

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

        UnfoldingEvent *e = new UnfoldingEvent(initState);
        UC.explore(C, {EventSet()}, D, A, e, prev_exC, actor_set);
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

        UnfoldingEvent *e = new UnfoldingEvent(initState);
        UC.explore(C, {EventSet()}, D, A, e, prev_exC, actor_set);
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

        UnfoldingEvent *e = new UnfoldingEvent(initState);
        UC.explore(C, {EventSet()}, D, A, e, prev_exC, actor_set);
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

            UnfoldingEvent *e = new UnfoldingEvent(initState);
            UC.explore(C, {EventSet()}, D, A, e, prev_exC, actor_set);
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

            UnfoldingEvent *e = new UnfoldingEvent(initState);
            UC.explore(C, {EventSet()}, D, A, e, prev_exC, actor_set);
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

        UnfoldingEvent *e = new UnfoldingEvent(initState);
        UC.explore(C, {EventSet()}, D, A, e, prev_exC, actor_set);
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

        UnfoldingEvent *e = new UnfoldingEvent(initState);
        UC.explore(C, {EventSet()}, D, A, e, prev_exC, actor_set);
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

            UnfoldingEvent *e = new UnfoldingEvent(initState);
            UC.explore(C, {EventSet()}, D, A, e, prev_exC, actor_set);
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

                UnfoldingEvent *e = new UnfoldingEvent(initState);
                UC.explore(C, {EventSet()}, D, A, e, prev_exC, actor_set);
		}
			break;


	case 25: { 		//master node
					actor_set.insert(Actor(0,{ Transition (2, 1, "Isend"), Transition (2, 1, "Wait"), Transition (3, 2, "Isend"),
											   Transition (3, 2, "Wait"), Transition (4, 3, "Isend"), Transition (4, 3, "Wait"),
											   Transition (1, 4, "Ireceive"), Transition (1, 4, "Wait"),
											   Transition (1, 5, "Ireceive"), Transition (1, 5, "Wait"),
											   Transition (1, 6, "Ireceive"), Transition (1, 6, "Wait")	}));
					// client 1
					actor_set.insert( Actor(1, { Transition (2, 1, "Ireceive"),	Transition (2, 1, "Wait"), Transition(0, 0, "localComp"),
												 Transition (1, 2, "Isend"), Transition (1, 2, "Wait")}));
					//client 2
					actor_set.insert( Actor(2,{	Transition (3, 1, "Ireceive"),	Transition (3, 1, "Wait"), Transition (0, 0, "localComp"),
												Transition (1, 2, "Isend"), Transition (1, 2, "Wait")}));
					//client 3
					actor_set.insert( Actor(3,{	Transition (4, 1, "Ireceive"),	Transition (4, 1, "Wait"), Transition (0, 0, "localComp"),
												Transition (1, 2, "Isend"), Transition (1, 2, "Wait")}));

					initState = new State(4, actor_set,	{ Mailbox(1), Mailbox(2), Mailbox(3), Mailbox(4) });

					UnfoldingEvent *e = new UnfoldingEvent(initState);
					UC.explore(C, { EventSet() }, D, A, e, prev_exC, actor_set);

					std::cout << "\n explore full state space :\n";

					State initState1(4, actor_set, { Mailbox(0), Mailbox(1), Mailbox(2) });
					stateStack.push_back(initState1);
					//exhautiveExplore(stateStack, transList);
			}
				break;

	case 26: { //  master- slaver 3 nodes

		//master node
		actor_set.insert(Actor(0,{ Transition (2, 1, "Isend"), Transition (2, 1, "Wait"), Transition (3, 2, "Isend"),
								   Transition (3, 2, "Wait"), Transition (1, 4, "Ireceive"), Transition (1, 4, "Wait"),
								   Transition (1, 5, "Ireceive"), Transition (1, 5, "Wait")	}));
		// client 1
		actor_set.insert( Actor(1, { Transition (2, 1, "Ireceive"),	Transition (2, 1, "Wait"), Transition(0, 0, "localComp"),
									 Transition (1, 2, "Isend"), Transition (1, 2, "Wait")}));
		//client 2
		actor_set.insert( Actor(2,{	Transition (3, 1, "Ireceive"),	Transition (3, 1, "Wait"), Transition (0, 0, "localComp"),
									Transition (1, 2, "Isend"), Transition (1, 2, "Wait")}));

		initState = new State(3, actor_set,
				{ Mailbox(0), Mailbox(1), Mailbox(2) });

		UnfoldingEvent *e = new UnfoldingEvent(initState);
		UC.explore(C, { EventSet() }, D, A, e, prev_exC, actor_set);

		std::cout << "\n explore full state space :\n";

		State initState1(3, actor_set, { Mailbox(0), Mailbox(1), Mailbox(2) });
		stateStack.push_back(initState1);
		//exhautiveExplore(stateStack, transList);



				}
					break;
	case 28: { // dtg benchmark

	//Transition (maiboxid, commid, type)

 //node 0
 actor_set.insert(Actor(0, { Transition (1, 1, "Ireceive"),	Transition (1, 1, "Wait"), Transition (5, 2, "Isend"),
		 	 	 	 	 	 Transition (5, 2, "Wait"), Transition (1, 3, "Ireceive"), Transition (1, 3, "Wait")}));
//node 1
 actor_set.insert(Actor(1, {Transition (1, 1, "Isend"),	Transition (1, 1, "Wait"),Transition (4, 2, "Isend"),Transition (4, 2, "Wait")}));

//node 2
 actor_set.insert(Actor(2, {Transition (3, 1, "Ireceive"),	Transition (3, 1, "Wait"),Transition (1, 2, "Isend"),Transition (1, 2, "Wait")}));
//node 3
 actor_set.insert(Actor(3, {Transition (4, 1, "Ireceive"),	Transition (4, 1, "Wait"),Transition (5, 2, "Ireceive"),Transition (5, 2, "Wait")}));
//node 4
 actor_set.insert(Actor(4, {Transition (3, 1, "Isend"),	Transition (3, 1, "Wait")}));


 initState = new State(5, actor_set, {Mailbox(1), Mailbox(2),Mailbox(3),Mailbox(4),Mailbox(5)});
 UnfoldingEvent *e = new UnfoldingEvent(initState);
 //UC.explore(C, {EventSet()}, D, A, e, prev_exC, actor_set);

 std::cout<<"\n explore full state space :\n";
 State initState1(5, actor_set, {Mailbox(1), Mailbox(2),Mailbox(3),Mailbox(4),Mailbox(5)});
 stateStack.push_back(initState1);
 exhautiveExplore(stateStack,transList);

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

		//Transition (maiboxid, commid, type)

		 //node 0
		 actor_set.insert(Actor(0, { Transition (2, 1, "Isend"), Transition (2, 1, "Wait"),	Transition (0, 2, "Ireceive"),
				 	 	 	 	 	 Transition (0, 2, "Wait"), Transition (1, 3, "Isend"), Transition (1, 3, "Wait")}));
		//node 1
		 actor_set.insert(Actor(1, {Transition (1, 1, "Ireceive"), Transition (1, 1, "Wait"),
				 	 	 	 	 	Transition (0, 2, "Isend"), Transition (0, 2, "Wait")}));

		//node 2
		 actor_set.insert(Actor(2, { Transition (2, 1, "Ireceive"),	Transition (2, 1, "Wait")}));


		 initState = new State(3, actor_set, {Mailbox(0), Mailbox(1),Mailbox(2)});

         UnfoldingEvent *e = new UnfoldingEvent(initState);
         //UC.explore(C, {EventSet()}, D, A, e, prev_exC, actor_set);

		 std::cout<<"\n explore full state space :\n";

		 State initState1(3, actor_set, {Mailbox(0), Mailbox(1),Mailbox(2)});
		 stateStack.push_back(initState1);
		 exhautiveExplore(stateStack,transList);


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
	//Transition (maiboxid, commid, type)

			 //node 0
			 actor_set.insert(Actor(0, {Transition (0, 1, "Ireceive"), Transition (0, 1, "Wait"), Transition (1, 2, "Isend"),	Transition (1, 2, "Wait")}));
			//node 1
			 actor_set.insert(Actor(1, {Transition (1, 1, "Ireceive"), Transition (1, 1, "Wait"), Transition (0, 2, "Isend"),Transition (0, 2, "Wait")}));

			 initState = new State(2, actor_set, {Mailbox(0), Mailbox(1)});
			 std::cout<<"\n UDPOR state space :\n";

	         UnfoldingEvent *e = new UnfoldingEvent(initState);
	        // UC.explore(C, {EventSet()}, D, A, e, prev_exC, actor_set);

			 std::cout<<"\n explore full state space :\n";

			 State initState1(2, actor_set, {Mailbox(0), Mailbox(1)});
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
				//Transition (maiboxid, commid, type)

				 //node 0
				 actor_set.insert(Actor(0, { Transition (0, 1, "Ireceive"),	Transition (0, 2, "Ireceive"), Transition (0, 1, "Wait"),
						 	 	 	 	 	 Transition (0, 2, "Wait"), Transition (1, 3, "Isend"), Transition (1, 3, "Wait")}));
				//node 1
				 actor_set.insert(Actor(1, {Transition (0, 1, "Isend"),	Transition (2, 2, "Isend"),
						                    Transition (0, 1, "Wait"),  Transition (2, 2, "Wait"),
											Transition (1, 3, "Ireceive"), Transition (1, 3, "Wait"),
											Transition (0, 4, "Isend"),	Transition (0, 4, "Wait")}));

				//node 2
				 actor_set.insert(Actor(2, { Transition (2, 1, "Ireceive"),	Transition (2, 1, "Wait")}));


				 initState = new State(3, actor_set, {Mailbox(0), Mailbox(1),Mailbox(2)});

		         UnfoldingEvent *e = new UnfoldingEvent(initState);
		         UC.explore(C, {EventSet()}, D, A, e, prev_exC, actor_set);

				 std::cout<<"\n explore full state space :\n";

				 State initState1(3, actor_set, {Mailbox(0), Mailbox(1),Mailbox(2)});
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

		//Transition (maiboxid, commid, type)

		//node 0
		actor_set.insert(Actor(0,{Transition (0, 1, "Ireceive"), Transition (1, 2, "Isend"), Transition (1, 2, "Wait"), Transition (0, 1, "Wait") }));
		//node 1
		actor_set.insert(Actor(1,{ Transition (1, 1, "Ireceive"), Transition (1, 1, "Wait"), Transition (0, 2, "Isend"), Transition (0, 2, "Wait") }));

		initState = new State(2, actor_set, { Mailbox(0), Mailbox(1) });

		std::cout << "\n UDPOR state space :\n";

		UnfoldingEvent *e = new UnfoldingEvent(initState);
		UC.explore(C, {EventSet()}, D, A, e, prev_exC, actor_set);

		std::cout << "\n explore full state space :\n";

		State initState1(2, actor_set, { Mailbox(0), Mailbox(1) });
		stateStack.push_back(initState1);
		//exhautiveExplore(stateStack, transList);
						}
							break;

	case 33: { /*any_src-can-deadlock3.c
		if (nprocs < 3)
	    {
	      printf ("not enough tasks\n");
	    }
	  else if (rank == 0)
	    {
	      MPI_Recv (buf1, buf_size, MPI_INT,
			MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);

	      MPI_Send (buf1, buf_size, MPI_INT, 1, 0, MPI_COMM_WORLD);

	      MPI_Recv (buf0, buf_size, MPI_INT,
			MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
	    }
	  else if (rank == 1)
	    {
	      memset (buf0, 0, buf_size);

	      MPI_Send (buf0, buf_size, MPI_INT, 0, 0, MPI_COMM_WORLD);

	      MPI_Recv (buf1, buf_size, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
	    }
	  else if (rank == 2)
	    {
	      memset (buf1, 1, buf_size);

	      //sleep (60);

	      MPI_Send (buf1, buf_size, MPI_INT, 0, 0, MPI_COMM_WORLD);
	    }

	 	 */
		//Transition (maiboxid, commid, type)

		//node 0
		actor_set.insert(Actor(0,{ 	Transition (0, 1, "Ireceive"),Transition (0, 1, "Wait"), Transition (1, 2, "Isend"),
				 	 	 	 	 	Transition (1, 2, "Wait"), Transition (0, 3, "Ireceive"),Transition (0, 3, "Wait")}));
		//node 1
		actor_set.insert(Actor(1, {	Transition (0, 1, "Isend"),	Transition (0, 1, "Wait"),
									Transition (1, 2, "Ireceive"), Transition (1, 2, "Wait")}));

		//node 2
		actor_set.insert(Actor(2, { Transition (0, 0, "Isend"), Transition (0, 0, "Wait") }));

		initState = new State(3, actor_set,	{ Mailbox(0), Mailbox(1), Mailbox(2) });

		UnfoldingEvent *e = new UnfoldingEvent(initState);
		//UC.explore(C, { EventSet() }, D, A, e, prev_exC, actor_set);

		std::cout << "\n explore full state space :\n";

		State initState1(3, actor_set, { Mailbox(0), Mailbox(1), Mailbox(2) });
		stateStack.push_back(initState1);
		exhautiveExplore(stateStack,transList);
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

