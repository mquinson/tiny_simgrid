#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include <unistd.h>
//#include "src/mc/mc_state.h"

#include "UnfoldingChecker.hpp"

unsigned int nb_events=0;
unsigned int nb_traces=0;
int comId = -1;
EventSet U, G, gD;

/*void UnfoldingChecker::computeAlt(EventSet& J, EventSet D, Configuration C,
 EventSet U1, EventSet Uc) {
 if (not J.empty())
 return;

 if (Uc.empty()) {
 U1 is a subset of U, we cheking that C1 \union U1 is configuration ?
 and for all e \in D, exist e' \in  (C1 \union U1): e' immediate  conflict with e

 EventSet C1 = C.makeUnion(C, U1);

 if (C1.isConfig()) {
 size_t count = 0;
 for (auto evt : D.events_)
 for (auto evt1 : C1.events_)
 if (evt->isImmediateConflict(evt1) and U.contains(evt1)) {
 count++;
 break;
 }

 if (count == D.size()) {
 J = U1;

 }
 }
 std::cout<<"\n return nhe ==================\n";
 return;
 }

 else {
 UnfoldingEvent *a = Uc.begin();
 EventSet evtSet1, evtSet2, evtSet3, evtSet4;
 evtSet1 = U1;
 evtSet3 = Uc;
 evtSet1.insert(a);
 evtSet3.erase(a);
 computeAlt(J, D, C, evtSet1, evtSet3);

 evtSet2 = U1;
 evtSet4 = Uc;
 evtSet4.erase(a);

 computeAlt(J, D, C, evtSet2, evtSet4);
 }

 }*/
void intTobinary(int n, int p[]) {
	int i = 0;
	while (n != 0) {
		p[i] = n % 2;
		i++;
		n = n / 2;
	}

}

EventSet UnfoldingChecker::filter(Configuration C, EventSet U) {
	EventSet evtS;
	for (auto evt : U.events_)
		if (not evt->conflictWithConfig(evt,C))
			evtS.insert(evt);

	return evtS;

}


/* this function select one event in every EventSet in a list to form a set,
 *  if they are not conflict with each other -> return the set J
 */

void ksubset(int sizeD, std::list<UnfoldingEvent*> EvtList,
		std::list<EventSet> list, int n, EventSet & J) {


	if (J.size() > 0)
		return;

	std::list<UnfoldingEvent*> EvtList1 = EvtList;
	std::list<UnfoldingEvent*> EvtList2;

	if (list.size() > 0) {

		EventSet intS = list.back();

		std::list<EventSet> list1 = list;
		list1.pop_back();

		int inter = 0;
		for (auto it : intS.events_) {

			bool check = false;
			for (auto evt : EvtList1)
				if (it->isConflict(it, evt)) {
					check = true;
					break;
				}
			if (check)
				continue;

			// if inter > 0 intS already has a presentative, pop the old one and add the new one

			if (inter > 0)
				EvtList1.pop_back();
			EvtList1.push_back(it);


			if (n == sizeD - 1) {
				int chk = true;

				//check there is no conflict between 2 events in the list
				/*	std::list<UnfoldingEvent*> EvtList2 = EvtList1;
				 for (auto it1 : EvtList1) for (auto it2 : EvtList2)
				 if (it1->isConflict(it2))
				 { chk = false; break;}
				 */

				//if (chk )
				if (EvtList1.size() == sizeD) {
					for (auto evt : EvtList1)
						J.insert(evt);
					return;
				}
			}

			if (J.size() == 0)
				ksubset(sizeD, EvtList1, list1, n + 1, J);
			inter++;
		}
	}
//	std::cout << " \n finish ksubset \n";
}

EventSet UnfoldingChecker::KpartialAlt(EventSet D, Configuration C) {


	EventSet J, J1, emptySet, result;
	std::list<EventSet> kSet;

	/*for each evt in D, add all evt1 in U that is conflict with evt to a set(spike) */

	for (auto evt : D.events_) {
		EventSet evtSet;
		for (auto evt1 : U.events_)
			if (evt->isConflict(evt,evt1))	evtSet.insert(evt1);

		kSet.push_back(evtSet);

	}

	std::list<EventSet> kSet1;

	if (kSet.size() < D.size()) {
//		std::cout << "there is no optimal solution (no alternative) 1";
		return emptySet;
	}

	else {


// for each spike, remove all evt whose [evt] is conflict with C
		for (auto it : kSet) {
			EventSet evtS = it;


			for (auto evt : it.events_)
			{

				EventSet subC , sub_history , history = evt->getHistory(); history.insert(evt);

	/*			subC = C;
				sub_history = history;

				// remove all common events

				for(auto evt1: C.events_) if (history.contains(evt1)) {subC.erase(evt1); sub_history.erase(evt1);}

			if ( (! history.isEmptyIntersection(history,D)) or  (subC.depends(sub_history)))*/

				bool chk = false;

				if ( not history.isEmptyIntersection(history,D)){

					chk = true;
					//if (evt->id == 29)std::cout <<"\n va chk =" << chk <<" \n";

				}
				else for(auto it1: C.events_) if(it1->isConflict(it1,evt)) { chk= true; break;}

				//if (evt->id == 29)std::cout<<" sau khi kt dk chk =" << chk << " \n";

					if(chk)	{ //if (evt->id == 29)std::cout<<" se xoa thang 29 nhe chk =" << chk << " \n";
					evtS.erase(evt);

					}

			}


			if (evtS.empty()) {

				//std::cout << "there is no optimal solution (no alternative)";
				return emptySet;
			}

			kSet1.push_back(evtS);
		}


// building J by chosing one event in each spike such that there are not 2 conflict events in J
		int n = 0;
		std::list<UnfoldingEvent*> EvtList;

		ksubset(D.size(), EvtList, kSet1, n, J1);
	}

	// J1.size() can be < D.size() since one event in J1 can be conflict with some events in D

	if (J1.size() == 0) {

		std::cout << "there is no optimal solution (no alternative) J1 size = "
				<< J1.size() << " \n";
		return emptySet;
	}

	else

	{

		for (auto evt : J1.events_) {
			EventSet history = evt->getHistory();
			J = J.makeUnion(J, history);
			J.insert(evt);
		}
	}

//	std::cout <<"\n ---->>> end kpartial \n";

	return J;

}



