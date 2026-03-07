#include "NexusService.h"

Nekres::Services::NexusService::NexusService(AddonAPI_t* p_api) : m_api(p_api)
{
	m_instance = this;
	m_nexus = (NexusLinkData_t*)m_api->DataLink_Get("DL_NEXUS_LINK");
	//m_rtdata = (RTAPI::RealTimeData*)m_api->DataLink.Get(DL_RTAPI);

	m_api->Events_Subscribe(ADDON_LOADED, OnAddonLoaded);
	m_api->Events_Subscribe(ADDON_UNLOADED, OnAddonUnloaded);
}

Nekres::Services::NexusService::~NexusService()
{
	m_instance = nullptr;
	m_api->Events_Unsubscribe(ADDON_LOADED, OnAddonLoaded);
	m_api->Events_Unsubscribe(ADDON_UNLOADED, OnAddonUnloaded);
}

/*RTAPI::RealTimeData* Nekres::Services::NexusService::Data() const
{
	return m_rtdata;
}*/

NexusLinkData_t* Nekres::Services::NexusService::Core() const
{
	return m_nexus;
}