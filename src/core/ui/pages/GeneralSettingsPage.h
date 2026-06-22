#ifndef GENERALSETTINGSPAGE_H
#define GENERALSETTINGSPAGE_H

#include "ISettingsPage.h"
#include <filesystem>

namespace Nekres {
    class GeneralSettingsPage : public ISettingsPage {
    public:
        GeneralSettingsPage(const std::filesystem::path& settingsPath);
        
        const char* GetName() const override;
        const char* GetTitle() const override;
        void Render() override;

    private:
        std::filesystem::path m_settingsPath;
    };
}

#endif
