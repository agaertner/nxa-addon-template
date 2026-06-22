#ifndef SETTINGSUI_H
#define SETTINGSUI_H

#include <filesystem>
#include <vector>
#include <memory>
#include "../../Defines.h"
#include <lib-nxa-sdk/NexusSDK.h>
#include "Footer.h"

namespace Nekres {

    class ContentArea : public NexusSDK::UI::Container {
    public:
        ContentArea() : NexusSDK::UI::Container() {}
        virtual ~ContentArea() = default;
        std::string HeaderTitle;
    protected:
        virtual void OnRender() override;
    };

    class SettingsUI : public NexusSDK::UI::FlowPanel {
    public:
        SettingsUI(const std::filesystem::path& settingsPath, AddonDefinition_t* addonDef);
        virtual ~SettingsUI() = default;
    protected:
        virtual void OnRender() override;

    private:
        std::filesystem::path m_settingsPath;
        AddonDefinition_t* m_addonDef;

        std::shared_ptr<ContentArea> m_contentPanel;
        std::shared_ptr<UI::Footer> m_footer;
        std::shared_ptr<NexusSDK::UI::Menu> m_sidebarMenu;
        std::shared_ptr<NexusSDK::UI::FlowPanel> m_mainBody;
    };
}

#endif // SETTINGSUI_H
