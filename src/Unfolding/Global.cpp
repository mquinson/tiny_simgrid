#include "Global.hpp"

namespace uc
{

    //UnfoldingEvent::UnfoldingEvent(unsigned int nb_events, const Transition &t, const EventSet &causes)
    UnfoldingEvent::UnfoldingEvent(unsigned int nb_events, app::Transition const &t, EventSet const &causes) : id(nb_events), transition(t), causes(causes)
    {
        set_transition_tag(t.get_tr_tag());
    }

    void UnfoldingEvent::print() const
    {

        std::cout << "e" << this->id << " =  < t" << this->transition.id << "-p" << this->transition.actor_id << "(";
        if (this->transition.type.length() > 1)
            std::cout << this->transition.type << ")"
                      << ","
                      << "(";
        if (this->causes.empty())
            std::cout << "-) >";
        else
        {

            for (auto evt : this->causes)
                std::cout << "e" << evt->id << ",";
            std::cout << " ) >";
        }
    }

    // Recursively compute the history of a given event by adding the causes of all ancestors
    EventSet UnfoldingEvent::getHistory() const
    {
        if (causes.empty()) // No direct ancestor => empty history
            return causes;
        else
        {
            EventSet res;
            for (auto ancestor : causes)
            {
                EventSet h1;

                // if event ancestor is already in history set -> we do not need to get it's history

                if (!EvtSetTools::contains(res, ancestor))
                    h1 = ancestor->getHistory();
                EvtSetTools::pushBack(h1, ancestor);
                res = EvtSetTools::makeUnion(res, h1);
            }
            return res;
        }
    }

    bool UnfoldingEvent::inHistory(UnfoldingEvent *otherEvent) const
    {
        auto history = getHistory();
        if (EvtSetTools::contains(history, otherEvent))
            return true;
        return false;
    }

    bool UnfoldingEvent::transition_is_IReceive(const UnfoldingEvent *testedEvt, const UnfoldingEvent *SdRcEvt) const
    {
        bool return_val = false;
        auto mbId = testedEvt->transition.mailbox_id;
        auto SdRcEvtH = SdRcEvt->getHistory();
        if (testedEvt->transition.type == "Ireceive")
        {
            EventSet testedEvtH = testedEvt->getHistory();
            int nbSend = 0;
            int nbReceive = 0;

            // count the number of Receive event before testedEvt
            for (auto it : testedEvtH)
                if (it->transition.mailbox_id == mbId && it->transition.type == "Ireceive")
                    nbReceive++;

            // count the number of Isend event before SdRcEvt
            for (auto it : SdRcEvtH)
                if (it->transition.mailbox_id == mbId && it->transition.type == "Isend")
                    nbSend++;

            if (nbSend == nbReceive)
                return_val = true;
        }
        return return_val;
    }

    bool UnfoldingEvent::transition_is_ISend(const UnfoldingEvent *testedEvt, const UnfoldingEvent *SdRcEvt) const
    {
        bool return_val = false;
        auto mbId = testedEvt->transition.mailbox_id;
        auto SdRcEvtH = SdRcEvt->getHistory();
        if (testedEvt->transition.type == "Isend")
        {
            EventSet testedEvtH = testedEvt->getHistory();
            int nbSend = 0;
            int nbReceive = 0;

            // count the number of Isend event before testedEvt
            for (auto it : testedEvtH)
                if (it->transition.mailbox_id == mbId && it->transition.type == "Isend")
                    nbSend++;

            // count the number of Ireceive event before SdRcEvt
            for (auto it : SdRcEvtH)
                if (it->transition.mailbox_id == mbId && it->transition.type == "Ireceive")
                    nbReceive++;

            if (nbSend == nbReceive)
                return_val = true;
        }
        return return_val;
    }

    /*Check whether 2 events a Test and a Send/Receive concern the same communication,
    * Here the events are supposed that they are not causality related
    * */
    bool UnfoldingEvent::concernSameComm(const UnfoldingEvent *event, const UnfoldingEvent *otherEvent) const
    {
        const UnfoldingEvent *testEvt = nullptr;
        const UnfoldingEvent *SdRcEvt = nullptr;
        const UnfoldingEvent *testedEvt = nullptr;

        if (event->transition.mailbox_id != otherEvent->transition.mailbox_id)
            return false;

        if (event->transition.type == "Test")
        {
            testEvt = event;
            SdRcEvt = otherEvent;
        }
        else
        {
            testEvt = otherEvent;
            SdRcEvt = event;
        }

        // 2 sends or 2 receives can not concern the same communication

        int comId = testEvt->transition.commId;

        EventSet testEvtH = testEvt->getHistory();
        EventSet SdRcEvtH = SdRcEvt->getHistory();

        for (auto it : testEvtH)
            if (it->transition.actor_id == testEvt->transition.actor_id && it->transition.commId == comId)
                testedEvt = it;

        if (testedEvt->transition.type == SdRcEvt->transition.type)
            return false;

        if (testedEvt->transition.type == "Isend")
        {
            auto isISend = transition_is_ISend(testedEvt, SdRcEvt);
            return isISend;
        }

        if (testedEvt->transition.type == "Ireceive")
        {
            auto isIReceive = transition_is_IReceive(testedEvt, SdRcEvt);
            return isIReceive;
        }

        return false;
    }

