#include "pch.h"
#include "Common.h"
#include "UIManager.h"
#include "MenuEventHandler.h"
#include "OilSystem.h"
#include "PlayerUpdateHook.h"
#include <keyhandler/keyhandler.h>

static void SKSEMessageHandler(SKSE::MessagingInterface::Message* message)
{
    switch (message->type) {
    case SKSE::MessagingInterface::kDataLoaded:
        MenuOpenCloseEventSink::GetSingleton()->register_();
        PlayerUpdateHook::Install();

        for (const auto& ptr : PtrsVec::getVec()) {
            ptr->init_ptr();
        }

        OilSystem::Initialize();

        if (PrismaUI && view) PrismaUI->Destroy(view);
        break;

    case SKSE::MessagingInterface::kPostLoadGame:
        PrismaUI = static_cast<PRISMA_UI_API::IVPrismaUI1*>(PRISMA_UI_API::RequestPluginAPI(PRISMA_UI_API::InterfaceVersion::V1));
        logger::info("PrismaUI API initialized");

        if (PrismaUI && view) PrismaUI->Destroy(view);

        view = PrismaUI->CreateView("index.html", [](PrismaView viewInstance) -> void {
            logger::info("RFAD plugin created");

            OilSystem::UpdateOilWidget();
        });
        break;
    }
}

SKSEPluginLoad(const SKSE::LoadInterface* skse) {
    SKSE::Init(skse);

    logger::info("loaded");

    SKSE::GetMessagingInterface()->RegisterListener(SKSEMessageHandler);

    return true;
}
