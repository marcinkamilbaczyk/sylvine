// config_loader.hpp
#ifndef CONFIG_LOADER_HPP
#define CONFIG_LOADER_HPP

#include <string>
#include <optional>
#include "config.hpp"

class ConfigLoader {
private:
    std::string config_path;
    bool verbose;

public:
    ConfigLoader(const std::string& path, bool verbose = false);
    std::optional<Config> load() const;
};

#endif // CONFIG_LOADER_HPP