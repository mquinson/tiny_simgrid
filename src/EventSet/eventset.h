#ifndef EVENTSET_H
#define EVENTSET_H

#include <iostream>
#include <set>
#include <algorithm>
#include "../UnfoldingEvent/unfoldingevent.h"

using namespace std;

//namespace event {

class EventSet
{
public:
    bool contains(UnfoldingEvent* e);
    UnfoldingEvent* find(UnfoldingEvent* e);
    void subtruct(EventSet otherSet);
    bool depends(EventSet s2);
    bool isConfig();
    std::set<UnfoldingEvent*> events_;
    bool conflictWithEvt(UnfoldingEvent* e);
    bool isEmptyIntersection(EventSet evtS1, EventSet evtS2);

    static EventSet makeUnion(EventSet s1, EventSet s2);
    static EventSet makeIntersection(EventSet s1, EventSet s2);
    const UnfoldingEvent* first();

    size_t size() const { return events_.size(); }
    bool empty() const { return this->events_.empty(); }
    UnfoldingEvent* begin() const { return *events_.begin(); }
    UnfoldingEvent* end() const { return *events_.end(); }

    void insert(UnfoldingEvent*);
    void erase(UnfoldingEvent*);
    inline bool operator==(const EventSet& other) const { return this->events_ == other.events_; }

    EventSet minus(UnfoldingEvent* evt);
    EventSet plus(UnfoldingEvent*);
};

//}

#endif // EVENTSET_H
