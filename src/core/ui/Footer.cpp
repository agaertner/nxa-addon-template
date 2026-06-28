#include "Footer.h"
#include <imgui.h>

namespace Nekres::UI {
    
    Footer::Footer(AddonDefinition_t* addonDef) : NexusSDK::UI::ControlBase(), m_addonDef(addonDef) 
    {
    }

    void Footer::OnDraw(const NexusSDK::UI::Rectangle& bounds)
    {
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 3.0f);

        // MumbleLink Indicator
        bool mumbleDetected = false;
        bool mumbleActive = false;
        if (NexusSDK::Mumble && NexusSDK::Mumble->Data()) {
            mumbleDetected = true;
            if (NexusSDK::Mumble->IsActive()) {
                mumbleActive = true;
            }
        }
        DrawStatusIndicator("MumbleLink", mumbleDetected, mumbleActive);

        // RealTime API Indicator
        bool rtapiDetected = false;
        bool rtapiActive = false;
        if (NexusSDK::RTAPI && NexusSDK::RTAPI->Data()) {
            rtapiDetected = true;
            if (NexusSDK::RTAPI->Data()->GameBuild != 0) {
                rtapiActive = true;
            }
        }
        ImGui::SameLine();
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
        DrawStatusIndicator("RealTime API", rtapiDetected, rtapiActive);

        // Right side: Name of Addon and version
        char versionText[256];
        snprintf(versionText, sizeof(versionText), "%s v%d.%d.%d.%d", m_addonDef->Name, m_addonDef->Version.Major, m_addonDef->Version.Minor, m_addonDef->Version.Build, m_addonDef->Version.Revision);
        
        ImGui::SameLine(ImGui::GetWindowWidth() - ImGui::CalcTextSize(versionText).x - ImGui::GetStyle().WindowPadding.x);
        ImGui::TextUnformatted(versionText);
    }

    void Footer::DrawStatusIndicator(const char* label, bool detected, bool active)
    {
        ImVec2 p = ImGui::GetCursorScreenPos();
        float circleRadius = 3.0f;
        
        ImU32 color = detected ? (active ? IM_COL32(0, 255, 0, 255) : IM_COL32(255, 255, 255, 255)) : IM_COL32(255, 0, 0, 255);
        ImGui::GetWindowDrawList()->AddCircleFilled(ImVec2(p.x + circleRadius, p.y + ImGui::GetTextLineHeight() * 0.5f), circleRadius, color);
        
        ImVec2 pos = ImGui::GetCursorPos();
        ImGui::SetCursorPosX(pos.x + circleRadius * 2 + 5.0f);
        ImGui::TextUnformatted(label);
    }
}
