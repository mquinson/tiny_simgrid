#include "UnfoldingChecker.hpp"

#include <unistd.h>

UnfoldingEvent::UnfoldingEvent(int nb_events, Transition t, EventSet causes) {

	this->id = nb_events;
	this->causes = causes;
	this->transition = t;
}

void UnfoldingEvent::print() {

	std::cout << "e" << this->id << " =  < t" << this->transition.id << "-p"
			<< this->transition.actor_id << "(";
	if (this->transition.type.length() > 1)
		std::cout << this->transition.type << ")" << "," << "(";
	if (this->causes.empty())
		std::cout << "-) >";
	else {
		for (auto evt : this->causes.events_)
			std::cout << "e" << evt->id << ",";
		std::cout << " ) >";
	}

}

// Recursively compute the history of a given event by adding the causes of all ancestors
EventSet UnfoldingEvent::getHistory() const {
	if (causes.empty()) // No direct ancestor => empty history
		return causes;
	else {
		//EventSet res = causes;
		EventSet res;
		for (auto ancestor : causes.events_) {
			EventSet h1;

			// if event ancestor is already in history set -> we do not need to get it's history

			if (not res.contains(ancestor))
				h1 = ancestor->getHistory();
			h1.insert(ancestor);
			res = res.makeUnion(res, h1);
		}
		return res;
	}
}

bool UnfoldingEvent::inHistory(UnfoldingEvent *otherEvent) {
	if (this->getHistory().contains(otherEvent))
		return true;
	return false;

}

/*Check whether 2 events a Test and a Send/Receive concern the same communication,
 * Here the events are supposed that they are not causality related
 * */

bool UnfoldingEvent::concernSameComm(UnfoldingEvent*event, UnfoldingEvent* otherEvent){
	UnfoldingEvent*testEvt, *SdRcEvt, *testedEvt;


	//std::cout <<" \n hien thi evet trong ham concern :";
	//event->print();
	//otherEvent->print();
	//std::cout <<" \n ham concern 1: \n";


	if (event->transition.mailbox_id != otherEvent->transition.mailbox_id) return false;

	if (event->transition.type=="Test") {testEvt = event; SdRcEvt = otherEvent;}
	else {testEvt = otherEvent; SdRcEvt = event;}

	// 2 sends or 2 receives can not concern the same communication

    int comId = testEvt->transition.commId;


	EventSet testEvtH = testEvt->getHistory();
	EventSet SdRcEvtH = SdRcEvt->getHistory();

	for(auto it : testEvtH.events_)
		if ( it->transition.actor_id == testEvt->transition.actor_id and it->transition.commId ==comId)
			testedEvt = it;

	if (testedEvt->transition.type == SdRcEvt->transition.type) return false;

	int mbId = testedEvt->transition.mailbox_id;


	//std::cout <<" \n ham concern 2: \n";


	if (testedEvt->transition.type =="Isend") {

		EventSet testedEvtH = testedEvt->getHistory();
		int nbSend =0, nbReceive =0;

		//count the number of Isend event before testedEvt
		for (auto it: testedEvtH.events_)  if (it->transition.mailbox_id ==  mbId and it->transition.type == "Isend") nbSend++;

		//count the number of Ireceive event before SdRcEvt
			for (auto it: SdRcEvtH.events_)  if (it->transition.mailbox_id ==  mbId and it->transition.type == "Ireceive") nbReceive++;

		if(nbSend == nbReceive) return true;

	}


	if (testedEvt->transition.type =="Ireceive") {

		//std::cout <<" \n ham concern 3: \n";


		EventSet testedEvtH = testedEvt->getHistory();
		int nbSend =0, nbReceive =0;

		//count the number of Receive event before testedEvt
		for (auto it: testedEvtH.events_)  if (it->transition.mailbox_id ==  mbId and it->transition.type == "Ireceive") nbReceive++;

		//count the number of Isend event before SdRcEvt
		for (auto it: SdRcEvtH.events_)  if (it->transition.mailbox_id ==  mbId and it->transition.type == "Isend") nbSend++;

		//if (nbSend == nbReceive) std::cout<<"\n CONCERN the same COMM nbsend =" << nbSend <<" nb receive = "<< nbReceive << "  \n";
		if(nbSend == nbReceive) return true;

	}

	return false;

}



