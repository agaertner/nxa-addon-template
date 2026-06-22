#include "SettingsUI.h"
#include "../Settings.h"
#include "../services/Services.h"
#include "Theme.h"
#include "Widgets.h"
#include "pages/GeneralSettingsPage.h"
#include "pages/AudioSettingsPage.h"
#include <imgui/imgui.h>

namespace Nekres {

    SettingsUI::SettingsUI(const std::filesystem::path& settingsPath, AddonDefinition_t* addonDef)
        : m_settingsPath(settingsPath), m_addonDef(addonDef)
    {
        m_pages.push_back(std::make_unique<GeneralSettingsPage>(m_settingsPath));
        m_pages.push_back(std::make_unique<AudioSettingsPage>(m_settingsPath));
    }

    void SettingsUI::Draw()
    {
        ImFont* fontUI = nullptr;
        if (Services::m_nexus && Services::m_nexus->Core()) {
            fontUI = (ImFont*)Services::m_nexus->Core()->FontUI;
        }

        if (fontUI) {
            ImGui::PushFont(fontUI);
        }

        // Calculate the height needed for the footer.
        float footerHeight = ImGui::GetTextLineHeightWithSpacing() + ImGui::GetStyle().ItemSpacing.y * 3.0f + 5.0f;

        // Sidebar
        DrawSidebar(footerHeight);

        ImGui::SameLine();

        // Content Area
        DrawContent(footerHeight);

        // Footer
        DrawFooter();

        if (fontUI) {
            ImGui::PopFont();
        }
    }

    void SettingsUI::DrawSidebar(float footerHeight)
    {
        ImGui::PushStyleColor(ImGuiCol_ChildBg, UI::Theme::BackgroundSidebar);
        ImGui::BeginChild("Sidebar", ImVec2(140, -footerHeight), true);
        ImGui::PopStyleColor();

        ImGui::Spacing();
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 8.0f);
        
        ImGui::TextColored(UI::Theme::Accent, m_addonDef->Name);
        
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 8.0f);
        ImGui::SetWindowFontScale(0.80f);
        ImGui::TextDisabled("by %s", m_addonDef->Author);
        ImGui::SetWindowFontScale(1.0f);

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        for (size_t i = 0; i < m_pages.size(); ++i) {
            bool isSelected = (m_selectedTab == i);
            ImVec2 cursorPos = ImGui::GetCursorScreenPos();
            
            if (isSelected) {
                ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0,0,0,0));
                ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(1,1,1,0.05f));
                ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(1,1,1,0.05f));
                ImGui::PushStyleColor(ImGuiCol_Text, UI::Theme::Accent);
            } else {
                ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(1,1,1,0.05f));
                ImGui::PushStyleColor(ImGuiCol_Text, UI::Theme::TextUnselected);
            }

            std::string label = "    " + std::string(m_pages[i]->GetName());
            
            ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.0f, 0.5f));
            if (ImGui::Selectable(label.c_str(), isSelected, 0, ImVec2(0, 24))) {
                m_selectedTab = static_cast<int>(i);
            }
            ImGui::PopStyleVar();

            if (isSelected) {
                ImGui::GetWindowDrawList()->AddRectFilled(
                    ImVec2(cursorPos.x, cursorPos.y), 
                    ImVec2(cursorPos.x + 3.0f, cursorPos.y + 24.0f), 
                    ImGui::GetColorU32(UI::Theme::Accent)
                );
            }

            if (isSelected) {
                ImGui::PopStyleColor(4);
            } else {
                ImGui::PopStyleColor(2);
            }
        }
        ImGui::EndChild();
    }

    void SettingsUI::DrawContent(float footerHeight)
    {
        ImGui::PushStyleColor(ImGuiCol_ChildBg, UI::Theme::BackgroundContent);
        
        ImVec2 padding = ImGui::GetStyle().WindowPadding;
        padding.x += 5.0f;
        padding.y += 5.0f;
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, padding);
        
        ImGui::BeginChild("Content", ImVec2(0, -footerHeight), true);
        ImGui::PopStyleVar();
        ImGui::PopStyleColor();

        if (m_pages.empty()) {
            ImGui::EndChild();
            return;
        }

        ImGui::TextColored(UI::Theme::Accent, m_pages[m_selectedTab]->GetTitle());
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::PushStyleColor(ImGuiCol_Header, UI::Theme::HeaderColor);
        ImGui::PushStyleColor(ImGuiCol_HeaderHovered, UI::Theme::AccentHover);
        ImGui::PushStyleColor(ImGuiCol_HeaderActive, UI::Theme::Accent);

        m_pages[m_selectedTab]->Render();
        
        ImGui::PopStyleColor(3); // Pop Header colors
        ImGui::EndChild();
    }

    void SettingsUI::DrawFooter()
    {
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 3.0f);

#ifdef USE_MUMBLE
        // MumbleLink Indicator
        bool mumbleDetected = false;
        bool mumbleActive = false;
        if (Services::m_mumble && Services::m_mumble->Data()) {
            mumbleDetected = true;
            if (Services::m_mumble->IsActive()) {
                mumbleActive = true;
            }
        }
        UI::DrawStatusIndicator("MumbleLink", mumbleDetected, mumbleActive);
#endif
#ifdef USE_RTAPI
        // RealTime API Indicator
        bool rtapiDetected = false;
        bool rtapiActive = false;
        if (Services::m_rtapi && Services::m_rtapi->Data()) {
            rtapiDetected = true;
            if (Services::m_rtapi->Data()->GameBuild != 0) {
                rtapiActive = true;
            }
        }
        ImGui::SameLine();
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
        UI::DrawStatusIndicator("RealTime API", rtapiDetected, rtapiActive);
#endif

        // Right side: Name of Addon and version
        char versionText[256];
        snprintf(versionText, sizeof(versionText), "%s v%d.%d.%d.%d", m_addonDef->Name, m_addonDef->Version.Major, m_addonDef->Version.Minor, m_addonDef->Version.Build, m_addonDef->Version.Revision);
        
        ImGui::SameLine(ImGui::GetWindowWidth() - ImGui::CalcTextSize(versionText).x - ImGui::GetStyle().WindowPadding.x);
        ImGui::TextUnformatted(versionText);
    }
}
