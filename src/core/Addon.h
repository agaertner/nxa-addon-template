#ifndef ADDON_H
#define ADDON_H
#include <cmath>
#include <vector>
#include <filesystem>
#include <fstream>
#include <DirectXMath.h>
#include "Settings.h"
#include "Defines.h"
#include "imgui/imgui.h"
#ifdef USE_MUMBLE
#include "services/Gw2MumbleService.h"
#endif
#ifdef USE_RTAPI
#include "services/RealTimeApiService.h"
#endif
#include "services/NexusService.h" 
namespace Nekres {
	class Addon
	{
		const char* ON_ADDON_LOADED = "EV_ADDON_LOADED";
		const char* ON_ADDON_UNLOADED = "EV_ADDON_UNLOADED";

		public:
			Addon(AddonDefinition_t* p_addonDef, AddonAPI_t* p_api);

			~Addon();

#ifdef USE_MUMBLE
			Services::Gw2MumbleService* Gw2Mumble;
#endif
			Services::NexusService* Nexus;
#ifdef USE_RTAPI
			Services::RealTimeApiService* RealTimeApi;
#endif

			static void Log(ELogLevel p_logLevel, const char* p_message) {
				if (m_instance) {
					m_instance->m_api->Log(p_logLevel, m_instance->m_addonDef->Name, p_message);
				}
			}

			void Render();
			void Options();

		private:
			inline static Addon* m_instance = nullptr;

			AddonDefinition_t* m_addonDef;
			AddonAPI_t* m_api;

			std::filesystem::path m_addonPath;
			std::filesystem::path m_settingsPath;

			static void AddonRender() { m_instance->Render(); }
			static void AddonOptions() { m_instance->Options(); }
	};

}
#endif