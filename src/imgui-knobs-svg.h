#include "include/lunasvg.h"

#define IMGUIKNOBSSVG_PI 3.14159265358979323846f

namespace ImGuiKnobsSVG {

	struct Knob {

		uint32_t image_width;
		uint32_t image_height;

		GLuint tex;
		GLuint fg_tex;
		GLuint bg_tex;

		std::unique_ptr<lunasvg::Document> document;
		std::unique_ptr<lunasvg::Document> fg_document;
		std::unique_ptr<lunasvg::Document> bg_document;

		std::string path;
		ImGuiKnobVariant variant;
		float size;
		float* value;
		float min, max;

		Knob(const std::string& path, ImGuiKnobVariant variant, float* value, float min, float max, float _size = 0) :
			path(path), variant(variant), value(value), min(min), max(max)
		{
			size = _size == 0 ? ImGui::GetTextLineHeight() * 4.0f : _size * ImGui::GetIO().FontGlobalScale;
			switch (variant) {
			case ImGuiKnobVariant_WiperOnly:
			case ImGuiKnobVariant_Wiper:
				image_height = image_width = (uint32_t)std::round(size * 0.7);
				break;
			case ImGuiKnobVariant_Stepped:
			case ImGuiKnobVariant_WiperDot:
				image_height = image_width = (uint32_t)std::round(size * 0.61);
				break;
			case ImGuiKnobVariant_Dot:
			case ImGuiKnobVariant_Tick:
				image_height = image_width = (uint32_t)std::round(size * 0.45);
				break;
			case ImGuiKnobVariant_Space:
				image_height = image_width = (uint32_t)std::round(size * 0.35);
				break;
			}

			document = lunasvg::Document::loadFromFile(path);
			if(!document) {
				d_stdout("Document error");
				return;	
			}
			auto bitmap = lunasvg::Bitmap(image_width, image_height);
			bitmap.clear(0x00000000);

			document->setMatrix(document->matrix().scale((float)(image_width)/document->width(), (float)(image_height)/document->height()));
			document->render(bitmap);
			if(!bitmap.valid()) {
				d_stdout("bitmap error");
				return;	
			}

			bitmap.convertToRGBA();

			glGenTextures(1, &tex);
			glBindTexture(GL_TEXTURE_2D, tex);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap.data());
		}

		void setBg(const std::string& _path) {
			bg_document = lunasvg::Document::loadFromFile(_path);
			if(!bg_document) {
				d_stdout("BG Document error");
				return;	
			}
			auto bitmap = lunasvg::Bitmap(image_width, image_height);
			bitmap.clear(0x00000000);
			bg_document->setMatrix(bg_document->matrix().scale((float)(image_width)/document->width(), (float)(image_height)/document->height()));
			bg_document->render(bitmap);
			if(!bitmap.valid()) {
				d_stdout("BG bitmap error");
				return;	
			}

			bitmap.convertToRGBA();

			glGenTextures(1, &bg_tex);
			glBindTexture(GL_TEXTURE_2D, bg_tex);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap.data());
		}

		void setFg(const std::string& _path) {
			fg_document = lunasvg::Document::loadFromFile(_path);
			if(!fg_document) {
				d_stdout("FG Document error");
				return;	
			}
			auto bitmap = lunasvg::Bitmap(image_width, image_height);
			bitmap.clear(0x00000000);
			fg_document->setMatrix(fg_document->matrix().scale((float)(image_width)/document->width(), (float)(image_height)/document->height()));
			fg_document->render(bitmap);
			if (!bitmap.valid()) {
				d_stdout("FG bitmap error");
				return;	
			}

			bitmap.convertToRGBA();

			glGenTextures(1, &fg_tex);
			glBindTexture(GL_TEXTURE_2D, fg_tex);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap.data());
		}

		inline ImVec2 rotate_point(ImVec2 p, ImVec2 center, float angle) {
		  float s = sin(angle);
		  float c = cos(angle);
		  ImVec2 pr = ImVec2(p);
		  pr.x -= center.x; pr.y -= center.y;
		  float xnew = pr.x * c - pr.y * s;
		  float ynew = pr.x * s + pr.y * c;
		  pr.x = xnew + center.x; pr.y = ynew + center.y;
		  return pr;
		}

		void paint() {
			auto start = ImGui::GetItemRectMin();
			start.y += ImGui::GetTextLineHeight() + ImGui::GetStyle().ItemSpacing.y;
			start.x += size/2.0;
			start.y += size/2.0;
			auto p1 = ImVec2(start.x - (image_width/2), start.y - (image_height/2));
			auto p2 = ImVec2(p1.x + image_width, p1.y);
			auto p3 = ImVec2(p1.x + image_width, p1.y + image_height);
			auto p4 = ImVec2(p3.x - image_width, p3.y);
			if (bg_document != nullptr) ImGui::GetWindowDrawList()->AddImageQuad((void*)(intptr_t)bg_tex, p1, p2, p3, p4);
			float angle = (2.25-0.75) * ((*value-min) * (1.0/(max-min))) + 0.75;
			auto p1_r = rotate_point(p1, start, IMGUIKNOBSSVG_PI * 0.5 + IMGUIKNOBSSVG_PI * angle);
			auto p2_r = rotate_point(p2, start, IMGUIKNOBSSVG_PI * 0.5 + IMGUIKNOBSSVG_PI * angle);
			auto p3_r = rotate_point(p3, start, IMGUIKNOBSSVG_PI * 0.5 + IMGUIKNOBSSVG_PI * angle);
			auto p4_r = rotate_point(p4, start, IMGUIKNOBSSVG_PI * 0.5 + IMGUIKNOBSSVG_PI * angle);
			ImGui::GetWindowDrawList()->AddImageQuad((void*)(intptr_t)tex, p1_r, p2_r, p3_r, p4_r);
			if (fg_document != nullptr) ImGui::GetWindowDrawList()->AddImageQuad((void*)(intptr_t)fg_tex, p1, p2, p3, p4);
			// ImGui::GetWindowDrawList()->AddRect(p1, p3, ImGui::GetColorU32(ImVec4(0.0, 0.0, 1.0, 1.0)));
		}

	};
}