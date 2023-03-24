#include "PluginUI.hpp"

#include "PluginUI_style.hpp"
#include "PluginUI_colors.hpp"


START_NAMESPACE_DISTRHO

PluginUI::PluginUI()
    : UI(DISTRHO_UI_DEFAULT_WIDTH, DISTRHO_UI_DEFAULT_HEIGHT),
      fResizeHandle(this)
{
    setGeometryConstraints(DISTRHO_UI_DEFAULT_WIDTH, DISTRHO_UI_DEFAULT_HEIGHT, true);

    // hide handle if UI is resizable
    if (isResizable())
        fResizeHandle.hide();
    

    SetupImGuiStyle();
    setupSilverboxColors();
    // applySilverboxTheme();

    ImGuiIO& io = ImGui::GetIO();
    font1 = io.Fonts->AddFontFromFileTTF("Commissioner-Regular.ttf", 16);
    d_stdout("FontSize: %f", font1->FontSize);

}

PluginUI::~PluginUI() {

}

void PluginUI::parameterChanged(uint32_t index, float value)
{
    switch (index) {
    case kParamGain:
        fGain = value;
        repaint();
        return;
    case kParamD:
        fOutputParam = value;
        return;
    }
}

void PluginUI::onImGuiDisplay()
{   

    const float width = getWidth();
    const float height = getHeight();
    const float margin = 2.0f * getScaleFactor();

    ImGui::SetNextWindowPos(ImVec2(margin, margin));
    ImGui::SetNextWindowSize(ImVec2(width - 2 * margin, height - 2 * margin));

    ImGui::PushFont(font1);
    if (k1 == nullptr) {
        k1 = std::make_unique<ImGuiKnobsSVG::Knob>("res/BefacoBigKnob.svg", ImGuiKnobVariant_Stepped, &v1, -6.0f, 6.0f, 100);
        k1->setBg("res/BefacoBigKnob_bg.svg");
        k2 = std::make_unique<ImGuiKnobsSVG::Knob>("res/WDR-8_SmallKnob.svg", ImGuiKnobVariant_WiperOnly, &v2, 0.0f, 10.0f);
        k2->setBg("res/WDR-8_SmallKnob_Orange_bg.svg");
        k3 = std::make_unique<ImGuiKnobsSVG::Knob>("res/Rogan1PSRed.svg", ImGuiKnobVariant_WiperOnly, &v3, 0.0f, 10.0f);
        k3->setFg("res/Rogan1PSRed_fg.svg"); 
        k3->setBg("res/Rogan1PS_bg.svg"); 
        k4 = std::make_unique<ImGuiKnobsSVG::Knob>("res/303Knob_0_8.svg", ImGuiKnobVariant_WiperDot, &v4, -12.0f, 12.0f, 100);
        k4->setBg("res/303Knob_0_8_bg.svg"); 
    }

    if (ImGui::Begin("Mini Silver", nullptr, ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoCollapse))
    {   

        if (ImGuiKnobs::Knob("Befaco Big Knob", &v1, -6.0f, 6.0f, 0.1f, "%.1fdB", ImGuiKnobVariant_Stepped, 100)) {
            // v1 was changed
        }
        k1->paint();
        ImGui::SameLine();

        if (ImGuiKnobs::Knob("WDR-8", &v2, 0.0f, 10.0f, 0.02f, "%.1f", ImGuiKnobVariant_WiperOnly, 0, ImGuiKnobFlags_ValueTooltip|ImGuiKnobFlags_NoInput)) {
            // v2 was changed
        }
        k2->paint();

        auto acidKnob = ImGui::GetItemRectMin();
        acidKnob.x += ImGui::GetItemRectSize().x + ImGui::GetStyle().ItemSpacing.x;

        auto trim2 = ImGui::GetItemRectMax();
        trim2.x -= ImGui::GetItemRectSize().x;
        trim2.y += ImGui::GetStyle().ItemSpacing.y;
        ImGui::SetCursorPos(trim2);
        if (ImGuiKnobs::Knob("Rogan 3P", &v3, 0.0f, 10.0f, 0.1f, "%.1f", ImGuiKnobVariant_WiperOnly, 0, ImGuiKnobFlags_ValueTooltip|ImGuiKnobFlags_NoInput)) {
            // v3 was changed
        }
        k3->paint();

        ImGui::SetCursorPos(acidKnob);
        if (ImGuiKnobs::Knob("Acid Knob", &v4, -12.0f, 12.0f, 0.05f, "%.1f", ImGuiKnobVariant_WiperDot, 100)) {
            // v4 was changed
        }
        k4->paint();

        // ImGui::Checkbox("Show demo window", &showDemo);
        // if (showDemo) ImGui::ShowDemoWindow(&showDemo);
        // ImGui::GetWindowDrawList()->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), ImGui::GetColorU32(ImVec4(1.0, 0.0, 0.0, 1.0)));
    }
    ImGui::PopFont();
    ImGui::End();

}


// --------------------------------------------------------------------------------------------------------------------

UI* createUI()
{
    return new PluginUI();
}

// --------------------------------------------------------------------------------------------------------------------

END_NAMESPACE_DISTRHO
