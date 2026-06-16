#include "Addon.h"

Nekres::Addon::Addon(AddonDefinition_t* p_addonDef, AddonAPI_t* p_api) : 
#ifdef USE_MUMBLE
Gw2Mumble(new Services::Gw2MumbleService(p_api)), 
#endif
Nexus(new Services::NexusService(p_api)), 
#ifdef USE_RTAPI
RealTimeApi(new Services::RealTimeApiService(p_api)), 
#endif
m_addonDef(p_addonDef), m_api(p_api)
{
	m_instance = this;
	ImGui::SetCurrentContext((ImGuiContext*)m_api->ImguiContext);
	ImGui::SetAllocatorFunctions((void* (*)(size_t, void*))m_api->ImguiMalloc, (void(*)(void*, void*))m_api->ImguiFree); // on imgui 1.80+

	m_addonPath = m_api->Paths_GetAddonDirectory("Nekres/WindowResize");
	m_settingsPath = m_api->Paths_GetAddonDirectory("Nekres/WindowResize/settings.json");
	std::filesystem::create_directory(m_addonPath);
	Settings::Load(m_settingsPath);
	m_api->GUI_Register(ERenderType::RT_Render, AddonRender);
	m_api->GUI_Register(ERenderType::RT_OptionsRender, AddonOptions);
}

Nekres::Addon::~Addon()
{
	m_api->GUI_Deregister(AddonOptions);
	m_api->GUI_Deregister(AddonRender);
#ifdef USE_MUMBLE
	delete Gw2Mumble;
#endif
	delete Nexus;
#ifdef USE_RTAPI
	delete RealTimeApi;
#endif
	delete m_api;
	Settings::Save(m_settingsPath);
	m_instance = nullptr;
}

void Nekres::Addon::Render()
{
}

void Nekres::Addon::Options()
{
}