    /** @brief check for conflict in the history of provided events
 *
 * In the paper, this.isConflict(other) is written "this # other"
 */

    bool UnfoldingEvent::isConflict(UnfoldingEvent *event, UnfoldingEvent *otherEvent) const
    {
        if (*event == *otherEvent)
            return false;

        EventSet h1 = event->getHistory();
        EventSet h2 = otherEvent->getHistory();

        // checking causality relation, if they are in a causality relation return false
        if (EvtSetTools::contains(h1, otherEvent) || EvtSetTools::contains(h2, event))
            return false;

        // check direct conflict
        if (event->transition.isDependent(otherEvent->transition))
            return true;

        //  if 2 event they have the same causes, just check their last transition
        if (event == otherEvent)
            return event->transition.isDependent(otherEvent->transition);
        else
        {
            EvtSetTools::pushBack(h1, event);
            EvtSetTools::pushBack(h2, otherEvent);
            EventSet his = h1;
            // FIXME remove all common events
            for (auto evt : his)
                if (EvtSetTools::contains(h2, evt))
                {
                    EvtSetTools::remove(h1, evt);
                    EvtSetTools::remove(h2, evt);
                }

            return EvtSetTools::depends(h1, h2);
        }
    }

    bool UnfoldingEvent::check_tr_concern_same_comm(bool &chk1, bool &chk2, UnfoldingEvent *evt1, UnfoldingEvent *evt2) const
    {
        auto return_val = true;
        if (!evt1->transition.isDependent(evt2->transition))
        {
            chk1 = true;
            chk2 = true;
            if (evt1->transition.type == "Test" && (evt2->transition.type == "Isend" || evt2->transition.type == "Ireceive"))
            {
                if (!evt1->concernSameComm(evt1, evt2))
                    return_val = false;
                else
                {
                    chk2 = false;
                }
            }

            if (evt2->transition.type == "Test" && (evt1->transition.type == "Isend" || evt1->transition.type == "Ireceive"))
            {
                if (!evt1->concernSameComm(evt1, evt2))
                    return_val = false;
                else
                {
                    chk2 = false;
                }
            }
        }
        return return_val;
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
    bool UnfoldingEvent::isImmediateConflict1(UnfoldingEvent *evt1, UnfoldingEvent *evt2) const
    {

        // event e should not conflict with itself
        if (*evt1 == *evt2)
            return false;

        auto chk1 = false;
        auto chk2 = false;
        auto ret = check_tr_concern_same_comm(chk1, chk2, evt1, evt2);
        if(!ret)
            return false;

        // 2 transitions are not depend and they are one is test other one is send/receive  -> return false
        if (chk1 && chk2)
            return false;

        // Now, check the second condition
        EventSet hist1 = evt1->getHistory();
        EventSet hist2 = evt2->getHistory();
        EventSet hist11 = hist1; 
        EventSet hist21 = hist2;

        // if causality ralated - > no immidiate conflict
        if (EvtSetTools::contains(hist1, evt2) || EvtSetTools::contains(hist2, evt1))
            return false;

        for (auto e1 : hist1)
            if (EvtSetTools::contains(hist2, e1))
            {
                EvtSetTools::remove(hist11, e1);
                EvtSetTools::remove(hist21, e1);
            }

        EventSet evtS1; 
        EventSet evtS2;

        EvtSetTools::pushBack(evtS1, evt1);
        EvtSetTools::pushBack(evtS2, evt2);

        if (EvtSetTools::depends(hist11, hist21) || EvtSetTools::depends(evtS1, hist21) || EvtSetTools::depends(evtS2, hist11))
        {
            return false;
        }

        return true;
    }

    // checking conflict relation between one event and one configuration or one history, it used when computing enC
    // there is a better way by checking the event with maximal events in the configuration, (change type of enC )
    bool UnfoldingEvent::conflictWithConfig(UnfoldingEvent *event, Configuration const& config) const 
    {
        if (config.events_.size() == 0)
            return false;
        // we don't really need to check the whole config. The maximal event should be enough.
        for (auto evt : config.maxEvent)
            if (event->isConflict(event, evt))
                return true;
        return false;
    }

    /** @brief check semantic equality (same transition, same causes) */
    bool UnfoldingEvent::operator==(const UnfoldingEvent &other) const
    {

        if ((this->transition.id != other.transition.id) || (this->transition.actor_id != other.transition.actor_id))
            return false;
        if (this->causes.size() != other.causes.size())
            return false;

        for (auto it : this->causes)
        {
            bool chk1 = false;
            for (auto it1 : other.causes)
                if (*it == *it1)
                {
                    chk1 = true;
                    break;
                }
            if (!chk1)
                return false;
        }

        return true;
    }

    void Configuration::updateMaxEvent(UnfoldingEvent *e)
    {
        this->lastEvent = e;
        // update the maximal events for current Conf removing causes from maxEvent and adding e to the maxEvent
        for (auto evt : e->causes)
        {
            EvtSetTools::remove(maxEvent, evt);
        }
        EvtSetTools::pushBack(maxEvent, e);
        /* update the maximal events for the actor=>
   removing the evt shares the same actor with e, then adding e to the actorMaxEvent */

        EventSet to_remove;

        for (auto evt : actorMaxEvent)
            if (evt->transition.actor_id == e->transition.actor_id)
                to_remove.push_back(evt);
        for (auto evt : to_remove)
            EvtSetTools::remove(actorMaxEvent, evt);
        EvtSetTools::pushBack(actorMaxEvent, e);
    }

    Configuration Configuration::plus_config(UnfoldingEvent *evt) const
    {
        Configuration res;
        res.events_ = this->events_;
        res.maxEvent = this->maxEvent;
        res.actorMaxEvent = this->actorMaxEvent;
        EvtSetTools::pushBack(res.events_, evt);
        return res;
    }

    UnfoldingEvent *Configuration ::findTestedComm(const UnfoldingEvent *testEvt)
    {
        for (auto it : this->events_)
            if (it->transition.commId == testEvt->transition.commId && it->transition.type != "Test" &&
                it->transition.actor_id == testEvt->transition.actor_id)
                return it;
        return nullptr;
    }

    bool EvtSetTools::contains(const EventSet events, const UnfoldingEvent *e)
    {
        for (auto evt : events)
            if (*evt == *e)
                return true;
        return false;
    }

    UnfoldingEvent *EvtSetTools::find(const EventSet events, const UnfoldingEvent *e)
    {
        for (auto evt : events)
            if (*evt == *e)
            {
                return evt;
            }
        return nullptr;
    }

    void EvtSetTools::subtract(EventSet &events, EventSet const& otherSet)
    {
        for (auto evt : otherSet)
            EvtSetTools::remove(events, evt);
    }

    bool check_events(const UnfoldingEvent *e1, const UnfoldingEvent *e2)
    {
        if (e1->transition.isDependent(e2->transition))
            return true;        
        auto c0 = (e1->transition.type == "Test") && (e2->transition.type == "Isend" || e2->transition.type == "Ireceive");
        auto c1 = (e2->transition.type == "Test") && (e1->transition.type == "Isend" || e1->transition.type == "Ireceive");
        if (c0 || c1)
        {
            auto c2 = e1->concernSameComm(e1, e2);
            if (c2)
                return true;
        }
        return false;
    }

    /** @brief Check if I'm dependent with another EventSet
    * Here we suppose that 2 given event sets do not have common events
    */
    bool EvtSetTools::depends(EventSet const& events, EventSet const& otherSet)
    {
        if (events.empty() || otherSet.empty())
            return false;

        for (auto e1 : events)
        {
            for (auto e2 : otherSet)
            {
                if(check_events(e1, e2))
                    return true;
            }
        }

        return false;
    }

    bool EvtSetTools::isEmptyIntersection(EventSet evtS1, EventSet evtS2)
    {
        if (evtS1.size() == 0 || evtS2.size() == 0)
            return false;
        for (auto evt : evtS2)
            if (EvtSetTools::contains(evtS1, evt))
                return false;
        return true;
    }

    EventSet EvtSetTools::makeUnion(EventSet s1, EventSet s2)
    {
        EventSet res = s1;
        for (auto evt : s2)
            EvtSetTools::pushBack(res, evt);
        return res;
    }

    void EvtSetTools::pushBack(EventSet &events, UnfoldingEvent *e)
    {
        if (!EvtSetTools::contains(events, e))
            events.push_back(e);
    }

    void EvtSetTools::remove(EventSet &events, UnfoldingEvent *e)
    {
        int index{0};
        EventSet evtS = events;
        for (auto it : evtS)
        {
            if (*it == *e)
            {
                events.erase(events.begin() + index);
            }
            else
            {
                index++;
            }
        }
    }

    EventSet EvtSetTools::minus(EventSet events, UnfoldingEvent *e)
    {
        int index{0};
        EventSet res = events;
        for (auto evt : events)
        {
            if (*evt == *e)
            {
                res.erase(res.begin() + index);
            }
            else
            {
                index++;
            }
        }
        return res;
    }

    EventSet EvtSetTools::plus(EventSet events, UnfoldingEvent *e)
    {
        EventSet res = events;
        if (!EvtSetTools::contains(res, e))
            res.push_back(e);
        return res;
    }

} // namespace uc
