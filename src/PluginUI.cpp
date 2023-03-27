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

void PluginUI::generateLogo() {
    auto logo_document = lunasvg::Document::loadFromFile("res/logo.svg");
    if(!logo_document) {
        d_stdout("Logo document error");
        return; 
    }
    base_dimension = ImGui::GetWindowWidth() * logo_width;
    auto bitmap = lunasvg::Bitmap(base_dimension, base_dimension / 11.0);
    bitmap.clear(0x00000000);
    d_stdout("logo_document %f %f", logo_document->width(), logo_document->height());

    logo_document->setMatrix(logo_document->matrix().scale(base_dimension/logo_document->width(), (base_dimension / 11.0)/logo_document->height()));
    logo_document->render(bitmap);
    if(!bitmap.valid()) {
        d_stdout("Logo bitmap error");
        return; 
    }

    bitmap.convertToRGBA();
    d_stdout("bitmap %d %d", bitmap.width(), bitmap.height());

    glGenTextures(1, &logo_tex);
    glBindTexture(GL_TEXTURE_2D, logo_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, base_dimension, base_dimension/11.0, 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap.data());
}

void PluginUI::showMenuBar()
{
    if (ImGui::BeginMenuBar()) {
        float menu_height = (6.0 + 6.0 + ImGui::GetTextLineHeight());
        float logo_height = (base_dimension / 11.0);
        float toply = (menu_height - logo_height) * 0.5;
        auto topl = ImVec2(ImGui::GetStyle().FramePadding.x, std::round(toply));
        auto botr = ImVec2(topl.x + base_dimension, topl.y + base_dimension / 11.0);
        ImGui::GetWindowDrawList()->AddImage((void*)(intptr_t)logo_tex, topl, botr);
        float button_x = getWidth();
        button_x -= ImGui::GetStyle().FramePadding.x * 5;
        button_x -= ImGui::CalcTextSize("About").x;
        button_x -= ImGui::GetStyle().ItemSpacing.x;
        button_x -= ImGui::CalcTextSize("Tweaks").x;
        ImGui::SetCursorPosX(button_x);
        ImGui::SmallButton("Tweaks");
        ImGui::PushStyleColor(ImGuiCol_Button, ImGui::IsPopupOpen("aboutpopup") ? Accent : ImGui::GetStyle().Colors[ImGuiCol_Button]);
        if (ImGui::SmallButton("About")) {
            ImGui::OpenPopup("aboutpopup");
        }
        ImGui::PopStyleColor();
        ImVec2 popupSize;
        popupSize.x = getWidth() * 0.8;
        popupSize.y = (getHeight() - menu_height) * 0.95;
        ImVec2 popupPos;
        popupPos.x = (getWidth() - popupSize.x) * 0.5;
        popupPos.y = menu_height + ((getHeight() - menu_height) - popupSize.y) * 0.5;
        ImGui::SetNextWindowPos(popupPos);
        ImGui::SetNextWindowSize(popupSize);
        if (ImGui::BeginPopup("aboutpopup")) {
            ImGui::Text("Mini Silver");
            ImGui::Text("Digital Roland TB-303 clone");
            ImGui::Text("\n");
            ImGui::Text("Based on hundreds of contributions, either code, text, images, suggestions, thoughts from\n");
            ImGui::Text("developers, musicians and forum members over at the KVR forum, on various blogs\n");
            ImGui::Text("and on the Adafruit x0xb0x forum.\n");
            ImGui::Text("A definitive source of information was the Open303 project by Robin Schmidt, initiated in a KVR thread\n");
            ImGui::Text("back in 2009 and used as a reference for many aspects in this clone.\n");
            ImGui::Text("Informed by tens of articles and blog posts, the x0xd0x wiki on x0xb0x at ladyada.net.\n");
            ImGui::Text("See full acknowledgments at https://synthe.tiseur.fr/opensilver\n");
            ImGui::Text("\n");
            ImGui::Text("Eternal thanks to antto for his support, help and suggestions, some of which appear\n");
            ImGui::Text("verbatim in the code.\n");
            ImGui::Text("Thanks to:\n");
            ImGui::Text("Robin Schmidt, guest, aciddose ...\n");
            ImGui::EndPopup();
        }
        ImGui::EndMenuBar();
    }
}

