#include "DistrhoUI.hpp"
#include "ResizeHandle.hpp"

#include "PluginDSP.hpp"

#include "imgui-knobs.h"
#include <imgui_internal.h>
#include "imgui-knobs-svg.h"
#include "implot.h"

START_NAMESPACE_DISTRHO

// --------------------------------------------------------------------------------------------------------------------

class PluginUI : public UI
{

    ResizeHandle fResizeHandle;

    bool showDemo = false;

    std::string resources_path;

    ImFont* font1;

    std::unique_ptr<ImGuiKnobsSVG::Knob> cutoff_knob;
    std::unique_ptr<ImGuiKnobsSVG::Knob> resonance_knob;
    std::unique_ptr<ImGuiKnobsSVG::Knob> envmod_knob;
    std::unique_ptr<ImGuiKnobsSVG::Knob> decay_knob;
    std::unique_ptr<ImGuiKnobsSVG::Knob> accent_knob;
    std::unique_ptr<ImGuiKnobsSVG::Knob> tuning_knob;
    std::unique_ptr<ImGuiKnobsSVG::Knob> vcadecay_knob;
    std::unique_ptr<ImGuiKnobsSVG::Knob> volume_knob;

    GLuint logo_tex;
    float logo_width = 0.47;
    float base_dimension;

    char vcfDecayDisplayString[16];
    char vcaDecayDisplayString[16];

    MiniSilverParameters params;

    int buffer_size;
    char buffer_size_str[20];
    bool showTweaks{false};
    float local_plot[192000];

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

    char* setTimeDisplayValueString(char* str, float v)
    {
        auto time = pow(2.0, v);
        if (time < 1)
            std::sprintf(str, "%6.1fms", time * 1000);
        else
            std::sprintf(str, "%6.3fs", time);
        return str;
    }

    void pushCustomKnobsColors() {
        auto *colors = ImGui::GetStyle().Colors;
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colors[ImGuiCol_ScrollbarGrabActive]);
    }
    
    void popCustomKnobsColors() {
        ImGui::PopStyleColor();
    }

    // ----------------------------------------------------------------------------------------------------------------
    // Widget Callbacks

    void generateLogo();
    void showMenuBar();
    void showTweaksTab(float size_x, float size_y);

    /**
      ImGui specific onDisplay function.
    */
    void onImGuiDisplay() override;


    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginUI)
};

END_NAMESPACE_DISTRHO
