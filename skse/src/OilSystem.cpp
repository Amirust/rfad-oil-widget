#include "OilSystem.h"
#include "Common.h"

// Static member definitions
float OilSystem::upd_timer = 0.2f;
GamePtr<RE::BGSKeyword> OilSystem::oil_improvedKW(0x21912E, "RfaD SSE - Awaken.esp");
GamePtr<RE::BGSKeyword> OilSystem::oil_pureKW(0x21E298, "RfaD SSE - Awaken.esp");
GamePtr<RE::TESObjectARMO> OilSystem::chemistPotions(0xD8B314, "RfaD SSE - Awaken.esp");

RE::ExtraPoison* OilSystem::GetPlayerPoison(bool is_left_hand)
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

bool OilSystem::IsEquipped(RE::Actor* actor, RE::TESBoundObject* obj)
{
    for (const auto &[item, data] : actor->GetInventory()) {
        const auto &[count, entry] = data;
        if (obj->formID == item->formID && entry && entry->IsWorn()) {
            return true;
        }
    }
    return false;
}

void OilSystem::UpdateOilWidget()
{
    if (!view) return;

    RE::ExtraPoison* oil = GetPlayerPoison(false);
    if (!oil) {
        oil = GetPlayerPoison(true);
        if (!oil) {
            std::string jsObject = std::format(
                "{{name: '{}', currentCharge: {}, maxCharge: {}}}",
                "no_oil", -1, -1
            );
            PrismaUI->Invoke(view, std::format("OilUpdate({})", jsObject).c_str());
        }
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

        if (IsEquipped(RE::PlayerCharacter::GetSingleton(), chemistPotions.p)) {
            max_charge += 50.f;
        }

        float charges = static_cast<float>(oil->count);
        std::string jsObject = std::format(
            "{{name: '{}', currentCharge: {}, maxCharge: {}}}",
            oil_id, charges, max_charge
        );
        PrismaUI->Invoke(view, std::format("OilUpdate({})", jsObject).c_str());
    }
}

void OilSystem::Initialize()
{
}
