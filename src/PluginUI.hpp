/*
 * ImGui plugin example
 * Copyright (C) 2021 Jean Pierre Cimalando <jp-dev@inbox.ru>
 * Copyright (C) 2021-2022 Filipe Coelho <falktx@falktx.com>
 * SPDX-License-Identifier: ISC
 */

#include "DistrhoUI.hpp"
#include "ResizeHandle.hpp"

#include "PluginDSP.hpp"

#include "imgui-knobs.h"
#include <imgui_internal.h>
#include "imgui-knobs-svg.h"

START_NAMESPACE_DISTRHO

// --------------------------------------------------------------------------------------------------------------------

class PluginUI : public UI
{
    enum Parameters {
        kParamGain = 0,
        kParamA,
        kParamB,
        kParamC,
        kParamD,
        kParamCount
    };

    float fGain = 0.0f;
    float fOutputParam = 0.0f;
    ResizeHandle fResizeHandle;

    bool showDemo = false;

    ImFont* font1;

    float v1 = 0;
    float v2 = 0;
    float v3 = 0;
    float v4 = 0;

    std::unique_ptr<ImGuiKnobsSVG::Knob> k1;
    std::unique_ptr<ImGuiKnobsSVG::Knob> k2;
    std::unique_ptr<ImGuiKnobsSVG::Knob> k3;
    std::unique_ptr<ImGuiKnobsSVG::Knob> k4;

    GLuint logo_tex;
    float logo_width = 0.47;
    float base_dimension;
    // ----------------------------------------------------------------------------------------------------------------

    public:
    /**
      UI class constructor.
      The UI should be initialized to a default state that matches the plugin side.
    */
    PluginUI();
    ~PluginUI();

    protected:
    // ----------------------------------------------------------------------------------------------------------------
    // DSP/Plugin Callbacks

    /**
      A parameter has changed on the plugin side.@n
      This is called by the host to inform the UI about parameter changes.
    */
    void parameterChanged(uint32_t index, float value) override;

    // Helpers

    // ----------------------------------------------------------------------------------------------------------------
    // Widget Callbacks

    void showLogo();

    /**
      ImGui specific onDisplay function.
    */
    void onImGuiDisplay() override;


    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginUI)
};

END_NAMESPACE_DISTRHO
