#include "pch.h"
#include "GuiManager.h"
#include "GuiRenderer.h"
#include "Console.h"

GuiManager gGuiManager;

bool GuiManager::Initialize()
{
    RegisterWidgetsClasses();
    return true;
}

void GuiManager::Deinit()
{
    mWidgetsClasses.clear();
}

void GuiManager::RenderFrame(GuiRenderer& renderContext)
{

}

void GuiManager::UpdateFrame()
{
}

void GuiManager::HandleInputEvent(MouseButtonInputEvent& inputEvent)
{
}

void GuiManager::HandleInputEvent(MouseMovedInputEvent& inputEvent)
{
}

void GuiManager::HandleInputEvent(MouseScrollInputEvent& inputEvent)
{
}

void GuiManager::HandleInputEvent(KeyInputEvent& inputEvent)
{
}

void GuiManager::HandleInputEvent(KeyCharEvent& inputEvent)
{
}

bool GuiManager::RegisterWidgetClass(GuiWidgetClass* widgetsClass)
{
    debug_assert(widgetsClass);
    if (widgetsClass == nullptr || widgetsClass->mFactory == nullptr)
        return false;

    GuiWidgetClass*& classRegistered = mWidgetsClasses[widgetsClass->mClassName];
    if (classRegistered)
    {
        gConsole.LogMessage(eLogMessage_Warning, "Widget class '%s' already registered in gui manager", widgetsClass->mClassName.c_str());
        return false;
    }
    classRegistered = widgetsClass;
    return true;
}

void GuiManager::RegisterWidgetsClasses()
{
    RegisterWidgetClass(&gBaseWidgetClass);
}

GuiWidgetClass* GuiManager::GetWidgetClass(const std::string& className) const
{
    auto iterator_found = mWidgetsClasses.find(className);
    if (iterator_found == mWidgetsClasses.end())
        return nullptr;

    return iterator_found->second;
}

GuiWidget* GuiManager::ConstructWidget(const std::string& className) const
{
    if (GuiWidgetClass* widgetClass = GetWidgetClass(className))
    {
        debug_assert(widgetClass->mFactory);
        return widgetClass->mFactory->ConstructWidget();
    }

    debug_assert(false);
    return nullptr;
}