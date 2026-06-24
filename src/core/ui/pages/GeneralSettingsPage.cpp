#include "GeneralSettingsPage.h"
#include "../../Settings.h"
#include <nexus-imgui/imgui.h>
#include <windows.h>

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
        exampleCombo->OnSelectionChanged = [this](int val) {
            Settings::ExampleDropdownIndex = val;
            Settings::Save(m_settingsPath);
        };
        flowPanel->AddChild(exampleCombo);

        // Spacer
        auto spacer = std::make_shared<NexusSDK::UI::ControlBase>();
        spacer->SetSize(0, 16);
        flowPanel->AddChild(spacer);

        // Example Button
        auto exampleButton = std::make_shared<NexusSDK::UI::Button>("btnExample", "Example Button");
        exampleButton->OnClick = []() {
            auto dialog = NexusSDK::UI::StandardDialog::Show(
                "<size=30><b><c=#00bfff>Example Dialog</c></b></size>\nThis is an <u>example dialog</u> which auto-adjusts to its content. <b>The text will wrap</b> when needed. It uses <s>crazy</s> simple markup for formatting. <stroke>It can even add stroke effect.</stroke> or link to <href=\"https://raidcore.gg/\">Raidcore.gg</href>.",
                NexusSDK::UI::DialogIcon::Exclamation
            );
        };
        flowPanel->AddChild(exampleButton);
    }
}
