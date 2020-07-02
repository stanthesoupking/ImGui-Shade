#pragma once

/**
 * Bindings for using Dear ImGui with Shade
 */

#include "imgui.h"      // IMGUI_IMPL_API

#include "shade/Shade.hpp"

IMGUI_IMPL_API bool     ImGui_ImplShade_Init(Shade::ShadeApplication* _app);
IMGUI_IMPL_API void     ImGui_ImplShade_Shutdown();
IMGUI_IMPL_API void     ImGui_ImplShade_NewFrame();
IMGUI_IMPL_API void     ImGui_ImplShade_RenderDrawData(ImDrawData* drawData);