#include "config.hpp"

Config::Config(int epochs, 
               const std::map<std::string, int>& strategy_counts,
               const std::vector<int>& payoff_matrix)
    : epochs(epochs), strategy_counts(strategy_counts), payoff_matrix(payoff_matrix) {
    
    if (epochs <= 0) {
        throw std::invalid_argument("Number of epochs must be positive");
    }
    
    for (const auto& [strategy, count] : strategy_counts) {
        if (count < 0) {
            throw std::invalid_argument("Strategy count cannot be negative for strategy: " + strategy);
        }
    }
    
    if (payoff_matrix.size() != 4) {
        throw std::invalid_argument("Payoff matrix must have exactly 4 elements");
    }
}

int Config::getEpochs() const {
    return epochs;
}

const std::map<std::string, int>& Config::getStrategyCounts() const {
    return strategy_counts;
}

int Config::getStrategyCount(const std::string& strategy) const {
    auto it = strategy_counts.find(strategy);
    return (it != strategy_counts.end()) ? it->second : 0;
}

int Config::getTotalPlayers() const {
    int total = 0;
    for (const auto& [strategy, count] : strategy_counts) {
        total += count;
    }
    return total;
}

const std::vector<int>& Config::getPayoffMatrix() const {
    return payoff_matrix;
}

int Config::getPayoff(int index) const {
    if (index < 0 || index >= 4) {
        throw std::out_of_range("Payoff index must be between 0 and 3");
    }
    return payoff_matrix[index];
}