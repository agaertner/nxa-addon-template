#include "GeneralSettingsPage.h"
#include "../../Settings.h"
#include <imgui/imgui.h>

namespace Nekres {
    GeneralSettingsPage::GeneralSettingsPage(const std::filesystem::path& settingsPath)
        : Container(), m_settingsPath(settingsPath)
    {
        auto flowPanel = std::make_shared<NexusSDK::UI::FlowPanel>();
        AddChild(flowPanel);

        // Checkbox
        auto exampleCheck = std::make_shared<NexusSDK::UI::Checkbox>("Example Feature:", &Settings::IsExampleEnabled);
        exampleCheck->OnCheckedChanged = [this](bool val) {
            Settings::Save(m_settingsPath);
        };
        flowPanel->AddChild(exampleCheck);

        // Dropdown
        if (Settings::ExampleDropdownIndex < 0 || Settings::ExampleDropdownIndex >= 3) Settings::ExampleDropdownIndex = 0;
        std::vector<std::string> options = { "Option A", "Option B", "Option C" };
        
        auto exampleCombo = std::make_shared<NexusSDK::UI::Dropdown>("exampleDropdown1", &Settings::ExampleDropdownIndex, options, "Example Dropdown:");
        exampleCombo->SetSize(ImVec2(120, 0));
        exampleCombo->OnSelectionChanged = [this](int val) {
            Settings::ExampleDropdownIndex = val;
            Settings::Save(m_settingsPath);
        };
        flowPanel->AddChild(exampleCombo);
    }
}