EventSet UnfoldingChecker::computeAlt(EventSet D, Configuration C) {

	/* U1 is a subset of U, we cheking that C1 \union U1 is configuration ?
	 and for all e \in D, exist e' \in  (C1 \union U1): e' immediate  conflict with e
	 */

	/*instead of using U we use Uc = U \ C -> in expore we replace J \ C by J*/


	EventSet Uc = U;

	int nbsubset = pow(2, Uc.size());

	for (auto i = 1; i < nbsubset; i++) {

		int B[Uc.size()];
		EventSet U1;
		int k = 0;

		for (int i = 0; i < Uc.size(); i++)
			B[i] = 0;

		intTobinary(i, B);

		for (auto it : Uc.events_) {
			if (B[k] == 1)
				U1.insert(it);
			k++;
		}

		EventSet C1 = C.makeUnion(C, U1);

		if (C1.isConfig()) {
			size_t count = 0;
			for (auto evt : D.events_)
				for (auto evt1 : C1.events_)

				{

					if (evt->isImmediateConflict1(evt,evt1) and U.contains(evt1)) {
						count++;
						break;
					}


				}

			if (count == D.size()) {
						return U1;
			}
		}
	}

	EventSet evtS;
	return evtS;

}

void IntSet::insert(int e) {
	this->ints.insert(e);
}

bool IntSet::inculude(IntSet other) {
	for (auto it : other.ints)
		if (not (this->ints.find(it) != this->ints.end()))
			return false;

	return true;

}

/*check whether a mutex wait is enabled ?*/
bool isMwaitEnabled(Configuration C, EventSet causalityEvt, Transition trans) {

	UnfoldingEvent * e;
	//bool chk = false;
	int nbLock = 0, nbUnlock = 0;

	for (auto evt : C.events_)
		if (trans.actor_id == evt->transition.actor_id
				and trans.lockId == evt->transition.lockId) {
			e = evt;
			break;
		}

	EventSet His = e->getHistory();

	for (auto evt : His.events_)
		if (evt->transition.type == "lock")
			nbLock++;

	EventSet unlockSet;

	// get all unlock and put them into unlockSet

	for (auto evt : causalityEvt.events_) {
		nbUnlock++; // wait is only depent with unlock -> all evts in causalityEvt are unlock -> increase nbUnlock
		EventSet H = evt->getHistory();
		for (auto evt1 : H.events_)
			if (evt1->transition.type == "Unlock")
				unlockSet.insert(evt1);
	}

	return (nbLock < unlockSet.size() - 1) ? true : false;

}


bool checkSdRcCreation(Transition trans, EventSet ancestors, Configuration C) {



	int nbTest =0, nbSend = 0, nbReceive = 0;
	UnfoldingEvent *testEvt;
	for (auto evt : ancestors.events_) if (evt->transition.type == "Test" and evt->transition.actor_id != trans.actor_id) {nbTest++; testEvt = evt;}

	// one send/receive can not concern more than one communication
	if (nbTest > 1) return false;
	else if (nbTest ==0) return true;


  UnfoldingEvent *testedEvt = C.findTestedComm(testEvt);

  //  two sends or receives can not be in the communiation -> not depend

if (testedEvt->transition.type == trans.type or testedEvt->transition.mailbox_id != trans.mailbox_id)
	  return false;



  EventSet testedEvtHist = testedEvt->getHistory();
  EventSet ancestorsHist;

  for (auto evt : ancestors.events_)
	   ancestorsHist = ancestorsHist.makeUnion(ancestorsHist, evt->getHistory());

  // check nb send == nb receive ?, if yes they concern the same comm -> test and send/receive are dependent

  if (testedEvt->transition.type =="Isend"){
	  for (auto evt: testedEvtHist.events_)
	  if (evt->transition.type =="Isend" and evt->transition.mailbox_id == testedEvt->transition.mailbox_id) nbSend++;

	  int nbReceive1 =0;
	  for(auto evt : ancestorsHist.events_) if (evt->transition.type == "Ireceive" and
			  evt->transition.mailbox_id == testedEvt->transition.mailbox_id)
		  nbReceive1 ++;
	  for(auto it: ancestors.events_) if(it->transition.type=="Ireceive"
			  and it->transition.mailbox_id == testedEvt->transition.mailbox_id)
		  nbReceive1 ++;

	  if(nbSend != nbReceive1) return false;


  }

  if (testedEvt->transition.type =="Ireceive"){

	  for (auto evt: testedEvtHist.events_)
	  if (evt->transition.type =="Ireceive" and evt->transition.mailbox_id == testedEvt->transition.mailbox_id) nbReceive++;

	  int nbSend1 =0;
	  for(auto evt : ancestorsHist.events_) if (evt->transition.type == "Isend" and
			  evt->transition.mailbox_id == testedEvt->transition.mailbox_id)
		  nbSend1 ++;

	  for(auto it: ancestors.events_) if(it->transition.type=="Isend"
			  and it->transition.mailbox_id == testedEvt->transition.mailbox_id)
		  nbSend1 ++;

	  if(nbReceive != nbSend1) return false;
  }
	return true;
}


/* this function creating new events from a transition and a set cadidate directed ancestors (ancestorSet)
 *  (the set includes events that can be a direct ancestor)
 *  by combination the transition and all subset (cause)  of the set ancestorSet
 */

void Configuration::createEvts(Configuration C, EventSet& result, Transition t,
		EventSet causuality_events, EventSet cause, EventSet ancestorSet,
		bool chk, UnfoldingEvent *immPreEvt) {
	if (ancestorSet.empty()) {

		bool chk1 = false;
		// if immediate precede event is not in the causuality_events, ensure that it is in the history of one event in cause
		if (not chk)
			for (auto evt : cause.events_)
				if (evt->getHistory().contains(immPreEvt)) {
					chk1 = true;
					break;
				}
		/* create a new evt with directed ancestors are cause1,
		 * if all conditions are passed (trans is enabled, any ancestors are not in the history of other ancestors)
		 */
		if (chk or chk1) {
			bool send_receiveCheck = true;
			EventSet cause1;
			cause1 = cause1.makeUnion(cause, causuality_events);
			//check condition for send/receive action or check enabled for MutexWait action

			if (t.type =="Isend" or t.type == "Ireceive")
			{
				send_receiveCheck = checkSdRcCreation(t, cause1,  C);
			}



			if (send_receiveCheck) {
			nb_events++;
			UnfoldingEvent *e = new UnfoldingEvent(nb_events, t, cause1);
			result.insert(e);
			}


		}
		return;
	}

	else {
		UnfoldingEvent *a = ancestorSet.begin();
		EventSet evtSet1, evtSet2, evtSet3, evtSet4;
		evtSet1 = cause;
		evtSet3 = ancestorSet;
		evtSet1.insert(a);
		evtSet3.erase(a);
		createEvts(C, result, t, causuality_events, evtSet1, evtSet3, chk,
				immPreEvt);
		evtSet2 = cause;
		evtSet4 = ancestorSet;
		evtSet4.erase(a);
		createEvts(C, result, t, causuality_events, evtSet2, evtSet4, chk,
				immPreEvt);
	}

}

// gives a event in actorMaxEvent has the id = a given id
UnfoldingEvent * Configuration::findActorMaxEvt(int id) {
	UnfoldingEvent * immPreEvt;
	for (auto evt : this->actorMaxEvent.events_)
		if (evt->transition.actor_id == id)
			immPreEvt = evt;
	return immPreEvt;
}

