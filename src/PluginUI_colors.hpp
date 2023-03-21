int Group1[] = {
	ImGuiCol_TitleBgCollapsed,
	ImGuiCol_TableRowBg,
};
int Group1_size = sizeof(Group1) / sizeof(int);

int Group2[] = {
	ImGuiCol_Border,
	ImGuiCol_ButtonActive,
	ImGuiCol_HeaderActive,
	ImGuiCol_SeparatorHovered,
	ImGuiCol_TabHovered,
};
int Group2_size = sizeof(Group2) / sizeof(int);

int Group3[] = {
	ImGuiCol_CheckMark,
	ImGuiCol_SeparatorActive,
	ImGuiCol_TabActive,
	ImGuiCol_PlotLinesHovered,
	ImGuiCol_TextSelectedBg,
	ImGuiCol_NavHighlight,
};
int Group3_size = sizeof(Group3) / sizeof(int);

int Group4[] = {
	ImGuiCol_NavWindowingDimBg,
	ImGuiCol_ModalWindowDimBg,
};
int Group4_size = sizeof(Group4) / sizeof(int);

int Group5[] = {
	ImGuiCol_Text,
	ImGuiCol_TableRowBgAlt,
	ImGuiCol_NavWindowingHighlight,
};
int Group5_size = sizeof(Group5) / sizeof(int);

int Group6[] = {
	ImGuiCol_BorderShadow,
	ImGuiCol_Separator,
};
int Group6_size = sizeof(Group6) / sizeof(int);

int Group7[] = {
	ImGuiCol_PopupBg,
	ImGuiCol_FrameBg,
	ImGuiCol_TitleBg,
	ImGuiCol_MenuBarBg,
	ImGuiCol_TabUnfocused,
	ImGuiCol_TableHeaderBg,
};
int Group7_size = sizeof(Group7) / sizeof(int);

int Group8[] = {
	ImGuiCol_WindowBg,
	ImGuiCol_ChildBg,
	ImGuiCol_TitleBgActive,
	ImGuiCol_Button,
};
int Group8_size = sizeof(Group8) / sizeof(int);

int Group9[] = {
	ImGuiCol_ScrollbarBg,
	ImGuiCol_ButtonHovered,
	ImGuiCol_Header,
	ImGuiCol_HeaderHovered,
	ImGuiCol_Tab,
	ImGuiCol_TabUnfocusedActive,
};
int Group9_size = sizeof(Group9) / sizeof(int);

int Group10[] = {
	ImGuiCol_TextDisabled
};
int Group10_size = sizeof(Group10) / sizeof(int);

int Group11[] = {
	ImGuiCol_FrameBgActive,
	ImGuiCol_FrameBgHovered,
	ImGuiCol_ScrollbarGrab,
	ImGuiCol_ScrollbarGrabActive,
	ImGuiCol_ScrollbarGrabHovered,
	ImGuiCol_PlotLines,
	ImGuiCol_PlotHistogramHovered,
	ImGuiCol_PlotHistogram,
	ImGuiCol_TableBorderStrong,
	ImGuiCol_TableBorderLight,
	ImGuiCol_ResizeGrip,
	ImGuiCol_ResizeGripActive,
	ImGuiCol_ResizeGripHovered,
	ImGuiCol_DragDropTarget,
	ImGuiCol_SliderGrab,
	ImGuiCol_SliderGrabActive,
};
int Group11_size = sizeof(Group11) / sizeof(int);

constexpr int Groups_count = 11;
int* Groups[Groups_count] = {
	Group1,
	Group2,
	Group3,
	Group4,
	Group5,
	Group6,
	Group7,
	Group8,
	Group9,
	Group10,
	Group11,
};

const int* Groups_size[Groups_count] = {
	&Group1_size,
	&Group2_size,
	&Group3_size,
	&Group4_size,
	&Group5_size,
	&Group6_size,
	&Group7_size,
	&Group8_size,
	&Group9_size,
	&Group10_size,
	&Group11_size,
};