/** @brief check for conflict in the history of provided events
 *
 * In the paper, this.isConflict(other) is written "this # other"
 */

bool UnfoldingEvent::isConflict(UnfoldingEvent*event, UnfoldingEvent* otherEvent) {

	// event e should not conflict with itself

	//if(event->conflictEvts.contains(otherEvent) or otherEvent->conflictEvts.contains(event) ) return true;

	if (*event == *otherEvent)
		return false;
//	std::cout<<"\n trong ham cflict";

	EventSet h1, h2;
	h1 = event->getHistory();
	h2 = otherEvent->getHistory();


	// checking causality relation, if they are in a causality relation return false
	if (h1.contains(otherEvent) or h2.contains(event))
		return false;

	// check direct conflict
	if (event->transition.isDependent(otherEvent->transition))
		return true;

	//  if 2 event they have the same causes, just check their last transition
	if (event->causes == otherEvent->causes)
		return event->transition.isDependent(otherEvent->transition);

	// if not, then check dependent relation on their full histories

	else {

		h1.insert(event);
		h2.insert(otherEvent);
		EventSet his = h1;
		//FIXME remove all common events
		for (auto evt : his.events_)
			if (h2.contains(evt)) {
				h1.erase(evt);
				h2.erase(evt);
			}

		return h1.depends(h2);

	}
//	std::cout<<"\n trong ham cflict6";

	return false;
}

/** @brief Checks if current event is in immediate conflict with the provided one
 *
 * For that, there is two conditions to meet:
 *  - both events are in conflict (there is a conflict in their histories)
 *  -      Union(hist1,       hist2, evt2) is a valid configuration
 *    AND  Union(hist1, evt1, hist2)       is a valid configuration
 *
 * In the paper, e1.isImmediate(e2) will be written "e1 #ⁱ e2"
 */

bool UnfoldingEvent::isImmediateConflict(UnfoldingEvent *evt1, UnfoldingEvent *evt2) {

	// event e should not conflict with itself
	if (*evt1 == *evt2)
		return false;

	// The first condition is easy to check
	if (not evt1->isConflict(evt1 ,evt2))
		return false;

	// Now, check the second condition
	EventSet hist1 = evt1->getHistory();
	EventSet hist2 = evt2->getHistory();

	// First compare the existing configurations

	// romove all common events

	EventSet hist11 = hist1, hist21 = hist2;


	for (auto e1 : hist2.events_)
		if (evt1->isConflict(evt1,e1))return false;

	// Compare the first config to the second new event
	for (auto e1 : hist1.events_)
		if (evt2->isConflict(evt2,e1))
			return false;
	// Every tests passed
	return true;
}




