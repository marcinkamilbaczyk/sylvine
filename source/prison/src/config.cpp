#include "config.hpp"

#include <cmath>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

namespace {

static inline void ltrim(std::string& s) {
    size_t i = 0;
    while (i < s.size() && std::isspace(static_cast<unsigned char>(s[i]))) ++i;
    s.erase(0, i);
}

static inline void rtrim(std::string& s) {
    if (s.empty()) return;
    size_t i = s.size();
    while (i > 0 && std::isspace(static_cast<unsigned char>(s[i - 1]))) --i;
    s.erase(i);
}

static inline std::string trim_copy(std::string s) {
    ltrim(s);
    rtrim(s);
    return s;
}

static inline void strip_inline_comment(std::string& s) {
    // Treat '#' or ';' as comment start.
    // This is simple and consistent with typical INI usage.
    const auto p1 = s.find('#');
    const auto p2 = s.find(';');
    size_t p = std::string::npos;
    if (p1 != std::string::npos) p = p1;
    if (p2 != std::string::npos) p = (p == std::string::npos) ? p2 : std::min(p, p2);
    if (p != std::string::npos) s.erase(p);
}

using SectionMap = std::unordered_map<std::string, std::unordered_map<std::string, std::string>>;

SectionMap parse_ini(const std::string& path) {
    std::ifstream in(path);
    if (!in) {
        throw std::runtime_error("Cannot open config file: " + path);
    }

    SectionMap data;
    std::string current_section = "main"; // default section if none specified
    std::string line;

    while (std::getline(in, line)) {
        // Remove inline comments then trim
        strip_inline_comment(line);
        line = trim_copy(line);
        if (line.empty()) continue;

        // Section header: [section]
        if (line.size() >= 3 && line.front() == '[' && line.back() == ']') {
            current_section = trim_copy(line.substr(1, line.size() - 2));
            if (current_section.empty()) {
                throw std::runtime_error("Empty INI section name in: " + path);
            }
            continue;
        }

        // key=value
        const auto eq = line.find('=');
        if (eq == std::string::npos) {
            throw std::runtime_error("Invalid INI line (missing '='): " + line);
        }

        std::string key = trim_copy(line.substr(0, eq));
        std::string val = trim_copy(line.substr(eq + 1));
        if (key.empty()) {
            throw std::runtime_error("Invalid INI line (empty key): " + line);
        }

        data[current_section][key] = val;
    }

    return data;
}

int as_int(const std::string& s, const std::string& what) {
    try {
        size_t idx = 0;
        int v = std::stoi(s, &idx);
        if (idx != s.size()) throw std::invalid_argument("trailing");
        return v;
    } catch (...) {
        throw std::runtime_error("Invalid integer for " + what + ": '" + s + "'");
    }
}

double as_double(const std::string& s, const std::string& what) {
    try {
        size_t idx = 0;
        double v = std::stod(s, &idx);
        if (idx != s.size()) throw std::invalid_argument("trailing");
        return v;
    } catch (...) {
        throw std::runtime_error("Invalid double for " + what + ": '" + s + "'");
    }
}

const std::string& require_key(const SectionMap& ini, const std::string& sec, const std::string& key) {
    auto sit = ini.find(sec);
    if (sit == ini.end()) {
        throw std::runtime_error("Missing INI section: [" + sec + "]");
    }
    auto kit = sit->second.find(key);
    if (kit == sit->second.end()) {
        throw std::runtime_error("Missing INI key: [" + sec + "] " + key);
    }
    return kit->second;
}

} // namespace

Config::Config(const std::string& config_path) {
    auto ini = parse_ini(config_path);

    // Load basic parameters (same names as YAML)
    num_prisoners = as_int(require_key(ini, "main", "num_prisoners"), "num_prisoners");
    num_rounds    = as_int(require_key(ini, "main", "num_epochs"), "num_epochs");

    // Load strategies from [strategies]
    {
        auto sit = ini.find("strategies");
        if (sit == ini.end()) {
            throw std::runtime_error("Missing INI section: [strategies]");
        }
        for (const auto& kv : sit->second) {
            const std::string& name = kv.first;
            const std::string& val  = kv.second;
            strategies[name] = as_double(val, "strategies." + name);
        }
    }

    // Load payoff matrix from [payoff] and create [R,S,T,P]
    int R = as_int(require_key(ini, "payoff", "R"), "payoff.R");
    int S = as_int(require_key(ini, "payoff", "S"), "payoff.S");
    int T = as_int(require_key(ini, "payoff", "T"), "payoff.T");
    int P = as_int(require_key(ini, "payoff", "P"), "payoff.P");

    payoff_matrix = {R, S, T, P};

    // Validation (same as before)
    if (num_prisoners <= 0) {
        throw std::invalid_argument("Number of prisoners must be positive");
    }
    if (num_rounds <= 0) {
        throw std::invalid_argument("Number of rounds must be positive");
    }

    // Check if percentages sum to ~1.0 (same warning behavior)
    double sum = 0.0;
    for (const auto& [name, percentage] : strategies) {
        (void)name;
        sum += percentage;
    }
    if (std::abs(sum - 1.0) > 0.01) {
        std::cerr << "Warning: Strategy percentages sum to " << sum << " instead of 1.0" << std::endl;
    }
}

int Config::getNumPrisoners() const {
    return num_prisoners;
}

int Config::getNumRounds() const {
    return num_rounds;
}

const std::map<std::string, double>& Config::getStrategies() const {
    return strategies;
}

const std::vector<int>& Config::getPayoffMatrix() const {
    return payoff_matrix;
}

int Config::getNumPrisonersForStrategy(const std::string& strategy) const {
    auto it = strategies.find(strategy);
    if (it == strategies.end()) return 0;
    return static_cast<int>(std::round(num_prisoners * it->second));
}