/* this function produces new events from a given transition (trans) and the maxEvtHistory*/

EventSet computeExt(Configuration C, std::list<EventSet> maxEvtHistory,
		Transition trans) {

	bool chk = false;
	EventSet causalityEvts;
	EventSet exC, ancestorSet, H;
	UnfoldingEvent *immPreEvt;

	// add causality evts to causalityEvts set, firstly add last event to causalityEvts
	causalityEvts.insert(C.lastEvent);

	/* add the immediate precede evt of transition trans to the causalityEvts
	 *  used to make sure trans is enabled (Ti is enlabled if Ti-1 is aready fined)
	 chk == true =>  causalityEvts contains immediate precede event of trans Or the immediate precede event is in history of lastEvt.
	 */

	if (trans.id == 0)
		chk = true; //if trans.id ==0 => trans is always enabled do not need to check enable condition ?.

	else {
		//if immediate precede evt in maxEvent, add it to the causalityEvts
		for (auto evt : C.maxEvent.events_)
			if (trans.actor_id == evt->transition.actor_id) {
				causalityEvts.insert(evt);
				chk = true;
				break;
			}

		//else find it in actorMaxEvent to add it into causalityEvts
		immPreEvt = C.findActorMaxEvt(trans.actor_id);
		if (not chk)
			if (C.lastEvent->getHistory().contains(immPreEvt))
				chk = true;
	}

	for (auto evt : C.maxEvent.events_)
		if (trans.isDependent(evt->transition)
				and (not causalityEvts.contains(evt)))
			ancestorSet.insert(evt);

	/*1. Create events from current (last) maximal event of C */
	// 1.1 if only last evt and immidiate precede event are dependent with trans -> only one evt is created
	if (causalityEvts.size() <= 2 and ancestorSet.size() == 0) {

		nb_events++;

		/* in this case only one event is created, since all MaxEvts are in the history of lastEvt*/
		UnfoldingEvent *e = new UnfoldingEvent(nb_events, trans, causalityEvts);
		exC.insert(e);

	}

	else {
		//1.2 else create events from trans and events in current maxEvent


		EventSet cause;
		EventSet exC1;

		C.createEvts(C, exC1, trans, causalityEvts, cause, ancestorSet, chk,
				immPreEvt);
		exC = exC.makeUnion(exC, exC1);

		//remove last MaxEvt, sine we already used it in the above
		maxEvtHistory.pop_back();

		/*2. We now compute new evts by using MaxEvts in the past, but we have to ensure that
		 * the ancestor events (used to generate history candidate) are not in history of the evts in the causalityEvts
		 */
		std::set<int> intS;
		// get all events in the history of the evts in causalityEvts
		for (auto evt : causalityEvts.events_) {
			EventSet H1;
			H1 = evt->getHistory();
			H = H.makeUnion(H, H1);
		}

		// put id of evts in H in the the set intS
		for (auto evt : H.events_)
			intS.insert(evt->id);

		/* compute a set of evt that can generate history (all subset of it)
		 by getting evts in the maximal evts but not in the history of causalityEvts*/

		for (auto evtSet : maxEvtHistory) {
			EventSet evtS;

			// put ids of events that are not in the history of evts in causalityEvts into a set intS1

			// if history candidate is not empty then try create new evts from its subset
			if (not evtSet.empty()) {

				// retrieve  evts in congig from intS1 (intS1 store id of evts in C whose transitions are dependent with trans)
				EventSet evtSet1;
				for (auto evt : evtSet.events_)
						if ( (not H.contains(evt)) and  evt->transition.isDependent(trans))
							evtSet1.insert(evt);

				EventSet exC1;
				EventSet cause;
				C.createEvts(C, exC1, trans, causalityEvts, cause, evtSet1,
						chk, immPreEvt);
				exC = exC.makeUnion(exC, exC1);
			}

		}
	}
	return exC;

}


/* this function creates new events from a wait transition (trans),
this wait waits a communication (action send/receive) in the the parameter/event evt
The idea here is that, we try to march the communication with all possible communication to crete a complete communication,
making wait become enabled. When the wait enable, we can create new events
*/

EventSet createWaitEvt( UnfoldingEvent * evt, Configuration C, Transition trans){
	EventSet evtS; int nbSdRc=0;
	EventSet hist = evt->getHistory();
	int mbId = evt->transition.mailbox_id;
	string comType = evt->transition.type;

	if(comType =="Isend"){
		 // if waited communication is  send, count the number of send request before the communication

		 for (auto evt1: hist.events_) if (evt1->transition.type=="Isend" and evt1->transition.mailbox_id == mbId) nbSdRc++;

		 // try to march the communication with all possible receice request
		 for (auto evt2: C.events_) if (evt2->transition.type =="Ireceive" and evt2->transition.mailbox_id == mbId)
		 {
			 // after find ount a receive request
			 EventSet hist1 = evt2->getHistory(); int nbRc =0;

		 // count the number of receice requests before the receive that we found above

		   for(auto evt3 : hist1.events_) if (evt3->transition.type =="Ireceive" and evt3->transition.mailbox_id == mbId) nbRc++;
		   	   if (nbSdRc == nbRc) {

	   // if the number send = number receive, we can march the send communication  with the rececive
		   		   EventSet ancestors;
		   		   UnfoldingEvent *maxEvt =  C.findActorMaxEvt(evt->transition.actor_id);
		   		   EventSet maxEvtHist = maxEvt->getHistory();

		   		   if (maxEvtHist.contains(evt2)) ancestors.insert(maxEvt);
		   		   else if (hist1.contains(maxEvt)) ancestors.insert(evt2);
		   		   	   else {ancestors.insert(maxEvt); ancestors.insert(evt2);}
		   		nb_events++;
		   		UnfoldingEvent *e = new UnfoldingEvent(nb_events, trans, ancestors);
		   		evtS.insert(e);
		   	   }
		 	 }
	 }
	// do the same for a receive
	else if(comType=="Ireceive")
	{
			 // if waited communication is send, count the number of send request before the communication

			 for (auto evt1: hist.events_) if (evt1->transition.type=="Ireceive" and evt1->transition.mailbox_id == mbId) nbSdRc++;

			 // try to march the communication with all possible receice request
			 for (auto evt2: C.events_) if (evt2->transition.type =="Isend" and evt2->transition.mailbox_id == mbId)
			 {
				 // after find out a receive request
				 EventSet hist1 = evt2->getHistory(); int nbRc =0;

			 // count the number of receice requests before the receive that we found above

			   for(auto evt3 : hist1.events_) if (evt3->transition.type =="Isend" and evt3->transition.mailbox_id == mbId) nbRc++;
			   	   if (nbSdRc == nbRc) {
		   // if the number send = number receive, we can march the send communication  with the rececive
			   		   EventSet ancestors;
			   		   UnfoldingEvent *maxEvt =  C.findActorMaxEvt(evt->transition.actor_id);
			   		   EventSet maxEvtHist = maxEvt->getHistory();

			   		   if (maxEvtHist.contains(evt2)) ancestors.insert(maxEvt);
			   		   else if (hist1.contains(maxEvt)) ancestors.insert(evt2);
			   		   	   else {ancestors.insert(maxEvt); ancestors.insert(evt2);}
			   		nb_events++;
			   		UnfoldingEvent *e = new UnfoldingEvent(nb_events, trans, ancestors);
			   		evtS.insert(e);
			   	   }
			 	 }
		 }

	return evtS;
}