bool UnfoldingEvent::isImmediateConflict1(UnfoldingEvent *evt1, UnfoldingEvent *evt2) {

	// event e should not conflict with itself
	if (*evt1 == *evt2)
		return false;


	bool chk1 = false, chk2 = false ;

/*	if (evt1->id == 28 and evt2->id ==19) if (evt1->transition.isDependent(evt2->transition)){

		std::cout <<"\n hai tran depend voi nhau \n ";


	}*/


	if (not evt1->transition.isDependent(evt2->transition))
		{

		chk1 = true; chk2 = true;
		if (evt1->transition.type =="Test" and (evt2->transition.type =="Isend" or evt2->transition.type == "Ireceive"))
			{ if( not evt1->concernSameComm(evt1,evt2))  return false;
			  else  {   chk2 = false;  }
			}

		if (evt2->transition.type =="Test" and (evt1->transition.type =="Isend" or evt1->transition.type == "Ireceive"))
			{ if( not evt1->concernSameComm(evt1,evt2))  return false;
				else {  chk2 = false;}

			}

		}
	// 2 transitions are not depend and they are one is test other one is send/receive  -> return false


	if (chk1 and chk2 )
		return false;

	// Now, check the second condition
	EventSet hist1 = evt1->getHistory();
	EventSet hist2 = evt2->getHistory();
	EventSet hist11 = hist1, hist21 = hist2;

	// if causality ralated - > no immidiate conflict
	if (hist1.contains(evt2) or hist2.contains(evt1)) return false;



	for (auto e1 : hist1.events_) if (hist2.contains(e1)) {hist11.erase(e1); hist21.erase(e1);}

	//if(hist11.empty() or hist21.empty()) if (evt1->id == 28 and evt2->id == 19) std::cout<<" \n kt depend trong ham isImmidiate empy no roi";

	//std::cout <<"\n  kiem tra dk depends \n ";



	EventSet evtS1, evtS2;

	evtS1.insert(evt1); evtS2.insert(evt2);


	if(hist11.depends(hist21) or  evtS1.depends(hist21) or evtS2.depends(hist11)) {

	//std::cout <<" DEPENDS HISTORY roi\n ";

	return false;}


	//std::cout <<"se tra ve true nhe ### \n";

	return true;
}









// checking conflict relation between one event and one configuration or one history, it used when computing enC
// there is a better way by checking the event with maximal events in the configuration, (change type of enC )
bool UnfoldingEvent::conflictWithConfig(UnfoldingEvent *event, Configuration config) {
	if (config.size() == 0)
		return false;
	// we don't really need to check the whole config. The maximal event should be enough.
	for (auto evt : config.maxEvent.events_)
		if (event->isConflict(event, evt))
			return true;
	return false;
}

// this operator is used for ordering in a set (need a key)
bool UnfoldingEvent::operator<(const UnfoldingEvent& other) const {
	if ((this->transition.actor_id < other.transition.actor_id)
			or (this->transition.id < other.transition.id)
			or (not (this->causes == other.causes)))
		return true;
	return false;
}

/** @brief check semantic equality (same transition, same causes) */
bool UnfoldingEvent::operator==(const UnfoldingEvent& other) const {

if ((this->transition.id != other.transition.id) or (this->transition.actor_id != other.transition.actor_id)) return false;
if (this->causes.size() != other.causes.size()) return false;

for (auto it : this->causes.events_) {
			bool chk1 = false;
			for (auto it1 : other.causes.events_)
				if (*it == *it1) {
					chk1 = true;
					break;
				}
			if (not chk1)return false;

		}

return true;


}

void Configuration::updateMaxEvent(UnfoldingEvent *e) {
	this->lastEvent = e;
	// update the maximal events for current Conf removing causes from maxEvent and adding e to the maxEvent
	for (auto evt : e->causes.events_) {
		maxEvent.erase(evt); //setMaxEvents.erase(evt->id);

	}
	maxEvent.insert(e);
	/* update the maximal events for the actor=>
	 removing the evt shares the same actor with e, then adding e to the actorMaxEvent */

	for (auto evt : actorMaxEvent.events_)
		if (evt->transition.actor_id == e->transition.actor_id)
			actorMaxEvent.erase(evt);
	actorMaxEvent.insert(e);

}




Configuration Configuration::plus(UnfoldingEvent *evt) {
	Configuration res;

	res.events_ = this->events_;
	res.maxEvent = this->maxEvent;
	res.actorMaxEvent = this->actorMaxEvent;
	if (not res.contains(evt)) res.events_.insert(evt);
	return res;
}




bool EventSet::contains(UnfoldingEvent *e) {
	for (auto evt : this->events_)
		if (*evt == *e)
			return true;
	return false;
}

void   EventSet::subtruct(EventSet otherSet) {
	for (auto evt : otherSet.events_)
		if (this->contains(evt)) this->erase(evt);

}

