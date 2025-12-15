#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <map>
#include <string>
#include <vector>
#include <stdexcept>

class Config {
private:
    int num_prisoners;
    int num_rounds;
    std::map<std::string, double> strategies;  // strategy name -> percentage (0.0-1.0)
    std::vector<int> payoff_matrix;  // [R, S, T, P] - 4x1 vector

public:
    // Constructor - loads from YAML file
    Config(const std::string& config_path);

    // Getters
    int getNumPrisoners() const;
    int getNumRounds() const;
    const std::map<std::string, double>& getStrategies() const;
    const std::vector<int>& getPayoffMatrix() const;
    
    int getNumPrisonersForStrategy(const std::string& strategy) const;
};

#endif // CONFIG_HPP