#ifndef ISETTINGSPAGE_H
#define ISETTINGSPAGE_H

namespace Nekres {
    class ISettingsPage {
    public:
        virtual ~ISettingsPage() = default;
        virtual const char* GetName() const = 0;
        virtual const char* GetTitle() const = 0;
        virtual void Render() = 0;
    };
}

#endif
