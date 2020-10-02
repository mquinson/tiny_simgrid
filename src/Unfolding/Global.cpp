#include "Global.hpp"

namespace uc
{
    std::shared_ptr<AppSide> App::app_side_ = std::make_shared<AppSide>();
    int Util::INT_DEF = -1;

    void App::set_app_side(std::shared_ptr<AppSide> app_side)
    {
        app_side_ = app_side;
    }

    void Util::get_transition_detail(std::string trans_tag, std::string &type, int &actor_id, int &mb_id, int &trans_id)
    {
        // (type, (actor_id, mb_id, trans_id))
        auto trans_attrs = App::app_side_->get_transition_attrs(trans_tag);
        type = trans_attrs.first;
        actor_id = std::get<0>(trans_attrs.second);
        mb_id = std::get<1>(trans_attrs.second);
        trans_id = std::get<2>(trans_attrs.second);
    }

    UnfoldingEvent::UnfoldingEvent(unsigned int nb_events, std::string const &trans_tag, EventSet const &causes, int sid) : 
                                                id(nb_events), transition_tag(trans_tag), causes(causes), state_id(sid) {}

    void UnfoldingEvent::print() const
    {
        auto trans_tag = this->get_transition_tag();
        std::string trans_type;
        int trans_actor_id;
        int trans_mb_id;
        int trans_id;
        Util::get_transition_detail(trans_tag, trans_type, trans_actor_id, trans_mb_id, trans_id);

        std::cout << "e" << this->id << " =  < t" << trans_id << "-p" << trans_actor_id << "(";
        if (trans_type.length() > 1)
            std::cout << trans_type << ")"
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
        bool result = false;

        auto testedEvt_trans_tag = testedEvt->get_transition_tag();
        auto mbId = App::app_side_->get_transition_mb_id(testedEvt_trans_tag);
        auto testedEvt_trans_type = App::app_side_->get_transition_type(testedEvt_trans_tag);
        auto SdRcEvtH = SdRcEvt->getHistory();
        if (testedEvt_trans_type == "Ireceive")
        {
            EventSet testedEvtH = testedEvt->getHistory();
            int nbSend = 0;
            int nbReceive = 0;

            // count the number of Receive event before testedEvt
            for (auto it : testedEvtH)
            {
                auto it_trans_tag = it->get_transition_tag();
                auto it_trans_mb_id = App::app_side_->get_transition_mb_id(it_trans_tag);
                auto it_trans_type = App::app_side_->get_transition_type(it_trans_tag);

                if ((it_trans_mb_id == mbId) && (it_trans_type == "Ireceive"))
                    nbReceive++;
            }
            // count the number of Isend event before SdRcEvt
            for (auto it : SdRcEvtH)
            {
                auto it_trans_tag = it->get_transition_tag();
                auto it_trans_mb_id = App::app_side_->get_transition_mb_id(it_trans_tag);
                auto it_trans_type = App::app_side_->get_transition_type(it_trans_tag);

                if ((it_trans_mb_id == mbId) && (it_trans_type == "Isend"))
                    nbSend++;
            }
            if (nbSend == nbReceive)
                result = true;
        }
        return result;
    }

