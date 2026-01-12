// config_loader.cpp
#include "config_loader.hpp"
#include <iostream>
#include <exception>

ConfigLoader::ConfigLoader(const std::string& path, bool verbose)
    : config_path(path), verbose(verbose) {}

std::optional<Config> ConfigLoader::load() const {
    try {
        if (verbose) {
            std::cout << "Loading config from: " << config_path << std::endl;
            std::cout << "========================================" << std::endl;
        }

        Config config(config_path);

        if (verbose) {
            std::cout << "Number of prisoners: " << config.getNumPrisoners() << std::endl;
            std::cout << "Number of rounds: " << config.getNumRounds() << std::endl;
            std::cout << std::endl;

            std::cout << "Strategies:" << std::endl;
            for (const auto& [name, percentage] : config.getStrategies()) {
                int count = config.getNumPrisonersForStrategy(name);
                std::cout << "  " << name << ": " << (percentage * 100) << "% ("
                          << count << " prisoners)" << std::endl;
            }
            std::cout << std::endl;

            const auto& payoff = config.getPayoffMatrix();
            std::cout << "Payoff matrix [R, S, T, P]: [";
            for (size_t i = 0; i < payoff.size(); i++) {
                std::cout << payoff[i];
                if (i < payoff.size() - 1) std::cout << ", ";
            }
            std::cout << "]" << std::endl;
            std::cout << "  R (both cooperate): " << payoff[0] << std::endl;
            std::cout << "  S (I cooperate, opponent defects): " << payoff[1] << std::endl;
            std::cout << "  T (I defect, opponent cooperates): " << payoff[2] << std::endl;
            std::cout << "  P (both defect): " << payoff[3] << std::endl;
            std::cout << std::endl;

            std::cout << "========================================" << std::endl;
        }

        return config;

    } catch (const std::exception& e) {
        std::cerr << "Config error: " << e.what() << std::endl;
        std::cerr << "Program terminated." << std::endl;
        return std::nullopt;
    }
}