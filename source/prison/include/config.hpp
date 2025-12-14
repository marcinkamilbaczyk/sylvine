#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

class Config {};
class Parser {
    public:
        Config parseConfig(std::string configPath);
};

#endif