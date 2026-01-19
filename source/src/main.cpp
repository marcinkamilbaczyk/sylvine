// main.cpp
#include <string>
#include <iostream>
#include "config_loader.hpp"
#include "config.hpp"
#include "game.hpp" 

// ------------------------------------------------------------------------//
// Moduł config - Ogonowski, Obara
// class Config {};

// Output - Zajko, Dębek, Prędota
// class Game {
//     public:
//         Game(Config config);
//         Output play();
// };

// class Output {

// };

// Moduł strategii - Gustaw, Owczarczuk, Mastej
// class Strategy {
//     public:
//         virtual int makeDecision(std::vector<int> gameHistoryWithPlayer) = 0;
// };

// class AlwaysPositives: public Strategy {
    
// };

// class AlwaysNegatives: public Strategy {

// };

// class RandomDecision: public Strategy {

// };

// Moduł gracza - Sitek, Wasmocki
// class PlayerFactory {
//     Player makePlayer(...) { // TODO: do definiowania jakie parametry

//     }
// };

// class Player {
//     public:
//         Player(int id, std::shared_ptr<Strategy> strategy): id(id), strategy(strategy) {}
//         int getId() { return id; }
    
//     private:
//         int id;
//         std::shared_ptr<Strategy> strategy;
// };


// Ewaluator - Macek, Fidura, Kiciński, 
// class Evaluator {
//     std::vector<int> evaluateScoring(std::vector<std::vector<int>> allPlayersDecisions) {

//     }
// };

// ------------------------------------------------------------------------//


int main(int argc, char* argv[]) {
    std::string configPath = "data/config/config1.ini";
    if (argc > 1) {
        configPath = argv[1];
    }

    ConfigLoader loader(configPath, true);
    auto config = loader.load();
    
    if (!config) return 1;

    auto game = Game(*config);
    auto output = game.play();
    output.saveToFile("scoreHistory.txt", "decisionsHistory.txt");
    // ------------------------------------------------------------------------//
    // DOSTEP DO DANYCH Z CONFIG PRZYKLAD: 
    // ------------------------------------------------------------------------//
    
    // std::cout << "Config values:" << std::endl;
    // std::cout << "Prisoners: " << config->getNumPrisoners() << std::endl;
    // std::cout << "Rounds: " << config->getNumRounds() << std::endl;
    
    // std::cout << "Strategies: ";
    // for (const auto& [name, percentage] : config->getStrategies()) {
    //     std::cout << name << "=" << percentage << " ";
    // }
    // std::cout << std::endl;
    
    // const auto& payoff = config->getPayoffMatrix();
    // std::cout << "Payoff [R,S,T,P]: [" << payoff[0] << "," << payoff[1] 
    //           << "," << payoff[2] << "," << payoff[3] << "]" << std::endl;
    
    // ------------------------------------------------------------------------//
    
    // Game game(*config);
    // game.play();

    return 0;
}
