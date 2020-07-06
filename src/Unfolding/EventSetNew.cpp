#include "EventSetNew.h"
#include <algorithm>

namespace tiny_simgrid {
namespace mc {

template<class T>
std::set<std::unique_ptr<T>> EventSetNew<T>::get_events() const {
    return events_;
}

template<class T>
void EventSetNew<T>::set_events(std::set<std::unique_ptr<T>> events) {
    events_ = std::move(events);
}

template<class T>
size_t EventSetNew<T>::size() const {
    return events_.size();
}

template<class T>
bool EventSetNew<T>::empty() const {
    return this->events_.empty();
}

template<class T>
T* EventSetNew<T>::begin() {
    return (*events_.begin())->get();
}

template<class T>
T* EventSetNew<T>::end() {
    return (*events_.end())->get();
}

template<class T>
void EventSetNew<T>::insert(T* event) {
    auto contains_ = contains(events_, event);
    if (!contains_)
        events_.insert(std::unique_ptr<T>(event));
}

template<class T>
void EventSetNew<T>::erase(T* event) {
    std::for_each(std::begin(events_), std::end(events_),
                  [=](std::unique_ptr<T> const& it) { if(*(it.get()) == *event) events_.erase(it); });
}

template<class T>
EventSetNew<T> EventSetNew<T>::minus(T* event) {
    EventSetNew<T> event_set(this);
    event_set.erase(event);
    return event_set;
}

template<class T>
EventSetNew<T> EventSetNew<T>::plus(T* event) {
    EventSetNew<T> event_set(this);
    event_set.insert(event);
    return event_set;
}

template<class T>
void EventSetNew<T>::subtract(EventSetNew<T> event_set)
{
    auto events_ = event_set.get_events();
    std::for_each(std::begin(events_), std::end(events_),
                  [&](std::unique_ptr<T> const& it) { this->erase(it.get()); });
}

// TODO: CHECK IT
template<class T>
bool EventSetNew<T>::operator==(const EventSetNew<T>& other) const {
    return this->events_ == other.events_;
}

template<typename T>
bool contains(std::set<std::unique_ptr<T>> value_set, T* value) {
    std::for_each(std::begin(value_set), std::end(value_set),
                  [=](std::unique_ptr<T> const& it) { if(*(it.get()) == *value) return true; });
    return false;
}

template<typename T>
bool is_empty_intersection(EventSetNew<T> event_set_1, EventSetNew<T> event_set_2) {
    if ((event_set_1.size() == 0) or (event_set_2.size() == 0))
        return false;
    auto events_1 = event_set_1.get_events();
    auto events_2 = event_set_2.get_events();
    std::for_each(std::begin(events_2), std::end(events_2),
                  [=](std::unique_ptr<T> const& it) {
        auto contains_ = contains(events_1, it.get());
        if(contains_)
            return false;
    }
    );
    return true;
}

template <typename T>
EventSetNew<T> make_union(EventSetNew<T> event_set_1, EventSetNew<T> event_set_2) {
    EventSetNew<T> result(event_set_1);
    auto events_2 = event_set_2.get_events();
    std::for_each(std::begin(events_2), std::end(events_2),
                  [&](std::unique_ptr<T> const& it) { result.insert(it.get()); });
    return result;
}

// TODO: CHECK IT
template<typename T>
EventSetNew<T> make_intersection(EventSetNew<T> event_set_1, EventSetNew<T> event_set_2) {
    EventSetNew<T> result;
    auto s1_begin = event_set_1.get_events().begin();
    auto s1_end = event_set_1.get_events().end();
    auto s2_begin = event_set_2.get_events().begin();
    auto s2_end = event_set_2.get_events().end();

    std::set<std::unique_ptr<T>> events;
    std::set_intersection(s1_begin, s1_end, s2_begin, s2_end,
                          std::inserter(events, events.begin()));

    result.set_events(events);
    return result;
}


// TODO: IMPLEMENTED - CHECK IT
// TODO: MOVE IT TO THE UNFOLDING_EVENT CALSS IMPLEMENTATION
///** @brief Check if I'm dependent with another EventSetNew
// * Here we suppose that 2 given EventSetNews do not have common events */
//template<typename T>
//bool depends(EventSetNew<T> event_set_1, EventSetNew<T> event_set_2)
//{
//    auto events_1 = event_set_1.get_events();
//    auto events_2 = event_set_2.get_events();
//    if (events_1.empty() or events_2.empty())
//        return false;

//    auto lambda = [&](std::unique_ptr<T> const& e1) {
//        for(auto e2 : events_2) {
//            if(e1->transitionis.isDependent(e2->transition))
//                return true;

//            auto c1 = (e1->transition.type == "Test" and
//                       (e2->transition.type == "Isend" or e2->transition.type == "Ireceive"));
//            auto c2 = (e2->transition.type == "Test" and
//                       (e1->transition.type == "Isend" or e1->transition.type == "Ireceive"));
//            if(c1 or c2) {
//                if (e1->concernSameComm(e1, e2))
//                    return true;
//            }

//        }
//    };

//    std::for_each(std::begin(events_1), std::end(events_1), lambda());
//    return false;
//}

} // namespace mc
} // namespace tiny_simgrid

