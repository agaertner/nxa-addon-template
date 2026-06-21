#include "Addon.h"
#include <algorithm>
#include <cctype>

Nekres::Addon::Addon(AddonDefinition_t* p_addonDef, AddonAPI_t* p_api) : 
    m_addonDef(p_addonDef), m_api(p_api)
{
#ifdef USE_MUMBLE
    Services::Mumble(p_api);
#endif
    Services::Nexus(p_api);
#ifdef USE_RTAPI
    Services::RTAPI(p_api);
#endif

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

    Services::m_audio = new AudioManager(m_api);
    Services::Local(m_addonPath);

    m_settingsUI = std::make_unique<SettingsUI>(m_settingsPath, m_addonDef);

    m_api->GUI_Register(ERenderType::RT_Render, AddonRender);
    m_api->GUI_Register(ERenderType::RT_OptionsRender, AddonOptions);
}

Nekres::Addon::~Addon()
{
    m_api->GUI_Deregister(AddonOptions);
    m_api->GUI_Deregister(AddonRender);
#ifdef USE_MUMBLE
    delete Services::m_mumble;
    Services::m_mumble = nullptr;
#endif
    delete Services::m_nexus;
    Services::m_nexus = nullptr;
#ifdef USE_RTAPI
    delete Services::m_rtapi;
    Services::m_rtapi = nullptr;
#endif

    delete Services::m_audio;
    Services::m_audio = nullptr;

    delete Services::m_localManager;
    Services::m_localManager = nullptr;

    delete m_api;
    Settings::Save(m_settingsPath);
    m_instance = nullptr;
}

void Nekres::Addon::Render()
{
}

void Nekres::Addon::Options()
{
    if (m_settingsUI) {
        m_settingsUI->Draw();
    }
}