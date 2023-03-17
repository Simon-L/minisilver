#include "PluginUI.hpp"

START_NAMESPACE_DISTRHO

PluginUI::PluginUI()
    : UI(DISTRHO_UI_DEFAULT_WIDTH, DISTRHO_UI_DEFAULT_HEIGHT),
      fResizeHandle(this)
{
    setGeometryConstraints(DISTRHO_UI_DEFAULT_WIDTH, DISTRHO_UI_DEFAULT_HEIGHT, true);

    // hide handle if UI is resizable
    if (isResizable())
        fResizeHandle.hide();
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
    const float margin = 20.0f * getScaleFactor();

    ImGui::SetNextWindowPos(ImVec2(margin, margin));
    ImGui::SetNextWindowSize(ImVec2(width - 2 * margin, height - 2 * margin));

    if (ImGui::Begin("__IMGUINAME__", nullptr, ImGuiWindowFlags_NoResize))
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
    }
    ImGui::End();

}


// --------------------------------------------------------------------------------------------------------------------

UI* createUI()
{
    return new PluginUI();
}

// --------------------------------------------------------------------------------------------------------------------

END_NAMESPACE_DISTRHO
