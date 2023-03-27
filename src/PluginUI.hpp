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

    float v_cutoff = 0;
    float v_resonance = 0;
    float v_envmod = 0;
    float v_decay = 0;
    float v_accent = 0;
    float v_tuning = 0;
    float v_vcadecay = 0;

    int wfm = 0;

    std::unique_ptr<ImGuiKnobsSVG::Knob> cutoff_knob;
    std::unique_ptr<ImGuiKnobsSVG::Knob> resonance_knob;
    std::unique_ptr<ImGuiKnobsSVG::Knob> envmod_knob;
    std::unique_ptr<ImGuiKnobsSVG::Knob> decay_knob;
    std::unique_ptr<ImGuiKnobsSVG::Knob> accent_knob;
    std::unique_ptr<ImGuiKnobsSVG::Knob> tuning_knob;
    std::unique_ptr<ImGuiKnobsSVG::Knob> vcadecay_knob;

    GLuint logo_tex;
    float logo_width = 0.47;
    float base_dimension;

    char decayDisplayString[16];
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

    char* setTimeDisplayValueString(float v)
    {
        auto time = pow(2.0, v);
        if (time < 1)
            std::sprintf(decayDisplayString, "%6.1fms", time * 1000);
        else
            std::sprintf(decayDisplayString, "%6.3fs", time);
        return decayDisplayString;
    }

    inline float linear(float x, float lo_bp, float hi_bp, float lo_y, float hi_y) {
        float Xmapping = 1.0f/(hi_bp - lo_bp);
        float mappedX = Xmapping * (x - lo_bp);
        return (hi_y - lo_y) * mappedX + lo_y;
    }

    float paramLog(float x, float bpx, float bpy, float min, float max) {
        float bpy_mapped = (max - min) * bpy + min;
        if (x < bpx) return linear(x, 0.0f, bpx, min, bpy_mapped);
        else return linear(x, bpx, 1.0f, bpy_mapped, max);
    }

    // ----------------------------------------------------------------------------------------------------------------
    // Widget Callbacks

    void generateLogo();
    void showMenuBar();

    /**
      ImGui specific onDisplay function.
    */
    void onImGuiDisplay() override;


    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginUI)
};

END_NAMESPACE_DISTRHO