EventSet createTestEvt( EventSet exC,  UnfoldingEvent * evt, Configuration C, Transition trans){

	EventSet evtS; int numberSend=0, numberReceive=0;
	EventSet hist = evt->getHistory();
	EventSet lastEvtHist = C.lastEvent->getHistory();

	int mbId = evt->transition.mailbox_id;
	string comType = evt->transition.type;
	UnfoldingEvent  *newEvt1, *newEvt2;
    EventSet ancestors;

    /* since action test is always enabled, create a new event although there is no pending Ireceive
	 * to march with the send (create ewEvt1)
	 *
		   		 	 	 	 /--------\
		   					/          \
		   evt=<Isend,ancestors>     evt2=<IReceive,ancestors>
		   	  	  	  	  / \           /
		   	 	 	 	 /	 \  	   /
		   				/	  \       /
		   	   	   	   /       \     /
	ewEvt1 =<Test1,(e1, e2)>     newEvt2 =<Test1, (e1, e2)>
	 * */

    /*1. last evt = pre evt -> create at least one event
     *							 |-> pre evt is in the history of last evt
     *2. last evt != pre evt =>  |  											-> TRY TO create one evt
     						     |-> pre evt is not in the history of last evt
     */

    // count the number of isend/ireceive befere evt
	if (comType == "Isend") {
		for (auto evt1 : hist.events_)
			if (evt1->transition.type == "Isend" and evt1->transition.mailbox_id == mbId)
				numberSend++;
	} else if (comType == "Ireceive") {
		for (auto evt1 : hist.events_)
			if (evt1->transition.type == "Ireceive" and evt1->transition.mailbox_id == mbId)
				numberReceive++;
	}


    // if last evt is the pre evt -> create at least one evt
    if (C.lastEvent->transition.actor_id == trans.actor_id)
	 //maxEvt =  C.findActorMaxEvt(evt->transition.actor_id);
    {     EventSet maxEvtHist = C.lastEvent->getHistory();

    	ancestors.insert(C.lastEvent);
    	nb_events++;
    	newEvt1 = new UnfoldingEvent(nb_events, trans, ancestors);

    	evtS.insert(newEvt1);

  /* Now try to create newEvt2 if there is a pending communication can be march
	 with the communication tested by the Test action */


	if(comType =="Isend"){

		 // try to march the communication with all possible receice request
		 for (auto evt2: C.events_) if (evt2->transition.type =="Ireceive" and evt2->transition.mailbox_id == mbId and (not lastEvtHist.contains(evt2)))
		 {
			 // after find out a receive request

			 EventSet hist2 = evt2->getHistory(); int nbReceive =0;

		 // count the number of receice requests before the receive that we found above

		   for(auto evt3 : hist2.events_) if (evt3->transition.type =="Ireceive" and evt3->transition.mailbox_id == mbId) nbReceive++;
		   	   if (numberSend == nbReceive)
		   	   {
	   /* if the number send = number receive, we can march the send communication with the rececive
	    * -> create an new event ( newEvt2 in the figure) */

		   		ancestors.insert(evt2);
		   		nb_events++;
		   		newEvt2 = new UnfoldingEvent(nb_events, trans, ancestors);

		   		evtS.insert(newEvt2);

		   	   }
		 	 }
	 }
	// do the same for a receive

	else if(comType =="Ireceive"){

	 // try to march the communication with all possible receice request
		 for (auto evt2: C.events_) if (evt2->transition.type =="Isend" and evt2->transition.mailbox_id == mbId and (not lastEvtHist.contains(evt2)))
		 {
			 // after find out a receive request

			 EventSet hist2 = evt2->getHistory(); int nbSend =0;

		 // count the number of receice requests heppen before the receive that we found above

		   for(auto evt3 : hist2.events_) if (evt3->transition.type =="Isend" and evt3->transition.mailbox_id == mbId) nbSend++;
		   	   if (numberReceive == nbSend)
		   	   {

	   /* if the number send = number receive, we can march the send communication with the rececive
	    * -> create an new event ( newEvt2 in the figure) */

		   		ancestors.insert(evt2);
		   		nb_events++;
		   		newEvt2 = new UnfoldingEvent(nb_events, trans, ancestors);
		   		evtS.insert(newEvt2);

		   	   }
		 	 }
	 }

    }

    // If the last event is evt2 (in figure), try to march evt2 with evt (in figure)
    else {


    	if(comType =="Isend") {
   		 int nbReceive = 0;

   		 for (auto evt2: lastEvtHist.events_) if (evt2->transition.type=="Ireceive") nbReceive++;
   		 if (numberSend == nbReceive) {

   			UnfoldingEvent *maxEvt =  C.findActorMaxEvt(evt->transition.actor_id);
   			ancestors.insert(C.lastEvent);  if (not lastEvtHist.contains(maxEvt)) ancestors.insert(maxEvt);
   			nb_events++;
   			newEvt2 = new UnfoldingEvent(nb_events, trans, ancestors);
   			evtS.insert(newEvt2);
   		 }
    	}
    	else if(comType =="Ireceive") {

      		 int nbSend = 0;
      		 for (auto evt2: lastEvtHist.events_) if (evt2->transition.type=="Isend") nbSend++;

      		 if (numberReceive == nbSend) {
      			UnfoldingEvent *maxEvt =  C.findActorMaxEvt(evt->transition.actor_id);

      			ancestors.insert(C.lastEvent); if (not lastEvtHist.contains(maxEvt)) ancestors.insert(maxEvt);
      			nb_events++;
      			newEvt2 = new UnfoldingEvent(nb_events, trans, ancestors);
      			evtS.insert(newEvt2);
      		 }

       	}
    }

 return evtS;
}



