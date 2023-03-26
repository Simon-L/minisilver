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
        if (ImGui::SmallButton("About")) {
            d_stdout("Popup!");
            ImGui::OpenPopup("aboutpopup");
        }
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
            ImGui::Text("developers, musicians and forum lurker over at the KVR forum, on various blogs\n");
            ImGui::Text("and on the Adafruit x0xb0x forum.\n");
            ImGui::Text("A definitive source of information was the Open303 project by Robin Schmidt, initiated in a KVR thread\n");
            ImGui::Text("back in 2009 and used as a reference for many aspects in this clone.   \n");
            ImGui::Text("Informed by tens of articles and blog posts, the x0xd0x wiki on x0xb0x at ladyada.net.\n");
            ImGui::Text("See full acknowledgments at https://synthe.tiseur.fr/opensilver\n");
            ImGui::Text("\n");
            ImGui::Text("Eternal thanks to antto for his support, help and suggestions, some of which appear\n");
            ImGui::Text("verbatim in the code.\n");
            ImGui::Text("Thanks to:\n");
            ImGui::Text("Robin Schmidt, guest, aciddose ...\n");
            // ImGui::SmallButton("Blabla");
            // ImGui::SmallButton("Blublu");
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
        generateLogo();
    }


    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(ImGui::GetStyle().FramePadding.x, 6.0));
    if (ImGui::Begin("Mini Silver", nullptr, ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_MenuBar))
    {   
        showMenuBar();
        ImGui::PopStyleVar();

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
