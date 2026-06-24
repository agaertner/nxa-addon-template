#ifndef GENERALSETTINGSPAGE_H
#define GENERALSETTINGSPAGE_H

#include <NexusSDK.h>
#include <filesystem>

namespace Nekres {
    class GeneralSettingsPage : public NexusSDK::UI::Container {
    public:
        GeneralSettingsPage(const std::filesystem::path& settingsPath);
        virtual ~GeneralSettingsPage() = default;

    private:
        std::filesystem::path m_settingsPath;
    };
}

#endif
