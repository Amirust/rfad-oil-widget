#pragma once

#include "Common.h"

// Player Update Hook - verantwortlich für periodische Updates
class PlayerUpdateHook {
public:
    static void Install();
    static void Update(RE::PlayerCharacter* player, float delta);
    static auto update_pc_hook(RE::PlayerCharacter* player, float delta) -> void;

private:
    static inline REL::Relocation<uintptr_t> update_pc_address_{REL::RelocationID(261916, 208040)};
    static inline auto update_pc_offset_{REL::Relocate(0xAD, 0xAD)};
};
