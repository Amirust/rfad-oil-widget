#pragma once

#include "PrismaUI_API.h"
#include "pch.h"

// Globale Variablen
extern PRISMA_UI_API::IVPrismaUI1* PrismaUI;
extern PrismaView view;

// UI Utility-Funktionen
void hide();
void show();
void toggle_visibility(bool show);
