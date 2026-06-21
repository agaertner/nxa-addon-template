#ifndef LOCAL_MANAGER_H
#define LOCAL_MANAGER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <optional>
#include <filesystem>
#include "../../thirdparty/nlohmann/json.hpp"

namespace Nekres {

    class LocalManager {
    public:
        LocalManager(const std::filesystem::path& addonPath);
        ~LocalManager() = default;

        std::string GetString(const std::string& key, std::optional<int> language = std::nullopt);
        std::string GetString(const std::string& key, const std::vector<std::string>& args, std::optional<int> language = std::nullopt);
        std::string GetIsoCode(int langId);

    private:
        void Load(const std::filesystem::path& filePath);
        void CreateDefaultFile(const std::filesystem::path& filePath);

        std::unordered_map<std::string, std::unordered_map<std::string, std::string>> m_strings;
        std::filesystem::path m_filePath;
    };

}

#endif // LOCAL_MANAGER_H
