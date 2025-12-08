#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "empty.hpp"

// Moduł config - Ogonowski, Obara
class Config {};

class Parser {
public:
    Config parseConfig(std::string configPath) {
        // TODO: implementacja
        return Config();
    }
};


// Output - Zajko, Dębek, Prędota
class Game {
public:
    Game(Config config) {
        // TODO: implementacja
    }
    
    void play() {
        // TODO: implementacja
    }
};

class Output {

};

// Moduł strategii - Gustaw, Owczarczuk, Mastej
class Strategy {
    public:
        virtual int makeDecision(std::vector<int> gameHistoryWithPlayer) = 0;
};

class AlwaysPositives: public Strategy {
    
};

class AlwaysNegatives: public Strategy {

};

class RandomDecision: public Strategy {

};

// Moduł gracza - Sitek, Wasmocki
class PlayerFactory {
    // Player makePlayer(...) { // TODO: do definiowania jakie parametry

    // }
};

class Player {
    public:
        Player(int id, std::shared_ptr<Strategy> strategy): id(id), strategy(strategy) {}
        int getId() { return id; }
    
    private:
        int id;
        std::shared_ptr<Strategy> strategy;
};


// Ewaluator - Macek, Fidura, Kiciński, 
class Evaluator {
    // std::vector<int> evaluateScoring(std::vector<std::vector<int>> allPlayersDecisions) {

    // }
};



int main() { // TODO: dodac argsy
    std::cout << "Sylvine Simulation Started" << std::endl;
    auto configPath = "";
    auto parser = Parser();
    auto config = parser.parseConfig(configPath); // configPath z argsów
    auto game = Game(config);

    game.play();

}



#include <string>
#include <vector>
#include <memory>
#include "empty.hpp"