EventSet createIsendEvts(Transition trans, Configuration C){

	bool enableChk = false;

	EventSet exC, EvtSet, causalityEvts, ancestorSet;
	UnfoldingEvent *testedEvt, *immPreEvt;

	/* if trans is not dependent with the last transition -> return */

	if (C.lastEvent->transition.type =="Test" and C.lastEvent->transition.actor_id != trans.actor_id) {
	// get the communication tested by Test
		testedEvt = C.findTestedComm(C.lastEvent);

	// two sends or two receives can not be in the same communication -> not denpendent
			if (trans.type == testedEvt->transition.type or trans.mailbox_id != testedEvt->transition.mailbox_id )
			 return EvtSet;
		}


	//if trans.id ==0 => trans is always enabled do not need to check enable condition ?.
	if (trans.id == 0 or C.lastEvent->transition.actor_id == trans.actor_id)
		enableChk = true;
	/* enableChk = true -> trans is ensured enabled or his pre evt is in the causalityEvts  */
	else if (C.lastEvent->transition.actor_id != trans.actor_id and (not enableChk)){
	//else find it in actorMaxEvent and check where it is in the history of last Evt
			immPreEvt = C.findActorMaxEvt(trans.actor_id);
			if (C.lastEvent->getHistory().contains(immPreEvt))
				enableChk = true;
	}

	immPreEvt = C.findActorMaxEvt(trans.actor_id);


	EventSet lastEvtHist = C.lastEvent->getHistory();


	EventSet immPreEvtHist; if (trans.id != 0) immPreEvtHist = immPreEvt->getHistory();


	ancestorSet.insert(C.lastEvent);

	// if last event is preEvt(trans) always create a new event.
		if( C.lastEvent->transition.actor_id == trans.actor_id)
		{
		nb_events++;
		UnfoldingEvent *e = new UnfoldingEvent(nb_events, trans, ancestorSet);
		exC.insert(e);
		}
		// else if last event is Isend try to create a new event .
		else if (C.lastEvent->transition.type =="Isend")
			 {

			if (enableChk)
					{
						nb_events++;
						UnfoldingEvent *e = new UnfoldingEvent(nb_events, trans, ancestorSet);
						exC.insert(e);
					}
			   else {	ancestorSet.insert(immPreEvt);
						nb_events++;
						UnfoldingEvent *e = new UnfoldingEvent(nb_events, trans, ancestorSet);
						exC.insert(e);
			}
				}

	// if last evt = preEvt(Isend) or last evt is a Isend, then try to combine with Test
	if(trans.isDependent(C.lastEvent->transition))
	 for(auto it : C.events_) if (it->transition.type =="Test" and it->transition.mailbox_id == trans.mailbox_id) {
		UnfoldingEvent *testedEvt;
		//retrive the communication tested by the the
			  testedEvt = C.findTestedComm(it);

		// tested action is Ireceive, create a new event if it can be marched with the Isend
		// make sure no ancestor candidate event is in history of other ancestor candidate

		if(testedEvt->transition.type =="Ireceive" and (not lastEvtHist.contains(it)))
				if ( not immPreEvtHist.contains(it) )
				{
					EventSet ancestorSet1;  ancestorSet1.insert(C.lastEvent);
					ancestorSet1.insert(it);
					EventSet itHist = it->getHistory();
					if ((not itHist.contains(immPreEvt)) and (not enableChk)) ancestorSet1.insert(immPreEvt);

					if(checkSdRcCreation(trans, ancestorSet1, C))
					{
						nb_events++;
						UnfoldingEvent *e = new UnfoldingEvent(nb_events, trans, ancestorSet1);
						exC.insert(e);
					}
				}
				}

	//else if last event is a Test
	if (C.lastEvent->transition.actor_id == trans.actor_id or
			(C.lastEvent->transition.actor_id != trans.actor_id  and C.lastEvent->transition.type =="Test"))
	{
		EventSet ansestors; ansestors.insert(C.lastEvent);
		if (not enableChk ) ansestors.insert(immPreEvt);
		if(checkSdRcCreation(trans, ansestors, C))
		{
			nb_events++;
			UnfoldingEvent *e = new UnfoldingEvent(nb_events, trans, ansestors);
			exC.insert(e);
		}

		for(auto it: C.events_) if (trans.isDependent(it->transition) and trans.actor_id != it->transition.actor_id)
		{
			// make sure no ancestor candidate event is in history of other ancestor candidate
			EventSet ansestors1; ansestors1.insert(C.lastEvent);

			if ( not lastEvtHist.contains(it) and (not immPreEvtHist.contains(it)))
			{	ansestors1.insert(it);
				EventSet itHist = it->getHistory();
				if( (not enableChk) and (not itHist.contains(immPreEvt))) ansestors1.insert(immPreEvt);

				if(checkSdRcCreation(trans, ansestors1, C))
				{
					nb_events++;
					UnfoldingEvent *e = new UnfoldingEvent(nb_events, trans, ansestors1);
					exC.insert(e);
				}
			}

		}
	}

// now combine send and test actions, forming a ancestors set including 3 events

if(C.lastEvent->transition.actor_id == trans.actor_id)
	for(auto sEvt : C.events_)
		if(sEvt->transition.type=="Isend" and sEvt->transition.mailbox_id == trans.mailbox_id and
				sEvt->transition.actor_id != trans.actor_id	and (not lastEvtHist.contains(sEvt)))
		{

			EventSet rEvtHist = sEvt->getHistory();
			for(auto tEvt : C.events_)
				if (tEvt->transition.type == "Test" and tEvt->transition.actor_id != trans.actor_id
						and tEvt->transition.mailbox_id == trans.mailbox_id)
			{
				UnfoldingEvent *testedEvent = C.findTestedComm(tEvt);
				if(testedEvent->transition.type == "Ireveive" and (not lastEvtHist.contains(tEvt))
						and not (rEvtHist.contains(tEvt))  and (not tEvt->getHistory().contains(sEvt)) )
				{
					EventSet ancestorsSet; ancestorsSet.insert(C.lastEvent); ancestorsSet.insert(sEvt);
					ancestorsSet.insert(tEvt);

					if(checkSdRcCreation(trans, ancestorsSet, C))
					{
						nb_events++;
						UnfoldingEvent *e = new UnfoldingEvent(nb_events, trans, ancestorsSet);
						exC.insert(e);


					}
				}
			}
}


	return exC;

}



