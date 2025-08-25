#include "MenuEventHandler.h"
#include "Common.h"

RE::BSEventNotifyControl MenuOpenCloseEventSink::ProcessEvent(const RE::MenuOpenCloseEvent* ev, RE::BSTEventSource<RE::MenuOpenCloseEvent>*)
{
    if (ev) {
        if (ev->menuName == RE::Console::MENU_NAME) {
            ev->opening ? hide() : show();
        }
        if (ev->menuName == RE::SleepWaitMenu::MENU_NAME)
        {
            ev->opening ? hide() : show();
        }
        else if (ev->menuName == RE::InventoryMenu::MENU_NAME)
        {
            show();
        }
        else if (ev->menuName == RE::HUDMenu::MENU_NAME) {
            ev->opening ? show() : hide();
        }
        else if (ev->menuName == RE::LoadingMenu::MENU_NAME) {
            ev->opening ? hide() : show();
        }
        else if (ev->menuName == RE::CraftingMenu::MENU_NAME) {
            ev->opening ? hide() : show();
        }
        else if (ev->menuName == RE::JournalMenu::MENU_NAME) {
            ev->opening ? hide() : show();
        }
        else if (ev->menuName == RE::MapMenu::MENU_NAME) {
            ev->opening ? hide() : show();
        }
        else if (ev->menuName == RE::TweenMenu::MENU_NAME) {
            ev->opening ? hide() : show();
        }
        else if (ev->menuName == RE::FavoritesMenu::MENU_NAME) {
            ev->opening ? hide() : show();
        }
        else if (ev->menuName == RE::MessageBoxMenu::MENU_NAME) {
            ev->opening ? hide() : show();
        }
        else if (ev->menuName == RE::MagicMenu::MENU_NAME) {
           ev->opening ? hide() : show();
        }
        else if (ev->menuName == RE::FaderMenu::MENU_NAME) {
           ev->opening ? hide() : show();
        }
        else if (ev->menuName == RE::TrainingMenu::MENU_NAME) {
           ev->opening ? hide() : show();
        }
        else if (ev->menuName == RE::StatsMenu::MENU_NAME) {
           ev->opening ? hide() : show();
        }
    }

    // Control map context handling (from TrueHUD)
    // using ContextID = RE::UserEvents::INPUT_CONTEXT_ID;
    // auto control_map = RE::ControlMap::GetSingleton();
    // if (control_map) {
    //     auto& priorityStack = control_map->GetRuntimeData().contextPriorityStack;
    //     if (priorityStack.empty())
    //     {
    //         toggle_visibility(true);
    //     }
    //     else if (priorityStack.back() == ContextID::kGameplay || priorityStack.back() == ContextID::kFavorites || priorityStack.back() == ContextID::kConsole)
    //     {
    //         toggle_visibility(false);
    //     }
    //     else if ((priorityStack.back() == ContextID::kCursor ||
    //                 priorityStack.back() == ContextID::kItemMenu ||
    //                 priorityStack.back() == ContextID::kMenuMode ||
    //                 priorityStack.back() == ContextID::kInventory) &&
    //                (RE::UI::GetSingleton()->IsMenuOpen(RE::DialogueMenu::MENU_NAME) ||
    //                 RE::UI::GetSingleton()->IsMenuOpen(RE::CraftingMenu::MENU_NAME) ||
    //                 (RE::UI::GetSingleton()->IsMenuOpen(RE::BarterMenu::MENU_NAME) ||
    //                  RE::UI::GetSingleton()->IsMenuOpen(RE::ContainerMenu::MENU_NAME) ||
    //                  RE::UI::GetSingleton()->IsMenuOpen(RE::GiftMenu::MENU_NAME) ||
    //                  RE::UI::GetSingleton()->IsMenuOpen(RE::InventoryMenu::MENU_NAME))))
    //     {
    //         toggle_visibility(true);
    //     }
    //     else
    //     {
    //         toggle_visibility(true);
    //     }
    // }

    return RE::BSEventNotifyControl::kContinue;
}
