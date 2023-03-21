
void SetupImGuiStyle()
{
    // Fork of Classic Steam style from ImThemes
    ImGuiStyle& style = ImGui::GetStyle();
    
    style.Alpha = 1.0f;
    style.DisabledAlpha = 0.6000000238418579f;
    style.WindowPadding = ImVec2(8.0f, 8.0f);
    style.WindowRounding = 0.0f;
    style.WindowBorderSize = 1.0f;
    style.WindowMinSize = ImVec2(32.0f, 32.0f);
    style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
    style.WindowMenuButtonPosition = ImGuiDir_Left;
    style.ChildRounding = 0.0f;
    style.ChildBorderSize = 1.0f;
    style.PopupRounding = 0.0f;
    style.PopupBorderSize = 1.0f;
    style.FramePadding = ImVec2(4.0f, 3.0f);
    style.FrameRounding = 0.0f;
    style.FrameBorderSize = 1.0f;
    style.ItemSpacing = ImVec2(8.0f, 4.0f);
    style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
    style.CellPadding = ImVec2(4.0f, 2.0f);
    style.IndentSpacing = 21.0f;
    style.ColumnsMinSpacing = 6.0f;
    style.ScrollbarSize = 14.0f;
    style.ScrollbarRounding = 0.0f;
    style.GrabMinSize = 10.0f;
    style.GrabRounding = 0.0f;
    style.TabRounding = 0.0f;
    style.TabBorderSize = 0.0f;
    style.TabMinWidthForCloseButton = 0.0f;
    style.ColorButtonPosition = ImGuiDir_Right;
    style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
    style.SelectableTextAlign = ImVec2(0.0f, 0.0f);
    
    // style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    // style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.4980392158031464f, 0.4980392158031464f, 0.4980392158031464f, 1.0f);
    // style.Colors[ImGuiCol_WindowBg] = ImVec4(0.2862745225429535f, 0.3372549116611481f, 0.2588235437870026f, 1.0f);
    // style.Colors[ImGuiCol_ChildBg] = ImVec4(0.2862745225429535f, 0.3372549116611481f, 0.2588235437870026f, 1.0f);
    // style.Colors[ImGuiCol_PopupBg] = ImVec4(0.239215686917305f, 0.2666666805744171f, 0.2000000029802322f, 1.0f);
    // style.Colors[ImGuiCol_Border] = ImVec4(0.5372549295425415f, 0.5686274766921997f, 0.5098039507865906f, 0.5f);
    // style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.1372549086809158f, 0.1568627506494522f, 0.1098039224743843f, 0.5199999809265137f);
    // style.Colors[ImGuiCol_FrameBg] = ImVec4(0.239215686917305f, 0.2666666805744171f, 0.2000000029802322f, 1.0f);
    // style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.2666666805744171f, 0.2980392277240753f, 0.2274509817361832f, 1.0f);
    // style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.2980392277240753f, 0.3372549116611481f, 0.2588235437870026f, 1.0f);
    // style.Colors[ImGuiCol_TitleBg] = ImVec4(0.239215686917305f, 0.2666666805744171f, 0.2000000029802322f, 1.0f);
    // style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.2862745225429535f, 0.3372549116611481f, 0.2588235437870026f, 1.0f);
    // style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0f, 0.0f, 0.0f, 0.5099999904632568f);
    // style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.239215686917305f, 0.2666666805744171f, 0.2000000029802322f, 1.0f);
    // style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.3490196168422699f, 0.4196078479290009f, 0.3098039329051971f, 1.0f);
    // style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.2784313857555389f, 0.3176470696926117f, 0.239215686917305f, 1.0f);
    // style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.2470588237047195f, 0.2980392277240753f, 0.2196078449487686f, 1.0f);
    // style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.2274509817361832f, 0.2666666805744171f, 0.2078431397676468f, 1.0f);
    // style.Colors[ImGuiCol_CheckMark] = ImVec4(0.5882353186607361f, 0.5372549295425415f, 0.1764705926179886f, 1.0f);
    // style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.3490196168422699f, 0.4196078479290009f, 0.3098039329051971f, 1.0f);
    // style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.5372549295425415f, 0.5686274766921997f, 0.5098039507865906f, 0.5f);
    // style.Colors[ImGuiCol_Button] = ImVec4(0.2862745225429535f, 0.3372549116611481f, 0.2588235437870026f, 0.4000000059604645f);
    // style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.3490196168422699f, 0.4196078479290009f, 0.3098039329051971f, 1.0f);
    // style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.5372549295425415f, 0.5686274766921997f, 0.5098039507865906f, 0.5f);
    // style.Colors[ImGuiCol_Header] = ImVec4(0.3490196168422699f, 0.4196078479290009f, 0.3098039329051971f, 1.0f);
    // style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.3490196168422699f, 0.4196078479290009f, 0.3098039329051971f, 0.6000000238418579f);
    // style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.5372549295425415f, 0.5686274766921997f, 0.5098039507865906f, 0.5f);
    // style.Colors[ImGuiCol_Separator] = ImVec4(0.1372549086809158f, 0.1568627506494522f, 0.1098039224743843f, 1.0f);
    // style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.5372549295425415f, 0.5686274766921997f, 0.5098039507865906f, 1.0f);
    // style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.5882353186607361f, 0.5372549295425415f, 0.1764705926179886f, 1.0f);
    // style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.1882352977991104f, 0.2274509817361832f, 0.1764705926179886f, 0.0f);
    // style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.5372549295425415f, 0.5686274766921997f, 0.5098039507865906f, 1.0f);
    // style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.5882353186607361f, 0.5372549295425415f, 0.1764705926179886f, 1.0f);
    // style.Colors[ImGuiCol_Tab] = ImVec4(0.3490196168422699f, 0.4196078479290009f, 0.3098039329051971f, 1.0f);
    // style.Colors[ImGuiCol_TabHovered] = ImVec4(0.5372549295425415f, 0.5686274766921997f, 0.5098039507865906f, 0.7799999713897705f);
    // style.Colors[ImGuiCol_TabActive] = ImVec4(0.5882353186607361f, 0.5372549295425415f, 0.1764705926179886f, 1.0f);
    // style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.239215686917305f, 0.2666666805744171f, 0.2000000029802322f, 1.0f);
    // style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.3490196168422699f, 0.4196078479290009f, 0.3098039329051971f, 1.0f);
    // style.Colors[ImGuiCol_PlotLines] = ImVec4(0.6078431606292725f, 0.6078431606292725f, 0.6078431606292725f, 1.0f);
    // style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.5882353186607361f, 0.5372549295425415f, 0.1764705926179886f, 1.0f);
    // style.Colors[ImGuiCol_PlotHistogram] = ImVec4(1.0f, 0.7764706015586853f, 0.2784313857555389f, 1.0f);
    // style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 0.6000000238418579f, 0.0f, 1.0f);
    // style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.239215686917305f, 0.2666666805744171f, 0.2000000029802322f, 1.0f);
    // style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.3098039329051971f, 0.3098039329051971f, 0.3490196168422699f, 1.0f);
    // style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.2274509817361832f, 0.2274509817361832f, 0.2470588237047195f, 1.0f);
    // style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    // style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.05999999865889549f);
    // style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.5882353186607361f, 0.5372549295425415f, 0.1764705926179886f, 1.0f);
    // style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.729411780834198f, 0.6666666865348816f, 0.239215686917305f, 1.0f);
    // style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.5882353186607361f, 0.5372549295425415f, 0.1764705926179886f, 1.0f);
    // style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.699999988079071f);
    // style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.2000000029802322f);
    // style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.3499999940395355f);
}