void PluginUI::onImGuiDisplay()
{   

    const float width = getWidth();
    const float height = getHeight();

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(width, height));

    ImGui::PushFont(font1);
    if (cutoff_knob == nullptr) {
        cutoff_knob = std::make_unique<ImGuiKnobsSVG::Knob>("res/303Knob_0_8.svg", ImGuiKnobVariant_Stepped, &v_cutoff, 0.0f, 1.0f, 100);
        cutoff_knob->setBg("res/303Knob_0_8_bg.svg");
        resonance_knob = std::make_unique<ImGuiKnobsSVG::Knob>("res/303Knob_0_4.svg", ImGuiKnobVariant_Stepped, &v_resonance, 0.0f, 1.0f, 100);
        resonance_knob->setBg("res/303Knob_0_4_bg.svg");
        envmod_knob = std::make_unique<ImGuiKnobsSVG::Knob>("res/303Knob_0_4.svg", ImGuiKnobVariant_Stepped, &v_envmod, 0.0f, 1.0f, 100);
        envmod_knob->setBg("res/303Knob_0_4_bg.svg");
        decay_knob = std::make_unique<ImGuiKnobsSVG::Knob>("res/303Knob_0_4.svg", ImGuiKnobVariant_Stepped, &v_decay, -2.223, 1.223, 100);
        decay_knob->setBg("res/303Knob_0_4_bg.svg");
        accent_knob = std::make_unique<ImGuiKnobsSVG::Knob>("res/303Knob_0_4.svg", ImGuiKnobVariant_Stepped, &v_accent, 0.0f, 1.0f, 100);
        accent_knob->setBg("res/303Knob_0_4_bg.svg");
        tuning_knob = std::make_unique<ImGuiKnobsSVG::Knob>("res/303Knob_0_24.svg", ImGuiKnobVariant_Stepped, &v_tuning, -1.0f, 1.0f);
        vcadecay_knob = std::make_unique<ImGuiKnobsSVG::Knob>("res/303Knob_0_24.svg", ImGuiKnobVariant_Stepped, &v_vcadecay, -1.0f, 1.0f);
        generateLogo();
    }


    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(ImGui::GetStyle().FramePadding.x, 6.0));
    if (ImGui::Begin("Mini Silver", nullptr, ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_MenuBar))
    {   
        showMenuBar();
        ImGui::PopStyleVar();

        if (ImGuiKnobs::Knob("CUT OFF FREQ", &v_cutoff, 0.0f, 1.0f, 0.005f, "%.3f", ImGuiKnobVariant_Stepped, 100)) {
            // v_cutoff was changed
            d_stdout("CUT OFF FREQ %f -> %f", v_cutoff, paramLog(v_cutoff, 0.5f, 0.1f, 0.85, 7.4));
        }
        cutoff_knob->paint();
        ImGui::SameLine();

        if (ImGuiKnobs::Knob("RESONANCE", &v_resonance, 0.0f, 1.0f, 0.005f, "%.3f", ImGuiKnobVariant_Stepped, 100)) {
            // 
        }
        resonance_knob->paint();
        ImGui::SameLine();

        if (ImGuiKnobs::Knob("ENV MOD", &v_envmod, 0.0f, 1.0f, 0.003f, "%.3f", ImGuiKnobVariant_Stepped, 100)) {
            // 
            d_stdout("ENV MOD %f -> %f", v_envmod, paramLog(v_envmod, 0.5f, 0.1f, 0.25, 0.887));
        }
        envmod_knob->paint();
        ImGui::SameLine();

        if (ImGuiKnobs::Knob("DECAY", &v_decay, -2.223, 1.223, 0.01f, setTimeDisplayValueString(v_decay), ImGuiKnobVariant_Stepped, 100)) {
            // 
        }
        decay_knob->paint();
        ImGui::SameLine();

        if (ImGuiKnobs::Knob("ACCENT", &v_accent, 0.0f, 1.0f, 0.005f, "%.3f", ImGuiKnobVariant_Stepped, 100)) {
            // 
        }
        accent_knob->paint();
        auto next_line = ImGui::GetCursorPos();
        ImGui::SameLine();

        auto wfm_topl = ImGui::GetCursorPos();
        auto hold_topl = ImGui::GetCursorPos();
        int but_w = 80;
        int but_h = 40;
        auto title_size = ImGui::CalcTextSize("HOLD VCA", NULL, false, width);
        hold_topl.y += title_size.y;
        hold_topl.y += (50 - but_h) * 0.5;
        hold_topl.y += ImGui::GetStyle().ItemSpacing.y;
        ImGui::BeginGroup();
        ImGui::GetCurrentWindow()->DC.CurrLineTextBaseOffset = 0;
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (but_w - title_size[0]) * 0.5f);
        ImGui::Text("%s", "HOLD VCA");
        ImGui::SetCursorPos(hold_topl);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, Accent);
        ImGui::Button("##hold", ImVec2(but_w, but_h));
        ImGui::PopStyleColor();
        ImGui::EndGroup();

        wfm_topl.x += but_w + ImGui::GetStyle().ItemSpacing.x;
        ImGui::SetCursorPos(wfm_topl);

        ImGui::BeginGroup();
        ImGui::Text("%s", "WAVEFORM");
        float wfm_slider_y = ImGui::GetStyle().FrameBorderSize * 2 + ImGui::GetStyle().FramePadding.y * 2 + ImGui::GetTextLineHeight();
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + (50 - wfm_slider_y) * 0.5);
        ImGui::SetNextItemWidth(but_w);
        ImGui::SliderInt("##waveforum", &wfm, 0, 1, wfm ? "PULSE" : "SAW", ImGuiSliderFlags_NoInput);
        ImGui::EndGroup();

        auto tuning_topl = hold_topl;
        tuning_topl.y += but_h + ImGui::GetStyle().ItemSpacing.y;
        tuning_topl.x += (but_w - 64) * 0.5;
        ImGui::SetCursorPos(tuning_topl);
        if (ImGuiKnobs::Knob("TUNING", &v_tuning, -1.0f, 1.0f, 0.01f, "%.3f", ImGuiKnobVariant_Stepped, 0, ImGuiKnobFlags_ValueTooltip|ImGuiKnobFlags_NoInput)) {
            // 
        }
        tuning_knob->paint();
        ImGui::SameLine();
        ImGui::SetCursorPosX(wfm_topl.x + (but_w - 64) * 0.5);
        if (ImGuiKnobs::Knob("VCA DEC", &v_vcadecay, -1.0f, 1.0f, 0.01f, "%.3f", ImGuiKnobVariant_Stepped, 0, ImGuiKnobFlags_ValueTooltip|ImGuiKnobFlags_NoInput)) {
            // 
        }
        vcadecay_knob->paint();

        ImGui::SetCursorPos(next_line);

        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        ImGui::Spacing();

        ImGui::Checkbox("Show demo window", &showDemo);
        if (showDemo) ImGui::ShowDemoWindow(&showDemo);
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
