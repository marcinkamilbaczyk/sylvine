#include "config.hpp"
#include <yaml-cpp/yaml.h>
#include <cmath>
#include <iostream>

Config::Config(const std::string& config_path) {
    try {
        YAML::Node config = YAML::LoadFile(config_path);
        
        // Load basic parameters
        num_prisoners = config["num_prisoners"].as<int>();
        num_rounds = config["num_epochs"].as<int>();
        
        // Load strategies
        YAML::Node strategies_node = config["strategies"];
        for (YAML::const_iterator it = strategies_node.begin(); it != strategies_node.end(); ++it) {
            std::string name = it->first.as<std::string>();
            double percentage = it->second.as<double>();
            strategies[name] = percentage;
        }
        
        // Load payoff matrix parameters and create 4x1 vector [R, S, T, P]
        YAML::Node params = config["params"];
        int R = params["R"].as<int>();
        int S = params["S"].as<int>();
        int T = params["T"].as<int>();
        int P = params["P"].as<int>();
        
        payoff_matrix = {R, S, T, P};
        
        // Validation
        if (num_prisoners <= 0) {
            throw std::invalid_argument("Number of prisoners must be positive");
        }
        if (num_rounds <= 0) {
            throw std::invalid_argument("Number of rounds must be positive");
        }
        
        // Check if percentages sum to ~1.0
        double sum = 0.0;
        for (const auto& [name, percentage] : strategies) {
            sum += percentage;
        }
        if (std::abs(sum - 1.0) > 0.01) {
            std::cerr << "Warning: Strategy percentages sum to " << sum << " instead of 1.0" << std::endl;
        }
        
    } catch (const YAML::Exception& e) {
        throw std::runtime_error("Error parsing YAML file: " + std::string(e.what()));
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
    if (it == strategies.end()) {
        return 0;
    }
    return static_cast<int>(std::round(num_prisoners * it->second));
}