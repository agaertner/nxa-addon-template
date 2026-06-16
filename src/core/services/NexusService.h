#ifndef NEXUSSERVICE_H
#define NEXUSSERVICE_H
#if __has_include("../submodules/nexus-rtapi/RTAPI.h")
#include "nexus-rtapi/RTAPI.h"
#elif __has_include("../submodules/nexus-rtapi/RTAPI.hpp")
#include "nexus-rtapi/RTAPI.hpp"
#endif
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

#if __has_include("../submodules/nexus-rtapi/RTAPI.h") || __has_include("../submodules/nexus-rtapi/RTAPI.hpp")
			RTAPI::RealTimeData* Data() const;
#endif

			NexusLinkData_t* Core() const;

		private:
			inline static NexusService* m_instance = nullptr;

			AddonAPI_t* m_api;
			NexusLinkData_t* m_nexus;
#if __has_include("../submodules/nexus-rtapi/RTAPI.h") || __has_include("../submodules/nexus-rtapi/RTAPI.hpp")
			RTAPI::RealTimeData* m_rtdata;
#endif

			static void OnAddonLoaded(void* aSignature)
			{
				if (m_instance)
				{
					int* sig = static_cast<int*>(aSignature);
					if (!sig) { return; }
					
					// Initialize real time API.
#if __has_include("../submodules/nexus-rtapi/RTAPI.h") || __has_include("../submodules/nexus-rtapi/RTAPI.hpp")
					if (*sig == RTAPI_SIG) m_instance->m_rtdata = (RTAPI::RealTimeData*)m_instance->m_api->DataLink_Get(DL_RTAPI);
#endif
				}
			}

			static void OnAddonUnloaded(void* aSignature)
			{
				if (m_instance)
				{
					int* sig = static_cast<int*>(aSignature);
					if (!sig) { return; }

					// Unset real time API.
#if __has_include("../submodules/nexus-rtapi/RTAPI.h") || __has_include("../submodules/nexus-rtapi/RTAPI.hpp")
					if (*sig == RTAPI_SIG) m_instance->m_rtdata = nullptr;
#endif
				}
			}
	};
}
#endif
