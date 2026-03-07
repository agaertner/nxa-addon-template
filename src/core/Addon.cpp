#include "Addon.h"

Nekres::Addon::Addon(AddonDefinition_t* p_addonDef, AddonAPI_t* p_api) : Gw2Mumble(new Services::Gw2MumbleService(p_api)), Nexus(new Services::NexusService(p_api)), m_addonDef(p_addonDef), m_api(p_api)
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
	delete Gw2Mumble;
	delete Nexus;
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