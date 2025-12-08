#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <map>
#include <string>
#include <vector>
#include <stdexcept>

class Config {
private:
    int epochs;
    std::map<std::string, int> strategy_counts;
    std::vector<std::vector<int>> payoff_matrix v(2, std::vector<int>(2,0));  // [[R, S], [T, P]]

public:
    // Konstruktor
    Config(int epochs, 
           const std::map<std::string, int>& strategy_counts,
           const std::vector<std::vector<int>>& payoff_matrix);

    // Gettery
    int getEpochs() const;
    
    const std::map<std::string, int>& getStrategyCounts() const;
    
    int getStrategyCount(const std::string& strategy) const;
    
    int getTotalPlayers() const;
    
    const std::vector<std::vector<int>>& getPayoffMatrix() const;
    
    // Pomocnicze gettery dla konkretnych wypłat
    int getPayoff(int index) const;  // index 0-3
};

#endif // CONFIG_HPP