void setupSilverboxColors() {
    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text]                   = ImVec4(0.19f, 0.18f, 0.18f, 1.00f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.87f, 0.87f, 0.87f, 1.00f);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.87f, 0.87f, 0.87f, 1.00f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
    colors[ImGuiCol_Border]                 = ImVec4(0.96f, 0.96f, 0.96f, 0.50f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.63f, 0.60f, 0.59f, 0.52f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.63f, 0.60f, 0.59f, 1.00f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.76f, 0.75f, 0.74f, 1.00f);
    colors[ImGuiCol_TitleBg]                = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.87f, 0.87f, 0.87f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.19f, 0.18f, 0.18f, 0.51f);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.99f, 0.99f, 0.99f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.76f, 0.75f, 0.74f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.60f, 0.24f, 0.25f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.85f, 0.19f, 0.23f, 1.00f);
    colors[ImGuiCol_CheckMark]              = ImVec4(0.85f, 0.19f, 0.23f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.76f, 0.75f, 0.74f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.77f, 0.17f, 0.21f, 0.50f);
    colors[ImGuiCol_Button]                 = ImVec4(0.87f, 0.87f, 0.87f, 0.40f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.99f, 0.99f, 0.99f, 1.00f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.96f, 0.96f, 0.96f, 0.50f);
    colors[ImGuiCol_Header]                 = ImVec4(0.99f, 0.99f, 0.99f, 1.00f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.99f, 0.99f, 0.99f, 0.60f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.96f, 0.96f, 0.96f, 0.50f);
    colors[ImGuiCol_Separator]              = ImVec4(0.63f, 0.60f, 0.59f, 1.00f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(0.85f, 0.19f, 0.23f, 1.00f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(0.19f, 0.18f, 0.18f, 0.00f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.60f, 0.24f, 0.25f, 1.00f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.85f, 0.19f, 0.23f, 1.00f);
    colors[ImGuiCol_Tab]                    = ImVec4(0.99f, 0.99f, 0.99f, 1.00f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.85f, 0.19f, 0.23f, 1.00f);
    colors[ImGuiCol_TabActive]              = ImVec4(0.85f, 0.19f, 0.23f, 1.00f);
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.99f, 0.99f, 0.99f, 1.00f);
    colors[ImGuiCol_PlotLines]              = ImVec4(0.85f, 0.19f, 0.23f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(0.85f, 0.19f, 0.23f, 1.00f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(0.85f, 0.19f, 0.23f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(0.77f, 0.17f, 0.21f, 1.00f);
    colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
    colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.60f, 0.24f, 0.25f, 1.00f);
    colors[ImGuiCol_TableBorderLight]       = ImVec4(0.60f, 0.24f, 0.25f, 1.00f);
    colors[ImGuiCol_TableRowBg]             = ImVec4(0.19f, 0.18f, 0.18f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt]          = ImVec4(0.19f, 0.18f, 0.18f, 0.06f);
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.85f, 0.19f, 0.23f, 1.00f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(0.85f, 0.19f, 0.23f, 1.00f);
    colors[ImGuiCol_NavHighlight]           = ImVec4(0.85f, 0.19f, 0.23f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(0.19f, 0.18f, 0.18f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.00f, 0.00f, 1.00f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
}