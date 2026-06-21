#ifndef AUDIOSETTINGSPAGE_H
#define AUDIOSETTINGSPAGE_H

#include "ISettingsPage.h"
#include <filesystem>

namespace Nekres {
    class AudioSettingsPage : public ISettingsPage {
    public:
        AudioSettingsPage(const std::filesystem::path& settingsPath);
        
        const char* GetName() const override;
        void Render() override;

    private:
        std::filesystem::path m_settingsPath;
    };
}

#endif
