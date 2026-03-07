#ifndef NEXUSSERVICE_H
#define NEXUSSERVICE_H
//#include <nexus-rtapi/RTAPI.hpp>
#include "nexus-core/Nexus.h"
namespace Nekres::Services
{
	class NexusService
	{
		const char* ADDON_LOADED = "EV_ADDON_LOADED";
		const char* ADDON_UNLOADED = "EV_ADDON_UNLOADED";
		public:
			NexusService(AddonAPI_t* p_api);

			~NexusService();

			//RTAPI::RealTimeData* Data() const;

			NexusLinkData_t* Core() const;

		private:
			inline static NexusService* m_instance = nullptr;

			AddonAPI_t* m_api;
			NexusLinkData_t* m_nexus;
			//RTAPI::RealTimeData* m_rtdata;

			static void OnAddonLoaded(void* aSignature)
			{
				if (m_instance)
				{
					int* sig = static_cast<int*>(aSignature);
					if (!sig) { return; }
					
					// Initialize real time API.
					//if (*sig == RTAPI_SIG) m_instance->m_rtdata = (RTAPI::RealTimeData*)m_instance->m_api->DataLink_Get(DL_RTAPI);
				}
			}

			static void OnAddonUnloaded(void* aSignature)
			{
				if (m_instance)
				{
					int* sig = static_cast<int*>(aSignature);
					if (!sig) { return; }

					// Unset real time API.
					//if (*sig == RTAPI_SIG) m_instance->m_rtdata = nullptr;
				}
			}
	};
}
#endif
