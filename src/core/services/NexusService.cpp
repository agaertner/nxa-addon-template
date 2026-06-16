#include "NexusService.h"

Nekres::Services::NexusService::NexusService(AddonAPI_t* p_api) : m_api(p_api)
{
	m_instance = this;
	m_nexus = (NexusLinkData_t*)m_api->DataLink_Get("DL_NEXUS_LINK");
#if __has_include("../submodules/nexus-rtapi/RTAPI.h") || __has_include("../submodules/nexus-rtapi/RTAPI.hpp")
	m_rtdata = (RTAPI::RealTimeData*)m_api->DataLink_Get(DL_RTAPI);
#endif

	m_api->Events_Subscribe(ADDON_LOADED, OnAddonLoaded);
	m_api->Events_Subscribe(ADDON_UNLOADED, OnAddonUnloaded);
}

Nekres::Services::NexusService::~NexusService()
{
	m_instance = nullptr;
	m_api->Events_Unsubscribe(ADDON_LOADED, OnAddonLoaded);
	m_api->Events_Unsubscribe(ADDON_UNLOADED, OnAddonUnloaded);
}

#if __has_include("../submodules/nexus-rtapi/RTAPI.h") || __has_include("../submodules/nexus-rtapi/RTAPI.hpp")
RTAPI::RealTimeData* Nekres::Services::NexusService::Data() const
{
	return m_rtdata;
}
#endif

NexusLinkData_t* Nekres::Services::NexusService::Core() const
{
	return m_nexus;
}