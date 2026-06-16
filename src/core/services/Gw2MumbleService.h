#ifndef GW2MUMBLESERVICE_H
#define GW2MUMBLESERVICE_H
#include "nexus-core/Nexus.h"
#if __has_include("../submodules/nexus-mumble/Mumble.h")
#include "nexus-mumble/Mumble.h"
namespace Nekres::Services
{
	class Gw2MumbleService
	{
		const char* MUMBLE_IDENTITY_UPDATED = "EV_MUMBLE_IDENTITY_UPDATED";
		public:
			Gw2MumbleService(AddonAPI_t* p_api);
			~Gw2MumbleService();

			Mumble::Data* Data() const;
			Mumble::Identity* Identity() const;

		private:
			inline static Gw2MumbleService* m_instance = nullptr;

			AddonAPI_t* m_api;
			Mumble::Data* m_link;
			Mumble::Identity* m_identity;

			static void OnMumbleIdentityUpdated(void* aEventArgs)
			{
				if (m_instance)
				{
					m_instance->m_identity = (Mumble::Identity*)aEventArgs;
				}
			}
	};

}
#endif
#endif
