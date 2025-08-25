#include "UIManager.h"
#include "Common.h"

// Globale Variablen Definition
PRISMA_UI_API::IVPrismaUI1* PrismaUI = nullptr;
PrismaView view;

void hide() {
    if (PrismaUI && view) PrismaUI->Invoke(view, "hide(true)");
}

void show() {
    if (PrismaUI && view) PrismaUI->Invoke(view, "hide(false)");
}

void toggle_visibility(bool show) {
    if (PrismaUI && view) PrismaUI->Invoke(view, std::format("hide({})", show ? "true" : "false").c_str());
}
