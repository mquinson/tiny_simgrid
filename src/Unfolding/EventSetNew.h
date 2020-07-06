#ifndef EVENTSET_H
#define EVENTSET_H

#include <memory>
#include <set>

namespace tiny_simgrid {
namespace mc {

template <class T>
class EventSetNew
{
public:
    EventSetNew() = default;
    ~EventSetNew() = default;
    EventSetNew(const EventSetNew&) = default;
    EventSetNew& operator=(const EventSetNew&) = default;
    EventSetNew(EventSetNew&&) = default;
    EventSetNew& operator=(EventSetNew&&) = default;

    std::set<std::unique_ptr<T>> get_events() const;
    void set_events(std::set<std::unique_ptr<T>> events);
    size_t size() const;
    bool empty() const;
    T* begin();
    T* end();
    void insert(T* event);
    void erase(T*);
    EventSetNew<T> minus(T* event);
    EventSetNew<T> plus(T* event);
    void subtract(EventSetNew<T> event_set);

    bool operator==(const EventSetNew<T>& other) const;

private:
    std::set<std::unique_ptr<T>> events_;

};

} // namespace mc
} // namespace tiny_simgrid

#endif // EVENTSET_H
