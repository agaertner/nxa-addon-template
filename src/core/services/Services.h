#ifndef SERVICES_H
#define SERVICES_H

#include "../../Defines.h"

#ifdef USE_MUMBLE
#include "Gw2MumbleService.h"
#endif

#ifdef USE_RTAPI
#include "RealTimeApiService.h"
#endif

#include "NexusService.h"

#include <lib-nxa-sdk/NexusSDK.h>

namespace Nekres::Services
{
#ifdef USE_MUMBLE
    inline Gw2MumbleService* m_mumble = nullptr;
    inline Gw2MumbleService* Mumble(AddonAPI_t* api = nullptr)
    {
        if (!m_mumble && api)
            m_mumble = new Gw2MumbleService(api);
        return m_mumble;
    }
#endif

#ifdef USE_RTAPI
    inline RealTimeApiService* m_rtapi = nullptr;
    inline RealTimeApiService* RTAPI(AddonAPI_t* api = nullptr)
    {
        if (!m_rtapi && api)
            m_rtapi = new RealTimeApiService(api);
        return m_rtapi;
    }
#endif

    inline NexusService* m_nexus = nullptr;
    inline NexusService* Nexus(AddonAPI_t* api = nullptr)
    {
        if (!m_nexus && api)
            m_nexus = new NexusService(api);
        return m_nexus;
    }

    inline NexusSDK::AudioManager* m_audio = nullptr;
    inline NexusSDK::AudioManager* Audio(AddonAPI_t* api = nullptr)
    {
        if (!m_audio && api)
            m_audio = new NexusSDK::AudioManager(api);
        return m_audio;
    }

    inline NexusSDK::LocalManager* m_localManager = nullptr;
    inline NexusSDK::LocalManager* Local(const std::filesystem::path& addonPath = "", AddonAPI_t* api = nullptr)
    {
        if (!m_localManager && !addonPath.empty())
            m_localManager = new NexusSDK::LocalManager(addonPath, api);
        return m_localManager;
    }
}

#endif