EventSet createIreceiveEvts(Transition trans, Configuration C){
	bool enableChk = false;

	EventSet exC, EvtSet, causalityEvts, ancestorSet;
	UnfoldingEvent *testedEvt, *immPreEvt;

	/* if trans is not dependent with the last transition -> return */

	if (C.lastEvent->transition.type =="Test" and C.lastEvent->transition.actor_id != trans.actor_id) {
	// get the communication tested by Test
		testedEvt = C.findTestedComm(C.lastEvent);

	// two sends or two receives can not be in the same communication -> not denpendent
			if (trans.type == testedEvt->transition.type or trans.mailbox_id != testedEvt->transition.mailbox_id )
			 return EvtSet;
		}


	//if trans.id ==0 => trans is always enabled do not need to check enable condition ?.
	if (trans.id == 0 or C.lastEvent->transition.actor_id == trans.actor_id)
		enableChk = true;
	/* enableChk = true -> trans is ensured enabled or his pre evt is in the causalityEvts  */
	else if (C.lastEvent->transition.actor_id != trans.actor_id and (not enableChk)){
	//else find it in actorMaxEvent and check where it is in the history of last Evt
			immPreEvt = C.findActorMaxEvt(trans.actor_id);
			if (C.lastEvent->getHistory().contains(immPreEvt))
				enableChk = true;
	}


	immPreEvt = C.findActorMaxEvt(trans.actor_id);
	EventSet lastEvtHist = C.lastEvent->getHistory();
	EventSet immPreEvtHist ; if (trans.id != 0)  immPreEvtHist = immPreEvt->getHistory();

	ancestorSet.insert(C.lastEvent);

	// if last event is preEvt(trans) always create a new event.
		if( C.lastEvent->transition.actor_id == trans.actor_id)
		{
		nb_events++;
		UnfoldingEvent *e = new UnfoldingEvent(nb_events, trans, ancestorSet);
		exC.insert(e);
		}
		// else if last event is Ireceive try to create a new event .
		else if (C.lastEvent->transition.type =="Ireceive")
			 { if (enableChk)
					{
						nb_events++;
						UnfoldingEvent *e = new UnfoldingEvent(nb_events, trans, ancestorSet);
						exC.insert(e);
					}
			   else {	ancestorSet.insert(immPreEvt);
						nb_events++;
						UnfoldingEvent *e = new UnfoldingEvent(nb_events, trans, ancestorSet);
						exC.insert(e);
			}
				}

	// if last evt = preEvt(Ireceive) or last evt is a Ireceive, then try to combine with Test
	if(trans.isDependent(C.lastEvent->transition))
	 for(auto it : C.events_) if (it->transition.type =="Test" and it->transition.mailbox_id == trans.mailbox_id) {
		UnfoldingEvent *testedEvt;
		//retrive the communication tested by the the
			  testedEvt = C.findTestedComm(it);

		// tested action is Ireceive, create a new event if it can be marched with the Isend
		// make sure no ancestor candidate event is in history of other ancestor candidate

		if(testedEvt->transition.type =="Isend" and (not lastEvtHist.contains(it)))
				if ( not immPreEvtHist.contains(it) )
				{

					EventSet ancestorSet1;  ancestorSet1.insert(C.lastEvent);
					ancestorSet1.insert(it);
					EventSet itHist = it->getHistory();
					if ((not itHist.contains(immPreEvt)) and (not enableChk)) ancestorSet1.insert(immPreEvt);

					if(checkSdRcCreation(trans, ancestorSet1, C))
					{
						nb_events++;
						UnfoldingEvent *e = new UnfoldingEvent(nb_events, trans, ancestorSet1);
						exC.insert(e);
					}
				}
				}

	//else if last event is a Test
	if (C.lastEvent->transition.actor_id == trans.actor_id or
			(C.lastEvent->transition.actor_id != trans.actor_id  and C.lastEvent->transition.type =="Test"))
	{
		EventSet ansestors; ansestors.insert(C.lastEvent);
		if (not enableChk ) ansestors.insert(immPreEvt);
		if(checkSdRcCreation(trans, ansestors, C))
		{
			nb_events++;
			UnfoldingEvent *e = new UnfoldingEvent(nb_events, trans, ansestors);
			exC.insert(e);
		}

		for(auto it: C.events_) if (trans.isDependent(it->transition) and trans.actor_id != it->transition.actor_id)
		{
			// make sure no ancestor candidate event is in history of other ancestor candidate
			EventSet ansestors1; ansestors1.insert(C.lastEvent);

			if ( not lastEvtHist.contains(it) and (not immPreEvtHist.contains(it)))
			{	ansestors1.insert(it);
				EventSet itHist = it->getHistory();
				if( (not enableChk) and (not itHist.contains(immPreEvt))) ansestors1.insert(immPreEvt);

				if(checkSdRcCreation(trans, ansestors1, C))
				{
					nb_events++;
					UnfoldingEvent *e = new UnfoldingEvent(nb_events, trans, ansestors1);
					exC.insert(e);
				}
			}

		}
	}

// now combine send and test actions, forming a ancestors set including 3 events

if(C.lastEvent->transition.actor_id == trans.actor_id)
	for(auto rEvt : C.events_)
		if(rEvt->transition.type=="Ireceive" and rEvt->transition.mailbox_id == trans.mailbox_id and
				rEvt->transition.actor_id != trans.actor_id	and (not lastEvtHist.contains(rEvt)))
		{
			EventSet rEvtHist = rEvt->getHistory();
			for(auto tEvt : C.events_)
				if (tEvt->transition.type == "Test" and tEvt->transition.actor_id != trans.actor_id
						and tEvt->transition.mailbox_id == trans.mailbox_id)
			{
				UnfoldingEvent *testedEvent = C.findTestedComm(tEvt);
				if(testedEvent->transition.type == "Isend" and (not lastEvtHist.contains(tEvt))
						and not (rEvtHist.contains(tEvt))  and (not tEvt->getHistory().contains(rEvt)) )
				{
					EventSet ancestorsSet; ancestorsSet.insert(C.lastEvent); ancestorsSet.insert(rEvt);
					ancestorsSet.insert(tEvt);

					if(checkSdRcCreation(trans, ancestorsSet, C))
					{
						nb_events++;
						UnfoldingEvent *e = new UnfoldingEvent(nb_events, trans, ancestorsSet);

						exC.insert(e);
					}
				}
			}
}
	return exC;

}






/* given a send/receive transition and a history candidate represented by maxmal event (ancestors), this function
   check whether we can create a event ?
*/

