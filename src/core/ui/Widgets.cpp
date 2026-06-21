#include "Widgets.h"
#include <imgui/imgui.h>

namespace Nekres::UI {
    void DrawStatusIndicator(const char* label, bool detected, bool active)
    {
        ImVec2 p = ImGui::GetCursorScreenPos();
        float circleRadius = 5.0f;
        
        ImU32 color = detected ? (active ? IM_COL32(0, 255, 0, 255) : IM_COL32(255, 255, 255, 255)) : IM_COL32(255, 0, 0, 255);
        ImGui::GetWindowDrawList()->AddCircleFilled(ImVec2(p.x + circleRadius, p.y + circleRadius + 2.0f), circleRadius, color);
        
        ImVec2 pos = ImGui::GetCursorPos();
        ImGui::SetCursorPosX(pos.x + circleRadius * 2 + 5.0f);
        ImGui::TextUnformatted(label);
    }
}
