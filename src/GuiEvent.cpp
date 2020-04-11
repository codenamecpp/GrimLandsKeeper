#include "pch.h"
#include "GuiEvent.h"
#include "GuiWidget.h"
#include "GuiManager.h"

GuiEventsHandler::~GuiEventsHandler()
{
    UnsubscribeAll();
}

void GuiEventsHandler::Subscribe(GuiWidget* eventSource, eGuiEvent eventId)
{
    if (eventSource == nullptr)
    {
        debug_assert(false);
        return;
    }

    bool subsFound = cxx::contains_if(mSubscriptions,
        [eventSource, eventId](const Subscription& curr)
        {
            return curr.mEventsSource == eventSource && curr.mEventsId == eventId;
        });

    if (subsFound)
        return;

    Subscription subs;
        subs.mEventsSource = eventSource;
        subs.mEventsId = eventId;
    mSubscriptions.push_back(subs);

    gGuiManager.RegisterEventsHandler(this);
}

void GuiEventsHandler::Unsubscribe(GuiWidget* eventSource, eGuiEvent eventId)
{
    if (eventSource == nullptr)
    {
        debug_assert(false);
        return;
    }

    cxx::erase_elements_if(mSubscriptions, [eventSource, eventId](const Subscription& curr)
        {
            return curr.mEventsSource == eventSource && curr.mEventsId == eventId;
        });

    if (mSubscriptions.empty())
    {
        gGuiManager.UnregisterEventsHandler(this);
    }
}

void GuiEventsHandler::Unsubscribe(GuiWidget* eventSource)
{
    if (eventSource == nullptr)
    {
        debug_assert(false);
        return;
    }

    cxx::erase_elements_if(mSubscriptions, [eventSource](const Subscription& curr)
        {
            return curr.mEventsSource == eventSource;
        });

    if (mSubscriptions.empty())
    {
        gGuiManager.UnregisterEventsHandler(this);
    }
}

void GuiEventsHandler::UnsubscribeAll()
{
    mSubscriptions.clear();
    gGuiManager.UnregisterEventsHandler(this);
}

bool GuiEventsHandler::ProcessEvent(GuiEvent* eventData)
{
    debug_assert(eventData);

    if (eventData->mEventSender == nullptr)
        return false;

    for (const Subscription& curr: mSubscriptions)
    {
        if (curr.mEventsSource == eventData->mEventSender && curr.mEventsId == eventData->mEventId)
        {
            switch (curr.mEventsId)
            {
                case eGuiEvent_Click: 
                    HandleClickEvent(eventData->mEventSender, eventData); 
                break;

                case eGuiEvent_MouseEnter:
                    HandleMouseEnter(eventData->mEventSender, eventData);
                break;

                case eGuiEvent_MouseLeave:
                    HandleMouseLeave(eventData->mEventSender, eventData);
                break;
            }
            return true;
        }
    }
    return false;
}