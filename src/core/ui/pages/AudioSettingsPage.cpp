#include "AudioSettingsPage.h"
#include "../../Settings.h"
#include "../../services/Services.h"
#include <imgui/imgui.h>

namespace Nekres {
    AudioSettingsPage::AudioSettingsPage(const std::filesystem::path& settingsPath)
        : m_settingsPath(settingsPath)
    {
    }

    const char* AudioSettingsPage::GetName() const
    {
        return "Sound";
    }

    const char* AudioSettingsPage::GetTitle() const
    {
        return "Sound Options";
    }

    void AudioSettingsPage::Render()
    {
        ImGui::Spacing();
        ImGui::AlignTextToFramePadding();
        ImGui::Text("Master Volume:");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(250.0f);
        if (ImGui::SliderFloat("##MasterVolume", &Settings::MasterVolume, 0.0f, 1.0f, "%.2f")) {
            Settings::Save(m_settingsPath);
            if (Services::m_audio) {
                Services::m_audio->UpdateVolume();
            }
        }
        ImGui::Spacing();
    }
}
