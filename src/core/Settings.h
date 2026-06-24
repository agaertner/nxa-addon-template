#ifndef SETTINGS_H
#define SETTINGS_H

#include <mutex>

#include "thirdparty/nlohmann/json.hpp"
using json = nlohmann::json;

extern const char* IS_EXAMPLE_ENABLED;
extern const char* EXAMPLE_DROPDOWN_INDEX;
extern const char* MASTER_VOLUME;
extern const char* UI_VOLUME;

namespace Settings
{
    extern std::mutex    Mutex;
    extern json            Settings;

    /* Loads the settings. */
    void Load(std::filesystem::path aPath);
    /* Saves the settings. */
    void Save(std::filesystem::path aPath);

    // ========================================================================
    // SETTINGS ACCESSIBILITY
    // ========================================================================
    // These variables are globally accessible across the addon's code.
    // Include "Settings.h" anywhere and access them via Settings::IsExampleEnabled.
    extern bool IsExampleEnabled;
    extern int ExampleDropdownIndex;
    extern float MasterVolume;
    extern float UIVolume;
}

#endif