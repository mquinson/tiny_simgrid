#ifndef EVENTSET_H
#define EVENTSET_H

#include <iostream>
#include <set>

using namespace std;

class EventSet
{
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

#endif // EVENTSET_H
