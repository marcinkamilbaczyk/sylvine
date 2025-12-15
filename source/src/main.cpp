#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "../include/config.hpp"

class Game {
public:
    Game(const Config& config) {}
    void play() {}
};

class Output {};

class Strategy {
public:
    virtual int makeDecision(std::vector<int> gameHistoryWithPlayer) = 0;
    virtual ~Strategy() = default;
};

class AlwaysPositives: public Strategy {
public:
    int makeDecision(std::vector<int> gameHistoryWithPlayer) override { return 0; }
};

class AlwaysNegatives: public Strategy {
public:
    int makeDecision(std::vector<int> gameHistoryWithPlayer) override { return 0; }
};

class RandomDecision: public Strategy {
public:
    int makeDecision(std::vector<int> gameHistoryWithPlayer) override { return 0; }
};

class PlayerFactory {};

class Player {
public:
    Player(int id, std::shared_ptr<Strategy> strategy): id(id), strategy(strategy) {}
    int getId() { return id; }
private:
    int id;
    std::shared_ptr<Strategy> strategy;
};

class Evaluator {};

int main(int argc, char* argv[]) {
    std::string configPath = (argc > 1) ? argv[1] : "data/config/config1.yaml";
    std::cout << "Using config file: " << configPath << std::endl;
    Config config(configPath);
    Game game(config);
    game.play();
    
    return 0;
}