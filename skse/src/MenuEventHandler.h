#pragma once

#include "Common.h"

class MenuOpenCloseEventSink : public RE::BSTEventSink<RE::MenuOpenCloseEvent>
{
public:
    virtual RE::BSEventNotifyControl ProcessEvent (const RE::MenuOpenCloseEvent* ev, RE::BSTEventSource<RE::MenuOpenCloseEvent>*) override;

    static MenuOpenCloseEventSink* GetSingleton()
    {
        static MenuOpenCloseEventSink singleton;
        return std::addressof(singleton);
    }

    void register_()
    {
        RE::UI::GetSingleton()->AddEventSink<RE::MenuOpenCloseEvent>(this);
    }
};
