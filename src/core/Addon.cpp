#include "Addon.h"
#include <algorithm>
#include <cctype>

Nekres::Addon::Addon(AddonDefinition_t* p_addonDef, AddonAPI_t* p_api) : 
    m_addonDef(p_addonDef), m_api(p_api)
{

    m_instance = this;
    ImGui::SetCurrentContext((ImGuiContext*)m_api->ImguiContext);
    if (m_api->ImguiMalloc && m_api->ImguiFree) {
        ImGui::SetAllocatorFunctions((void* (*)(size_t, void*))m_api->ImguiMalloc, (void(*)(void*, void*))m_api->ImguiFree); // on imgui 1.80+
    }

    std::string folderName = m_addonDef->Name;
    folderName.erase(std::remove_if(folderName.begin(), folderName.end(), ::isspace), folderName.end());

    m_addonPath = m_api->Paths_GetAddonDirectory(folderName.c_str());
    m_settingsPath = m_addonPath / "settings.json";
    std::filesystem::create_directories(m_addonPath);
    Settings::Load(m_settingsPath);

    extern HMODULE hSelf;

    NexusSDK::Initialize(m_api, hSelf, m_addonPath);
    NexusSDK::Audio->SetMasterVolume(Settings::MasterVolume);
    NexusSDK::Audio->SetChannelVolume("UI", Settings::UIVolume);

    m_settingsUI = std::make_unique<SettingsUI>(m_settingsPath, m_addonDef);

    m_api->GUI_Register(ERenderType::RT_Render, AddonRender);
    m_api->GUI_Register(ERenderType::RT_OptionsRender, AddonOptions);
}

Nekres::Addon::~Addon()
{
    m_api->GUI_Deregister(AddonOptions);
    m_api->GUI_Deregister(AddonRender);

    NexusSDK::Shutdown();

    delete m_api;
    Settings::Save(m_settingsPath);
    m_instance = nullptr;
}

void Nekres::Addon::Render()
{
    NexusSDK::Render();
}

void Nekres::Addon::Options()
{
    if (m_settingsUI) {
        NexusSDK::UI::Rectangle bounds;
        bounds.X = ImGui::GetCursorScreenPos().x;
        bounds.Y = ImGui::GetCursorScreenPos().y;
        bounds.Width = ImGui::GetContentRegionAvail().x;
        bounds.Height = ImGui::GetContentRegionAvail().y;

        m_settingsUI->Draw(bounds, 1.0f);
    }
}