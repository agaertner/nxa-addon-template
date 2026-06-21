#ifndef SETTINGSUI_H
#define SETTINGSUI_H

#include <filesystem>
#include <vector>
#include <memory>
#include "../../Defines.h"
#include "pages/ISettingsPage.h"

namespace Nekres {
    class SettingsUI {
    public:
        SettingsUI(const std::filesystem::path& settingsPath, AddonDefinition_t* addonDef);
        ~SettingsUI() = default;
        
        void Draw();

    private:
        void DrawSidebar(float footerHeight);
        void DrawContent(float footerHeight);
        void DrawFooter();
        std::filesystem::path m_settingsPath;
        AddonDefinition_t* m_addonDef;
        std::vector<std::unique_ptr<ISettingsPage>> m_pages;
        int m_selectedTab = 0;
    };
}

#endif // SETTINGSUI_H
