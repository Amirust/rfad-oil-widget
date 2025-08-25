#pragma once

#include "Common.h"
#include "RfaD/GamePtr.h"

class OilSystem {
public:
    static RE::ExtraPoison* GetPlayerPoison(bool is_left_hand);
    static bool IsEquipped(RE::Actor* actor, RE::TESBoundObject* obj);
    static void UpdateOilWidget();
    static void Initialize();

private:
    static float upd_timer;
    static GamePtr<RE::BGSKeyword> oil_improvedKW;
    static GamePtr<RE::BGSKeyword> oil_pureKW;
    static GamePtr<RE::TESObjectARMO> chemistPotions;
    static GamePtr<RE::BGSPerk> firstAlchemyPerk;
};
