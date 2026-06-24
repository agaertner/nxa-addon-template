#include "AudioSettingsPage.h"
#include "../../Settings.h"
#include <NexusSDK.h>
#include <nexus-imgui/imgui.h>
#include <chrono>

namespace Nekres {
    AudioSettingsPage::AudioSettingsPage(const std::filesystem::path& settingsPath)
        : Container(), m_settingsPath(settingsPath)
    {
        auto flowPanel = std::make_shared<NexusSDK::UI::FlowPanel>();
        flowPanel->ControlFlowDirection = NexusSDK::UI::FlowDirection::TopToBottom;
        flowPanel->ControlPadding = 2.0f;
        AddChild(flowPanel);

        float maxLabelWidth = 220.0f;

        // Master Volume Slider
        auto masterVol = std::make_shared<NexusSDK::UI::Slider>("Master Volume:", &Settings::MasterVolume, 0.0f, 1.0f);
        masterVol->LabelWidth = maxLabelWidth;
        masterVol->OnValueChanged = [this](float val) {
            Settings::Save(m_settingsPath);
            if (NexusSDK::Audio) {
                NexusSDK::Audio->SetMasterVolume(val);
            }
        };
        flowPanel->AddChild(masterVol);

        // Add extra padding after Master Volume
        auto padding = std::make_shared<NexusSDK::UI::ControlBase>();
        padding->SetSize(0, 16); // Spacer
        flowPanel->AddChild(padding);

        // UI Volume Slider
        auto uiVolSlider = std::make_shared<NexusSDK::UI::Slider>("UI Volume:", &Settings::UIVolume, 0.0f, 1.0f);
        uiVolSlider->LabelWidth = maxLabelWidth;
        uiVolSlider->OnValueChanged = [this](float val) {
            static auto lastClickTime = std::chrono::steady_clock::now() - std::chrono::milliseconds(500);
            Settings::Save(m_settingsPath);
            if (NexusSDK::Audio) {
                NexusSDK::Audio->SetChannelVolume("UI", val);
                
                auto now = std::chrono::steady_clock::now();
                if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastClickTime).count() > 100) {
                    NexusSDK::Audio->Play(IDR_AUDIO_BUTTON_CLICK, "UI");
                    lastClickTime = now;
                }
            }
        };
        flowPanel->AddChild(uiVolSlider);
    }
}
