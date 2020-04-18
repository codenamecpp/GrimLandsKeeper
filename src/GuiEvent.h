#pragma once

#include "GuiDefs.h"
#include "GuiWidget.h"

// gui event type
enum eGuiEvent: unsigned int
{
    eGuiEvent_Click         = (1U << 0),
    eGuiEvent_MouseEnter    = (1U << 1),
    eGuiEvent_MouseLeave    = (1U << 2),
    eGuiEvent_MouseDown     = (1U << 3),
    eGuiEvent_MouseUp       = (1U << 4),
};

inline eGuiEvent operator | (eGuiEvent lhs, eGuiEvent rhs) { return (eGuiEvent)((unsigned int)(lhs) | (unsigned int)(rhs)); }
inline eGuiEvent operator & (eGuiEvent lhs, eGuiEvent rhs) { return (eGuiEvent)((unsigned int)(lhs) & (unsigned int)(rhs)); }
inline eGuiEvent operator ^ (eGuiEvent lhs, eGuiEvent rhs) { return (eGuiEvent)((unsigned int)(lhs) ^ (unsigned int)(rhs)); }
inline eGuiEvent operator ~ (eGuiEvent bits) { return (eGuiEvent)(~(unsigned int)(bits)); }

// all standard events mask except for action
const eGuiEvent GuiEvent_All = 
    (eGuiEvent_Click | eGuiEvent_MouseEnter | eGuiEvent_MouseLeave | eGuiEvent_MouseDown | eGuiEvent_MouseUp);

// base events struct of gui widget
struct GuiEvent
{
public:
    GuiEvent(GuiWidget* eventSender, eGuiEvent eventType)
        : mEventSender(eventSender)
        , mEventId(eventType)
        , mMouseButton()
    {
    }
    GuiEvent(GuiWidget* eventSender, eGuiEvent eventType, eMouseButton mouseButton)
        : mEventSender(eventSender)
        , mEventId(eventType)
        , mMouseButton()
    {
    }
public:
    GuiWidgetHandle mEventSender; // sender widget handle
    eGuiEvent mEventId;// event identifier
    // event specific args
    eMouseButton mMouseButton; // eGuiEvent_MouseButtonDown, eGuiEvent_MouseButtonUp
};

// widget events handler
class GuiEventsHandler
{
    friend class GuiManager;

public:
    GuiEventsHandler() = default;
    virtual ~GuiEventsHandler();

    // @param eventSource cannot be null
    void Subscribe(GuiWidget* eventSource, eGuiEvent eventId);
    void Unsubscribe(GuiWidget* eventSource, eGuiEvent eventId);
    void Unsubscribe(GuiWidget* eventSource);
    void UnsubscribeAll();

protected:
    // overridables
    virtual void HandleClickEvent(GuiWidget* sender) {}
    virtual void HandleMouseEnter(GuiWidget* sender) {}
    virtual void HandleMouseLeave(GuiWidget* sender) {}
    virtual void HandleMouseDown(GuiWidget* sender, eMouseButton mbutton) {}
    virtual void HandleMouseUp(GuiWidget* sender, eMouseButton mbutton) {}

private:
    void ProcessEvent(GuiEvent* eventData);

private:
    std::map<GuiWidget*, eGuiEvent> mSubscriptions;
};