    bool UnfoldingEvent::transition_is_ISend(const UnfoldingEvent *testedEvt, const UnfoldingEvent *SdRcEvt) const
    {
        bool return_val = false;
        auto testedEvt_trans_tag = testedEvt->get_transition_tag();
        auto mbId = App::app_side_->get_transition_mb_id(testedEvt_trans_tag);
        auto testedEvt_trans_type = App::app_side_->get_transition_type(testedEvt_trans_tag);
        auto SdRcEvtH = SdRcEvt->getHistory();
        if (testedEvt_trans_type == "Isend")
        {
            EventSet testedEvtH = testedEvt->getHistory();
            int nbSend = 0;
            int nbReceive = 0;

            // count the number of Isend event before testedEvt
            for (auto it : testedEvtH)
            {
                auto it_trans_tag = it->get_transition_tag();
                auto it_trans_mb_id = App::app_side_->get_transition_mb_id(it_trans_tag);
                auto it_trans_type = App::app_side_->get_transition_type(it_trans_tag);

                if ((it_trans_mb_id == mbId) && (it_trans_type == "Isend"))
                    nbSend++;
            }
            // count the number of Ireceive event before SdRcEvt
            for (auto it : SdRcEvtH)
            {
                auto it_trans_tag = it->get_transition_tag();
                auto it_trans_mb_id = App::app_side_->get_transition_mb_id(it_trans_tag);
                auto it_trans_type = App::app_side_->get_transition_type(it_trans_tag);

                if ((it_trans_mb_id == mbId) && (it_trans_type == "Ireceive"))
                    nbReceive++;
            }
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

        auto event_trans_tag = event->get_transition_tag();
        auto event_trans_mb_id = App::app_side_->get_transition_mb_id(event_trans_tag);
        auto event_trans_type = App::app_side_->get_transition_type(event_trans_tag);
        auto otherEvent_trans_mb_id = App::app_side_->get_transition_mb_id(otherEvent->get_transition_tag());

        if (event_trans_mb_id != otherEvent_trans_mb_id)
            return false;

        if (event_trans_type == "Test")
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
        auto testEvt_trans_tag = testEvt->get_transition_tag();
        int comId = App::app_side_->get_transition_comm_id(testEvt_trans_tag);
        int testEvt_trans_actor_id = App::app_side_->get_transition_actor_id(testEvt_trans_tag);

        EventSet testEvtH = testEvt->getHistory();
        EventSet SdRcEvtH = SdRcEvt->getHistory();

        for (auto it : testEvtH)
        {
            auto it_trans_tag = it->get_transition_tag();
            auto it_trans_actor_id = App::app_side_->get_transition_actor_id(it_trans_tag);
            auto it_trans_commId = App::app_side_->get_transition_comm_id(it_trans_tag);
            if ((it_trans_actor_id == testEvt_trans_actor_id) && (it_trans_commId == comId))
                testedEvt = it;
        }

        auto testedEvt_trans_tag = testedEvt->get_transition_tag();
        auto testedEvt_trans_type = App::app_side_->get_transition_type(testedEvt_trans_tag);
        auto SdRcEvt_trans_tag = SdRcEvt->get_transition_tag();
        auto SdRcEvt_trans_type = App::app_side_->get_transition_type(SdRcEvt_trans_tag);
        if (testedEvt_trans_type == SdRcEvt_trans_type)
            return false;

        if (testedEvt_trans_type == "Isend")
        {
            auto isISend = transition_is_ISend(testedEvt, SdRcEvt);
            return isISend;
        }

        if (testedEvt_trans_type == "Ireceive")
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
        auto event_trans_tag = event->get_transition_tag();
        auto otherEvent_trans_tag = otherEvent->get_transition_tag();
        bool is_dependent = App::app_side_->check_transition_dependency(event_trans_tag, otherEvent_trans_tag);

        if (is_dependent)
            return true;

        //  if 2 event they have the same causes, just check their last transition
        if (event == otherEvent)
            return is_dependent;
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
        auto evt1_trans_tag = evt1->get_transition_tag();
        auto evt2_trans_tag = evt2->get_transition_tag();
        auto is_dependent = App::app_side_->check_transition_dependency(evt1_trans_tag, evt2_trans_tag);

        auto evt1_trans_type = App::app_side_->get_transition_type(evt1_trans_tag);
        auto evt2_trans_type = App::app_side_->get_transition_type(evt2_trans_tag);

        if (!is_dependent)
        {
            chk1 = true;
            chk2 = true;
            if (evt1_trans_type == "Test" && (evt2_trans_type == "Isend" || evt2_trans_type == "Ireceive"))
            {
                if (!evt1->concernSameComm(evt1, evt2))
                    return_val = false;
                else
                {
                    chk2 = false;
                }
            }

            if (evt2_trans_type == "Test" && (evt1_trans_type == "Isend" || evt1_trans_type == "Ireceive"))
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
        if (!ret)
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
    bool UnfoldingEvent::conflictWithConfig(UnfoldingEvent *event, Configuration const &config) const
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
        auto trans0_tag = this->get_transition_tag();
        auto trans1_tag = other.get_transition_tag();

        auto partial_check = App::app_side_->partial_check_transition_equality(trans0_tag, trans1_tag);
        if (!partial_check)
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
        auto e_trans_actor_id = App::app_side_->get_transition_actor_id(e->get_transition_tag());

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
        {
            auto evt_trans_actor_id = App::app_side_->get_transition_actor_id(evt->get_transition_tag());
            if (evt_trans_actor_id == e_trans_actor_id)
                to_remove.push_back(evt);
        }
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

    UnfoldingEvent *Configuration::findTestedComm(const UnfoldingEvent *testEvt)
    {
        auto testEvt_trans_tag = testEvt->get_transition_tag();
        for (auto it : this->events_)
        {
            auto it_trans_tag = it->get_transition_tag();

            auto it_trans_comm_id = App::app_side_->get_transition_comm_id(it_trans_tag);
            auto it_trans_type = App::app_side_->get_transition_type(it_trans_tag);
            auto it_trans_actor_id = App::app_side_->get_transition_actor_id(it_trans_tag);
            auto testEvt_trans_comm_id = App::app_side_->get_transition_comm_id(testEvt_trans_tag);
            auto testEvt_trans_type = App::app_side_->get_transition_type(testEvt_trans_tag);
            auto testEvt_trans_actor_id = App::app_side_->get_transition_actor_id(testEvt_trans_tag);
            auto check = (it_trans_comm_id == testEvt_trans_comm_id) &&
                         (it_trans_type != "Test") && (it_trans_actor_id == testEvt_trans_actor_id);
            if (check)
                return it;
        }
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

    void EvtSetTools::subtract(EventSet &events, EventSet const &otherSet)
    {
        for (auto evt : otherSet)
            EvtSetTools::remove(events, evt);
    }

    bool check_events(const UnfoldingEvent *e1, const UnfoldingEvent *e2)
    {
        auto e1_trans_tag = e1->get_transition_tag();    
        auto e2_trans_tag = e2->get_transition_tag();    

        auto e1_trans_type = App::app_side_->get_transition_type(e1_trans_tag);
        auto e2_trans_type = App::app_side_->get_transition_type(e2_trans_tag);
        auto is_dependent = App::app_side_->check_transition_dependency(e1_trans_tag, e2_trans_tag);

        if (is_dependent)
            return true;
        auto c0 = (e1_trans_type == "Test") && ((e2_trans_type == "Isend") || (e2_trans_type == "Ireceive"));
        auto c1 = (e2_trans_type == "Test") && ((e1_trans_type == "Isend") || (e1_trans_type == "Ireceive"));
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
    bool EvtSetTools::depends(EventSet const &events, EventSet const &otherSet)
    {
        if (events.empty() || otherSet.empty())
            return false;

        for (auto e1 : events)
        {
            for (auto e2 : otherSet)
            {
                if (check_events(e1, e2))
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
                events.erase(events.begin() + index);
            else
                index++;
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