EventSet createSendReceiveEvts(Transition trans, Configuration C, std::list<EventSet> maxEvtHistory){
EventSet exC, EvtSet, causalityEvts, ancestorSet, H;
UnfoldingEvent *testedEvt, *immPreEvt;
bool chk = false;


/* if trans is not dependent with the last transition -> return
 if the last transition is a test -> check whether they concern the same communication ?*/

if (C.lastEvent->transition.type =="Test" and C.lastEvent->transition.actor_id != trans.actor_id) {

// get the communication tested by Test
	for (auto evt: C.events_) if (evt->transition.actor_id == C.lastEvent->transition.actor_id
			and evt->transition.commId == C.lastEvent->transition.commId and evt->transition.type !="Test")

			{ testedEvt = evt; break;}
	// two sends or two receives can not be in the same communication -> not denpendent
		if (trans.type == testedEvt->transition.type or trans.mailbox_id != testedEvt->transition.mailbox_id )
			 return EvtSet;
	}

// add causality evts to causalityEvts set, firstly add last event to causalityEvts
causalityEvts.insert(C.lastEvent);

/* add the immediate precede evt of transition trans to the causalityEvts
 *  used to make sure trans is enabled (Ti is enlabled if Ti-1 is aready fined)
 chk == true =>  causalityEvts contains immediate precede event of trans Or the immediate precede event is in history of lastEvt.
 */

if (trans.id == 0 or C.lastEvent->transition.actor_id == trans.actor_id)
	chk = true; //if trans.id ==0 => trans is always enabled do not need to check enable condition ?.



/* chk = true -> trans is ensured enabled or his pre evt is in the causalityEvts  */

else if (C.lastEvent->transition.actor_id != trans.actor_id and (not chk)){

	//if immediate precede evt in maxEvent, add it to the causalityEvts

	for (auto evt : C.maxEvent.events_)
		if (trans.actor_id == evt->transition.actor_id) {
			causalityEvts.insert(evt);
			chk = true;
			break;
		}

	//else find it in actorMaxEvent and check where it is in the history of last Evt

	if (not chk) {

		immPreEvt = C.findActorMaxEvt(trans.actor_id);
		if (C.lastEvent->getHistory().contains(immPreEvt))
			chk = true;
	}
}



// compute all events are dependent with the transition trans.

	for (auto evt : C.maxEvent.events_)
		if ((trans.isDependent(evt->transition)
				or (evt->transition.type == "Test"
						and evt->transition.mailbox_id == trans.mailbox_id))
				and (not causalityEvts.contains(evt)))
			ancestorSet.insert(evt);


	if (checkSdRcCreation(trans, causalityEvts, C) and chk) {
		nb_events++;
		UnfoldingEvent *e = new UnfoldingEvent(nb_events, trans, causalityEvts);
		exC.insert(e);  }

	EventSet cause;
	EventSet exC1;

	C.createEvts(C, exC1, trans, causalityEvts, cause, ancestorSet, chk,
			immPreEvt);
	exC = exC.makeUnion(exC, exC1);

	//remove last MaxEvt, sine we already used it before
	maxEvtHistory.pop_back();


	/*2. We now compute new evts by using MaxEvts in the past, but we have to ensure that
	 * the ancestor events (used to generate history candidate) are not in history of the evts in the causalityEvts
	 */
	std::set<int> intS;
	/* get all events in the history of the evts in causalityEvts */
	for (auto evt : causalityEvts.events_) {
		EventSet H1;
		H1 = evt->getHistory();
		H = H.makeUnion(H, H1);
	}

	for (auto evtSet : maxEvtHistory) {

		EventSet evtS;

		// if intS1 is not empty then retrive thier events, create new events from all subsets
		if (not evtSet.empty()) {


			// retrieve  evts from intS1 (intS1 store id of evts in C whose transitions are dependent with trans)
			EventSet evtSet1;
			for (auto evt : evtSet.events_)
								if ( (not H.contains(evt) ) and (evt->transition.isDependent(trans)	or (evt->transition.type == "Test"	and trans.mailbox_id== evt->transition.mailbox_id)))

						evtSet1.insert(evt);

			EventSet exC1, cause;

			C.createEvts(C, exC1, trans, causalityEvts, cause, evtSet1,
					chk, immPreEvt);

			exC = exC.makeUnion(exC, exC1);
		}

	}

return exC;



}


void UnfoldingChecker::extend(std::set<Actor> actors, Configuration C,
		std::list<EventSet> maxEvtHistory, EventSet & exC, EventSet& enC) {

	// in the initial state each actor creates one event
	EventSet causes;
	if (C.empty()) {
		for (auto p : actors) {
			nb_events++;
			UnfoldingEvent *newEvent = new UnfoldingEvent(nb_events, p.trans[0],
					causes);
			if (not U.contains(newEvent)) {
				U.insert(newEvent);
				enC.insert(newEvent);
				exC.insert(newEvent);


			} else {
				enC.insert(U.find(newEvent));
				exC.insert(U.find(newEvent));
			}
		}

		} else {

		// get all enabled transitions at current appState
		std::set<Transition> enabledTransitions;
		enabledTransitions = C.lastEvent->appState.getEnabledTransition();

		// try to create new events from a enabled transition and every maximal_Evt history in maxEvtHistory of C

		for (auto trans : enabledTransitions) {
			// if trans is not a wait action, and is dependent with the transition of last event
			if (trans.isDependent(C.lastEvent->transition)
					and trans.type != "Wait" and trans.type != "Test" and trans.type != "Isend"
							and trans.type != "Ireceive" and trans.type != "localComp" ) {

				EventSet exC1, causalityEvts;

				// in maxEvent of C, we only consider events having transitions that are dependent with trans
				if (trans.read_write < 2) {
					std::list<EventSet> maxEvtHistory1 = maxEvtHistory;

					exC1 = computeExt(C, maxEvtHistory1, trans);

				}

					for (auto newEvent : exC1.events_)
					if (not U.contains(newEvent)) {
														U.insert(newEvent);
														exC.insert(newEvent);
													} else
														exC.insert(U.find(newEvent));


			}

			// ELSE IF THE TRANSITION IS A isend or i receive

			else if ( trans.type == "Isend" and ( trans.isDependent(C.lastEvent->transition)
					or (C.lastEvent->transition.type =="Test" and C.lastEvent->transition.mailbox_id == trans.mailbox_id)) ) {
				EventSet exC1 = createIsendEvts(trans, C);
				for (auto newEvent : exC1.events_)
					if (not U.contains(newEvent)) {
											U.insert(newEvent);
											exC.insert(newEvent);
											} else
												exC.insert(U.find(newEvent));


			}

			else if ( trans.type == "Ireceive"  and ( trans.isDependent(C.lastEvent->transition)
					or (C.lastEvent->transition.type =="Test" and C.lastEvent->transition.mailbox_id == trans.mailbox_id)) ) {
				EventSet exC1 = createIreceiveEvts(trans, C);
				for (auto newEvent : exC1.events_)
					if (not U.contains(newEvent)) {
											U.insert(newEvent);
											exC.insert(newEvent);
											} else
												exC.insert(U.find(newEvent));

			}
			// ELSE IF THE TRANSITION IS A WAIT ACTION
			else if (trans.type == "Wait") {

				// check which kind of communication (send/receive) waited by the wait?
				UnfoldingEvent * evt;
					for(auto evt1: C.events_) if (evt1->transition.actor_id == trans.actor_id and
							evt1->transition.commId == trans.commId) {evt = evt1; break;}

				/* we only call function createWaitEvt if the last action is send/ or receive
				  or dependent with the wait (transition in the same actor) */

				string comType = C.lastEvent->transition.type;
				string comType1 = evt->transition.type;

			if(C.lastEvent->transition.actor_id == trans.actor_id or
						(comType=="Isend" and comType1 == "Ireceive") or (comType=="Ireceive" and comType1 == "Isend"))
				{	EventSet newEvts = createWaitEvt(evt,C, trans);

				//EventSet unionSet = U.makeUnion(U,gD1);

									for (auto newEvent : newEvts.events_)
									if (not U.contains(newEvent)) {
																		U.insert(newEvent);
																		exC.insert(newEvent);
																	} else
																		exC.insert(U.find(newEvent));

				}


			}

			// ELSE IF THE TRANSITION IS A TEST ACTION

			else if (trans.type == "Test") {

			// check which kind of communication (send/receive) tested by the test?

							UnfoldingEvent * event;
								for(auto evt1: C.events_) if (evt1->transition.actor_id == trans.actor_id and
										evt1->transition.commId == trans.commId) {event = evt1; break;}

			/* we only call function createTestEvt if the last action is send or receive
			   or dependent with the test (transition in the same actor) */

							string comType = C.lastEvent->transition.type;
							string comType1 = event->transition.type;

						if(C.lastEvent->transition.actor_id == trans.actor_id or
									(comType=="Isend" and comType1 == "Ireceive") or (comType=="Ireceive" and comType1 == "Isend"))

						{
							EventSet newEvts =createTestEvt(exC,  event, C, trans);

					for (auto newEvent : newEvts.events_)
						if (not U.contains(newEvent)) {

							U.insert(newEvent);
							exC.insert(newEvent);

						} else 	exC.insert(U.find(newEvent));


						}

			}

			else if (trans.type == "localComp" and C.lastEvent->transition.actor_id == trans.actor_id) {
				EventSet ancestors; ancestors.insert(C.lastEvent);
				nb_events++;
				UnfoldingEvent *newEvent = new UnfoldingEvent(nb_events, trans, ancestors);
				if (not U.contains(newEvent)) {
					U.insert(newEvent);
					exC.insert(newEvent);

				} else
					exC.insert(U.find(newEvent));



			}

		}


		for (auto evt : exC.events_) {
			/* add new event evt to enC if evt's transition is not dependent with any transition of a event
			 which is in C and is not in history of evt */
			bool chk = true;
			EventSet evtHisty = evt->getHistory();

			/*for (auto evt1 : C.events_)
				if (not evtHisty.contains(evt1))
						 {
							if (evt1->transition.isDependent(evt->transition)) {chk = false; break;}
							else if( (evt->transition.type =="Test" and (evt1->transition.type=="Isend" or evt1->transition.type=="Ireceive")) or
									(evt1->transition.type =="Test" and (evt->transition.type=="Isend" or evt->transition.type=="Ireceive")))
								  if (evt->concernSameComm(evt,evt1)) {chk = false; break;}
				}*/

			for(auto it: C.events_) if (it->isConflict(it,evt)) chk = false;

			if (chk)
				enC.insert(evt);

		}
	}
}