UnfoldingEvent* EventSet::find(UnfoldingEvent *e) {

	for (auto evt : this->events_)
		if (*evt == *e) {
			return evt;
		}
}

UnfoldingEvent * Configuration :: findTestedComm(UnfoldingEvent *testEvt){
	for (auto it : this->events_)
		if (it->transition.commId == testEvt->transition.commId and
				it->transition.type != "Test" and it->transition.actor_id == testEvt->transition.actor_id)
			return it;
}


/** @brief Check if I'm dependent with another EventSet
 * Here we suppose that 2 given event sets do not have common events
 *  */

bool EventSet::depends(EventSet s2) {
	if(this->events_.empty() or s2.events_.empty())
		return false;

	for (auto e1 : this->events_)
		for (auto e2 : s2.events_)
				if (e1->transition.isDependent(e2->transition))	return true;
				else if ((e1->transition.type =="Test" and (e2->transition.type =="Isend" or e2->transition.type == "Ireceive")) or
						(e2->transition.type =="Test" and (e1->transition.type =="Isend" or e1->transition.type == "Ireceive")))
								if(e1->concernSameComm(e1,e2)) return true;

	return false;
}

bool EventSet::isConfig() {
	if ((this->size() == 1) && (this->begin()->causes.empty()))
		return true;

	// checking conflict relation between one event and all other events in the set
	for (auto e1 : events_) {
		for (auto e2 : events_) {
			if (*e1 == *e2)
				continue;

			if (e1->isConflict(e1,e2))
				return false;
		}
		// Every event of the history should be in the set
		for (auto ancestor : e1->getHistory().events_)
			if (not (this->contains(ancestor)))
				return false;
	}

	return true;
}

EventSet EventSet::makeUnion(EventSet s1, EventSet s2) {
	EventSet res= s1;
//	res.events_.insert(s1.events_.begin(), s1.events_.end());
//	res.events_.insert(s2.events_.begin(), s2.events_.end());

	for (auto evt : s2.events_)
		res.insert(evt);

	return res;
}

EventSet EventSet::makeIntersection(EventSet s1, EventSet s2) {
	EventSet res;
	std::set_intersection(s1.events_.begin(), s1.events_.end(),
			s2.events_.begin(), s2.events_.end(),
			std::inserter(res.events_, res.events_.begin()));
	return res;
}

EventSet EventSet::minus(UnfoldingEvent *evt) {

	EventSet res;
	res.events_ = this->events_;
	for (auto e : this->events_)
		if (*e == *evt)
			res.erase(e);

	return res;
}

EventSet EventSet::plus(UnfoldingEvent *evt) {
	EventSet res;
	res.events_ = this->events_;
	if(not res.contains(evt)) res.events_.insert(evt);
	return res;
}


size_t EventSet::size() const{
	return events_.size();
}

bool EventSet::empty() const {
	return this->events_.empty();
}

UnfoldingEvent* EventSet::begin() const {
	return *events_.begin();
}

UnfoldingEvent* EventSet::end() const {
	return *events_.end();
}

bool EventSet::operator==(const EventSet& other) const {

	return this->events_ == other.events_;

}
void EventSet::insert(UnfoldingEvent* e) {
	if (not this->contains(e))
		events_.insert(e);
}

void EventSet::erase(UnfoldingEvent *e) {
	std::set<UnfoldingEvent*> evtS = this->events_;

	for (auto it : evtS)
	if(*it == *e)  this->events_.erase(it);

}

bool EventSet::conflictWithEvt(UnfoldingEvent *e) {
	for (auto evt : this->events_)
		if (evt->isConflict(evt,e))
			return true;
	return false;
}

bool EventSet::isEmptyIntersection(EventSet evtS1, EventSet evtS2) {

	if(evtS1.size() ==0 or evtS2.size() ==0) return false;

	for (auto evt : evtS2.events_)
		if (evtS1.contains(evt))
			return false;

	return true;
}
