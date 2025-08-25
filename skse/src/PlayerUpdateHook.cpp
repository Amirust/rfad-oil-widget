#include "PlayerUpdateHook.h"
#include "OilSystem.h"

static float upd_timer = 0.2f;

void PlayerUpdateHook::Update(RE::PlayerCharacter* player, float delta)
{
    upd_timer -= delta;
    if (upd_timer <= 0.f) {
        upd_timer = 0.2f;
        OilSystem::UpdateOilWidget();
    }
}

static REL::Relocation<decltype(PlayerUpdateHook::update_pc_hook)> update_pc_;

auto PlayerUpdateHook::update_pc_hook(RE::PlayerCharacter* player, float delta) -> void
{
    Update(player, delta);
    return update_pc_(player, delta);
}

void PlayerUpdateHook::Install()
{
    logger::info("Installing Player Update Hook");
    update_pc_ = update_pc_address_.write_vfunc(update_pc_offset_, update_pc_hook);
    logger::info("Player Update Hook installed successfully");
}
