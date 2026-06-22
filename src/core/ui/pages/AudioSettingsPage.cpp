#include "AudioSettingsPage.h"
#include "../../Settings.h"
#include "../../services/Services.h"
#include <imgui/imgui.h>

namespace Nekres {
    AudioSettingsPage::AudioSettingsPage(const std::filesystem::path& settingsPath)
        : Container(), m_settingsPath(settingsPath)
    {
        auto flowPanel = std::make_shared<NexusSDK::UI::FlowPanel>();
        AddChild(flowPanel);

        auto masterVol = std::make_shared<NexusSDK::UI::Slider>("Master Volume:", &Settings::MasterVolume, 0.0f, 1.0f);
        masterVol->SetSize(ImVec2(150, 0));
        masterVol->OnValueChanged = [this](float val) {
            Settings::Save(m_settingsPath);
            if (Services::m_audio) {
                Services::m_audio->SetVolume(Settings::MasterVolume);
            }
        };

        flowPanel->AddChild(masterVol);
    }
}