void UnfoldingChecker::explore(Configuration C,
		std::list<EventSet> maxEvtHistory, EventSet D, EventSet A,
		UnfoldingEvent* currentEvt, EventSet prev_exC, std::set<Actor> actors) {

	UnfoldingEvent *e;
	EventSet enC, exC = prev_exC;// exC.erase(currentEvt);

	exC.erase(currentEvt);

	// exC = previous exC - currentEvt + new events

	extend(actors, C, maxEvtHistory, exC, enC);


	for(auto it: C.events_) exC.erase(it);


	// return when enC \subset of D

	bool chk = true;
	if (enC.size() > 0 ) for (auto evt: enC.events_) if (not D.contains(evt)) {chk = false; break;}


	if (chk) {

		if (C.size() > 0) {

			nb_traces++;
			std::cout << "\n Exploring executions: " << nb_traces << " : \n";
			std::cout
					<< "\n-----------------------------------------------------------"
							"-------------------------------------------------------------------"
							"-------------------\n";
			for (auto evt : C.events_) {
				std::cout << " --> ";
				evt->print();
			}

/*			if(C.size() < 16)
			{std::cout <<" \n co bien nhe ";
			std::cout <<" \n co bien nhe ";
			usleep(999999999);
			}*/
			std::cout
					<< "\n-----------------------------------------------------------"
							"-------------------------------------------------------------------"
							"-------------------\n";
			std::cout << "\n";


		}
		return;
	}



	if (A.empty()) {
		e = enC.begin();
	} else {



		// if A is not empty, chose one event in the intersection of A and enC
		for (auto evt : A.events_)
			if (enC.contains(evt)) {

				e = evt;
				break;

			}
	}




	std::cout << " exploring --------------------> :";
	e->print();
	std::cout<<"\n";


	State nextState = currentEvt->appState.execute(e->transition);

	e->appState = nextState;

	// UnfoldingEvent* newEvent = e + e.transition;
	Configuration C1 = C; C1.insert(e);

	C1.updateMaxEvent(e);

	// update history of the maximal events by adding maximal events of the current Configuration (adding intSet)
	std::list<EventSet> maxEvtHistory1 = maxEvtHistory;


	maxEvtHistory1.push_back(C1.maxEvent);



	explore(C1, maxEvtHistory1, D, A.minus(e), e, exC.minus(e), actors);

	EventSet J, U1;
	EventSet Uc = U;


		EventSet D1 = D; D1.insert(e);
		EventSet D2 = D; D2.insert(e);



		EventSet J1;

		J = KpartialAlt(D1 , C);
		//J = computeAlt(D2, C);

	if (not J.empty()) {


		J.subtruct(C);
		explore(C, maxEvtHistory, D1, J, currentEvt, prev_exC, actors);

	}


	remove(e, C, D);


}






void UnfoldingChecker::remove(UnfoldingEvent* e, Configuration C, EventSet D) {

	EventSet unionSet, res, res1;
	unionSet = unionSet.makeUnion(C, D);

	// building Qcdu
	for (auto e1 : U.events_) {
		for (auto e2 : unionSet.events_)
			// add e1 which is immediate conflict with one event in C u D to res


			if (e1->isImmediateConflict1(e1,e2)) {
				res.insert(e1);
				break;
			}

	}

	res1 = res;
	for (auto e1 : res1.events_) {
		EventSet h = e1->getHistory();
		res = res.makeUnion(res, h);

	}

	res = res.makeUnion(res, unionSet);
	// move e from U to G if the condition is satisfied

	if (not res.contains(e)) {
		U.erase(e);

		//G.insert(e);
	}

	// move history of ê from U to G
	EventSet U1 = U;
	for (auto evt : U1.events_)

	{	if (evt->isImmediateConflict1(evt,e)) {

			EventSet h = evt->getHistory();
			h.insert(evt);

			for (auto e2 : h.events_)
				if (not res.contains(e2)) {
					U.erase(e2);
				//	G.insert(e2);
				}
		}

	}

}


/*

void UnfoldingChecker::remove(UnfoldingEvent* e, Configuration C, EventSet D) {

	EventSet unionSet, res, res1, U1 ;
	unionSet = unionSet.makeUnion(C, D);

	// building Qcdu
	for (auto e1 : U.events_)
		for (auto e2 : unionSet.events_)
				if (e1->isConflict(e1,e2)) res.insert(e1);


res = res.makeUnion(res, unionSet);
	U1 = U;
for (auto it: U1.events_)


	if (not res.contains(it))
	{	U.erase(it);

		//G.insert(e);
	}



}
*/






