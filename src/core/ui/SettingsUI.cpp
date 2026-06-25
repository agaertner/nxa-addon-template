#include "SettingsUI.h"
#include "../Settings.h"
#include "Theme.h"
#include "pages/GeneralSettingsPage.h"
#include "pages/AudioSettingsPage.h"
#include <imgui.h>
#include <lib-nxa-sdk/src/utils/ImStateGuards.h>

namespace Nekres {

    void ContentArea::OnDraw(const NexusSDK::UI::Rectangle& bounds, float scale) {
        ImGui::SetCursorScreenPos(bounds.GetMin());

        ImVec2 padding = ImGui::GetStyle().WindowPadding;
        padding.x += 5.0f;
        padding.y += 5.0f;

        bool isVisible = false;
        {
            NexusSDK::UI::Color bgGuard(ImGuiCol_ChildBg, UI::Theme::BackgroundContent);
            NexusSDK::UI::Style padGuard(ImGuiStyleVar_WindowPadding, padding);
            isVisible = ImGui::BeginChild(m_id.c_str(), GetSize(), true);
        }

        if (isVisible) {
            if (!HeaderTitle.empty()) {
                ImGui::TextColored(UI::Theme::Accent, "%s", HeaderTitle.c_str());
                ImGui::Separator();
                ImGui::Spacing();
            }

            NexusSDK::UI::Color headerGuard(ImGuiCol_Header, UI::Theme::HeaderColor);
            NexusSDK::UI::Color headerHoverGuard(ImGuiCol_HeaderHovered, UI::Theme::AccentHover);
            NexusSDK::UI::Color headerActiveGuard(ImGuiCol_HeaderActive, UI::Theme::Accent);

            ImVec2 scrolledPos = ImGui::GetCursorScreenPos();
            NexusSDK::UI::Rectangle clientBounds;
            clientBounds.X = scrolledPos.x;
            clientBounds.Y = scrolledPos.y;
            clientBounds.Width = GetSize().x;
            clientBounds.Height = GetSize().y;

            NexusSDK::UI::Container::DrawChildren(clientBounds, scale);
        }
        ImGui::EndChild();
    }

    SettingsUI::SettingsUI(const std::filesystem::path& settingsPath, AddonDefinition_t* addonDef)
        : FlowPanel(), m_settingsPath(settingsPath), m_addonDef(addonDef)
    {
        ControlFlowDirection = NexusSDK::UI::FlowDirection::TopToBottom;
        ControlPadding = 0.0f;

        m_mainBody = std::make_shared<NexusSDK::UI::FlowPanel>();
        m_mainBody->ControlFlowDirection = NexusSDK::UI::FlowDirection::LeftToRight;
        m_mainBody->ControlPadding = 0.0f;

        m_contentPanel = std::make_shared<ContentArea>();
        m_footer = std::make_shared<UI::Footer>(m_addonDef);
        
        m_sidebarMenu = std::make_shared<NexusSDK::UI::Menu>();
        m_sidebarMenu->AccentColor = UI::Theme::Accent;
        m_sidebarMenu->TextUnselectedColor = UI::Theme::TextUnselected;
        m_sidebarMenu->BackgroundColor = UI::Theme::BackgroundSidebar;
        m_sidebarMenu->HeaderTitle = m_addonDef->Name;
        m_sidebarMenu->HeaderSubtitle = std::string("by ") + m_addonDef->Author;
        
        m_mainBody->AddChild(m_sidebarMenu);
        m_mainBody->AddChild(m_contentPanel);

        AddChild(m_mainBody);
        AddChild(m_footer);
        
        m_sidebarMenu->AddTab({"General", "General Options", std::make_shared<GeneralSettingsPage>(m_settingsPath), nullptr});
        m_sidebarMenu->AddTab({"Sound", "Sound Options", std::make_shared<AudioSettingsPage>(m_settingsPath), nullptr});
        
        m_sidebarMenu->OnSelectionChanged = [this](int index) {
            m_contentPanel->ClearChildren();
            m_contentPanel->HeaderTitle = m_sidebarMenu->Tabs[index].Title;
            m_contentPanel->AddChild(m_sidebarMenu->Tabs[index].PageControl);
        };

        // Build first tab by default
        if (!m_sidebarMenu->Tabs.empty()) {
            m_sidebarMenu->SelectedIndex = 0;
            m_contentPanel->HeaderTitle = m_sidebarMenu->Tabs[0].Title;
            m_contentPanel->AddChild(m_sidebarMenu->Tabs[0].PageControl);
        }
    }

    void SettingsUI::OnDraw(const NexusSDK::UI::Rectangle& bounds, float scale)
    {
        float footerHeight = ImGui::GetTextLineHeightWithSpacing() + ImGui::GetStyle().ItemSpacing.y * 3.0f + 5.0f;

        float availableWidth = bounds.Width / scale;
        float availableHeight = bounds.Height / scale;

        m_mainBody->SetSize(ImVec2(availableWidth, availableHeight - footerHeight));
        m_sidebarMenu->SetSize(ImVec2(140.0f, availableHeight - footerHeight));
        
        // ControlPadding defaults to 8.0f in FlowPanel. Since mainBody padding is 0.0f, we don't subtract padding.
        m_contentPanel->SetSize(ImVec2(availableWidth - 140.0f, availableHeight - footerHeight));
        m_footer->SetSize(ImVec2(availableWidth, footerHeight));

        NexusSDK::UI::FlowPanel::OnDraw(bounds, scale);
    }
}
