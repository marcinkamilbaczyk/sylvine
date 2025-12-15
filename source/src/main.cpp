#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <exception>
#include "config.hpp"

int main(int argc, char* argv[]) {
    std::string configPath = (argc > 1)
        ? argv[1]
        : "data/config/config1.ini";

    std::cout << "Loading config from: " << configPath << std::endl;
    std::cout << "========================================" << std::endl;

    try {
        Config config(configPath);

        // Print basic parameters
        std::cout << "Number of prisoners: " << config.getNumPrisoners() << std::endl;
        std::cout << "Number of rounds: " << config.getNumRounds() << std::endl;
        std::cout << std::endl;

        // Print strategies
        std::cout << "Strategies:" << std::endl;
        for (const auto& [name, percentage] : config.getStrategies()) {
            int count = config.getNumPrisonersForStrategy(name);
            std::cout << "  " << name << ": " << (percentage * 100) << "% ("
                      << count << " prisoners)" << std::endl;
        }
        std::cout << std::endl;

        // Print payoff matrix
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
        std::cout << "Starting game..." << std::endl;

        // Game game(config);
        // game.play();

    } catch (const std::exception& e) {
        std::cerr << "Config error: " << e.what() << std::endl;
        std::cerr << "Program terminated." << std::endl;
        return 1;
    }

    return 0;
}
