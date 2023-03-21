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
    if (ImGui::Begin("Mini Silver", nullptr, ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoCollapse))
    {
        static char aboutText[256] = "This is a demo plugin made with ImGui,\ndemoing direct DSP instance access from the GUI\n(you should avoid doing this!).\nClick the button below to call\nthe method on the current DSP instance.\n";
        ImGui::InputTextMultiline("About", aboutText, sizeof(aboutText));

        if (ImGui::SliderFloat("Gain (dB)", &fGain, -90.0f, 30.0f))
        {
            if (ImGui::IsItemActivated())
                editParameter(kParamGain, true);

            setParameterValue(kParamGain, fGain);
        }

        if (ImGui::IsItemDeactivated())
        {
            editParameter(kParamGain, false);
        }

        ImGui::LabelText("<- OutputParam", "%f", fOutputParam);

        if (ImGui::Button("Call & print PluginDSP::publicMethod()")) {
            PluginDSP* const dspPtr = (PluginDSP*)getPluginInstancePointer();
            if (dspPtr != NULL) { 
                d_stdout("publicMethod return value: %d", dspPtr->publicMethod());
            }
        }

        ImGui::Checkbox("Show demo window", &showDemo);
        if (showDemo) ImGui::ShowDemoWindow(&showDemo);

        ImGui::Separator();
        ImGuiStyle& style = ImGui::GetStyle();
        int col;
        for (int g = 0; g < Groups_count-1; ++g)
        {   
            char groupname[16];
            sprintf(groupname, "Group%d", g+1);
            ImGui::Text(groupname);
            for (int i = 0; i < *Groups_size[g]; ++i)
            {
                col = Groups[g][i];
                char colorname[32];
                sprintf(colorname, "%s (%.3f)", ImGui::GetStyleColorName(col), style.Colors[col].w);
                // const char* name = ;
                ImGui::TextUnformatted(colorname);                
                ImGui::SameLine();
            }
            ImGui::NewLine();
            col = Groups[g][0];
            ImGui::PushID(col);
            ImGui::ColorEdit4("##color", (float*)&style.Colors[col], ImGuiColorEditFlags_AlphaBar);
            ImGui::PopID();
            ImGui::Separator();
        }
        // for (int i = 0; i < Group11_size; ++i)
        // {
        //     col = Groups[10][i];
        //     const char* name = ImGui::GetStyleColorName(col);
        //     ImGui::TextUnformatted(name);                
        //     ImGui::PushID(col);
        //     ImGui::ColorEdit4("##color", (float*)&style.Colors[col], ImGuiColorEditFlags_AlphaBar);
        //     ImGui::PopID();
        //     ImGui::Separator();
        // }
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
