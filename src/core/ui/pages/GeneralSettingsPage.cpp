#include "GeneralSettingsPage.h"
#include "../../Settings.h"
#include <imgui/imgui.h>

namespace Nekres {
    GeneralSettingsPage::GeneralSettingsPage(const std::filesystem::path& settingsPath)
        : m_settingsPath(settingsPath)
    {
    }

    const char* GeneralSettingsPage::GetName() const
    {
        return "General Settings";
    }

    void GeneralSettingsPage::Render()
    {
        ImGui::Spacing();
        if (ImGui::Checkbox("Enable Example Feature", &Settings::IsExampleEnabled)) {
            Settings::Save(m_settingsPath);
        }

        ImGui::Spacing();
        const char* exampleOptions[] = { "Option A", "Option B", "Option C" };
        if (Settings::ExampleDropdownIndex < 0 || Settings::ExampleDropdownIndex >= 3) Settings::ExampleDropdownIndex = 0;
        
        ImGui::AlignTextToFramePadding();
        ImGui::Text("Example Dropdown:");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(150.0f);
        if (ImGui::BeginCombo("##ExampleDropdown", exampleOptions[Settings::ExampleDropdownIndex])) {
            for (int i = 0; i < 3; i++) {
                bool isSelected = (Settings::ExampleDropdownIndex == i);
                if (ImGui::Selectable(exampleOptions[i], isSelected)) {
                    Settings::ExampleDropdownIndex = i;
                    Settings::Save(m_settingsPath);
                }
                if (isSelected) {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
        ImGui::Spacing();
    }
}
