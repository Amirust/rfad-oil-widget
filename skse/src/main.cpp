#include "PrismaUI_API.h"
#include "pch.h"
#include <keyhandler/keyhandler.h>

PRISMA_UI_API::IVPrismaUI1* PrismaUI;

PrismaView view;

RE::ExtraPoison* u_get_pc_poison (bool is_left_hand)
{
    if (auto weapEntryData = RE::PlayerCharacter::GetSingleton()->GetEquippedEntryData(is_left_hand)) {
        if (weapEntryData->IsPoisoned() && weapEntryData->extraLists) {
            if (auto extraData = weapEntryData->extraLists->front()) {
                if (auto poisonData = extraData->GetByType<RE::ExtraPoison>()) {
                    return poisonData;
                }
            }
        }
    }
    return nullptr;
}

bool u_is_equipped (RE::Actor* actor, RE::TESBoundObject* obj)
{
    for (const auto &[item, data] : actor->GetInventory()) {
        const auto &[count, entry] = data;
        if (obj->formID == item->formID && entry && entry->IsWorn()) {
            return true;
        }
    }
    return false;
}

static float upd_timer = 0.2f;

static GamePtr<RE::BGSKeyword> oil_improvedKW (0x21912E, "RfaD SSE - Awaken.esp");
static GamePtr<RE::BGSKeyword> oil_pureKW (0x21E298, "RfaD SSE - Awaken.esp");
static GamePtr<RE::TESObjectARMO> chemistPotions (0xD8B314, "RfaD SSE - Awaken.esp");

class OnPlayerUpdate_Hook {
private:
    static inline REL::Relocation<uintptr_t> update_pc_address_{REL::RelocationID(261916, 208040)};
    static inline auto update_pc_offset_{REL::Relocate(0xAD, 0xAD)};

    static auto update_pc(RE::PlayerCharacter* player, float delta) -> void
    {
        upd_timer -= delta;
        if (upd_timer <= 0.f) {
            upd_timer = 0.2f;

            if (view) {
                RE::ExtraPoison* oil = u_get_pc_poison(false);
                if (!oil) {
                    oil = u_get_pc_poison(true);
                }
                if (oil) {
                    auto data = oil->poison;
                    if (!oil || data->effects.empty()) return;
                    auto oil_id = data->effects[0]->baseEffect->formID;

                    float max_charge = 140.f;

                    if (data->HasKeyword(oil_improvedKW.p)) {
                        max_charge += 40.f;
                    }
                    else if (data->HasKeyword(oil_pureKW.p)) {
                        max_charge += 80.f;
                    }
                    if (u_is_equipped(player, chemistPotions.p)) max_charge += 50.f;

                    float charges = static_cast<float>(oil->count);
                    std::string jsObject = std::format(
                        "{{name: '{}', currentCharge: {}, maxCharge: {}}}",
                        oil_id, charges, max_charge
                    );
                    PrismaUI->Invoke(view, std::format("OilUpdate({})", jsObject).c_str());
                }
            }
        }

        return update_pc_(player, delta);
    }
    static inline REL::Relocation<decltype(update_pc)> update_pc_;

public:
    static auto install_hook() -> void
    {
        logger::info("start hook update pc"sv);
        update_pc_ = update_pc_address_.write_vfunc(update_pc_offset_, update_pc);
        logger::info("finish hook update pc"sv);
    }
};


static void SKSEMessageHandler(SKSE::MessagingInterface::Message* message)
{
    switch (message->type) {
    case SKSE::MessagingInterface::kDataLoaded:
        OnPlayerUpdate_Hook::install_hook();

        for (const auto& ptr : PtrsVec::getVec()) {
            ptr->init_ptr();
        }

        if (PrismaUI && view) {
            PrismaUI->Destroy(view);
        }
        break;

    case SKSE::MessagingInterface::kPostLoadGame:
        PrismaUI = static_cast<PRISMA_UI_API::IVPrismaUI1*>(PRISMA_UI_API::RequestPluginAPI(PRISMA_UI_API::InterfaceVersion::V1));
        logger::info("PrismaUI API initialized");
        view = PrismaUI->CreateView("index.html", [](PrismaView view) -> void {
            logger::info("RFAD plugin created");

            RE::ExtraPoison* oil = u_get_pc_poison(false);
                if (!oil) {
                    oil = u_get_pc_poison(true);
                }
                if (oil) {
                    auto data = oil->poison;
                    if (!oil || data->effects.empty()) return;
                    auto oil_id = data->effects[0]->baseEffect->formID;

                    float max_charge = 140.f;

                    if (data->HasKeyword(oil_improvedKW.p)) {
                        max_charge += 40.f;
                    }
                    else if (data->HasKeyword(oil_pureKW.p)) {
                        max_charge += 80.f;
                    }
                    if (u_is_equipped(RE::PlayerCharacter::GetSingleton(), chemistPotions.p)) max_charge += 50.f;

                    float charges = static_cast<float>(oil->count);
                    std::string jsObject = std::format(
                        "{{name: '{}', currentCharge: {}, maxCharge: {}}}",
                        oil_id, charges, max_charge
                    );
                    PrismaUI->Invoke(view, std::format("OilUpdate({})", jsObject).c_str());
                }
        });
        break;

    // out from game
    case SKSE::MessagingInterface::kPreLoadGame:
        logger::info("SKSE Pre Load Game, destroying PrismaUI view...");
        if (PrismaUI && view) {
            PrismaUI->Destroy(view);
        }
        break;
    }

}

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
{
    REL::Module::reset();

    auto g_messaging = reinterpret_cast<SKSE::MessagingInterface*>(a_skse->QueryInterface(SKSE::LoadInterface::kMessaging));

    if (!g_messaging) {
        logger::critical("Failed to load messaging interface! This error is fatal, plugin will not load.");
        return false;
    }

    SKSE::Init(a_skse);
    SKSE::AllocTrampoline(1 << 10);

    g_messaging->RegisterListener("SKSE", SKSEMessageHandler);

    return true;
}