ImVec4 AccentDim2 = ImVec4(154.0f/255.0f, 61.0f/255.0f, 65.0f/255.0f, 1.0f); // cordovan
ImVec4 AccentDim1 = ImVec4(197.0f/255.0f, 44.0f/255.0f, 53.0f/255.0f, 1.0f); // persian-red
ImVec4 Accent = ImVec4(217.0f/255.0f, 48.0f/255.0f, 58.0f/255.0f, 1.0f); // poppy
ImVec4 Dark0 = ImVec4(49.0f/255.0f, 46.0f/255.0f, 47.0f/255.0f, 1.0f); // jet
ImVec4 Dark1 = ImVec4(69.0f/255.0f, 67.0f/255.0f, 67.0f/255.0f, 1.0f); // onyx
ImVec4 Dark2 = ImVec4(160.0f/255.0f, 152.0f/255.0f, 151.0f/255.0f, 1.0f); // taupe-gray
ImVec4 Dark3 = ImVec4(193.0f/255.0f, 190.0f/255.0f, 189.0f/255.0f, 1.0f); // silver
ImVec4 Light0 = ImVec4(222.0f/255.0f, 221.0f/255.0f, 221.0f/255.0f, 1.0f); // platinum
ImVec4 Light1 = ImVec4(244.0f/255.0f, 244.0f/255.0f, 245.0f/255.0f, 1.0f); // antiflash-white
ImVec4 Light2 = ImVec4(252.0f/255.0f, 252.0f/255.0f, 252.0f/255.0f, 1.0f); // white

ImVec4 colorPerGroup[10] = {
	Dark0, // 1 Row bg (minor)
	Light1, // 2 active/hover/border : light accent
	Accent, // 3 active accent
	ImVec4(0.0,0.0,1.0,1.0), // 4 ignore
	Dark0, // 5 text
	Dark2, // 6 border / separator
	Light1, //  7 bg dark
	Light0, // 8 bg
	Light2,// 9 bg light
};

ImVec4 Group11_colors[32] = {
	Dark3, //FrameBgActive
	Dark2, //FrameBgHovered
	Dark3, //ScrollbarGrab
	Accent, //ScrollbarGrabActive
	AccentDim2, //ScrollbarGrabHovered
	Accent, //PlotLines
	AccentDim1, //PlotHistogramHovered
	Accent, //PlotHistogram
	AccentDim2, //TableBorderStrong
	AccentDim2, //TableBorderLight
	Dark0, //ResizeGrip
	Accent, //ResizeGripActive,
	AccentDim2, //ResizeGripHovered,
	Accent, //DragDropTarget
	Dark3, // SliderGrab
	AccentDim1, // SliderGrabActive,
};

void applyColorKeepAlpha(ImVec4 apply, ImVec4* dest) { dest->x = apply.x; dest->y = apply.y; dest->z = apply.z; }
void applySilverboxTheme() {
	ImGuiStyle& style = ImGui::GetStyle();
	for (int g = 0; g < Groups_count-1; ++g)
	{   
	    for (int c = 0; c < *Groups_size[g]; ++c)
	    {
			int color;
	        color = Groups[g][c];
	        auto colorVec4 = &style.Colors[color];
	        applyColorKeepAlpha(colorPerGroup[g], colorVec4);
	        // const char* name = ImGui::GetStyleColorName(color);
	        // ImGui::TextUnformatted(name);                
	        // ImGui::SameLine();
	    }
	    for (int c = 0; c < Group11_size; ++c)
	    {
	        int color = Groups[10][c];
	        auto colorVec4 = &style.Colors[color];
	        applyColorKeepAlpha(Group11_colors[c], colorVec4);
	    }
	    // ImGui::NewLine();
	    // col = Groups[g][0];
	    // ImGui::PushID(col);
	    // ImGui::ColorEdit4("##color", (float*)&style.Colors[col], ImGuiColorEditFlags_AlphaBar);
	    // ImGui::PopID();
	    // ImGui::Separator();
	}
}