#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <bits/stdc++.h>
#include "empty.hpp"
#include "strategy.hpp"


/*
// Moduł config - Ogonowski, Obara
class Config {};
class Parser {
    public:
        Config parseConfig(std::string configPath);
};

// Output - Zajko, Dębek, Prędota
class Game {
    public:
        Game(Config config);
        Output play();
};

class Output {

};

*/
// Moduł strategii - Gustaw, Owczarczuk, Mastej

/*
// Moduł gracza - Sitek, Wasmocki
class PlayerFactory {
    Player makePlayer(...) { // TODO: do definiowania jakie parametry

    }
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
    std::vector<int> evaluateScoring(std::vector<std::vector<int>> allPlayersDecisions) {

    }
};


*/
int main() { // TODO: dodac argsy
  std::cout << "Kompiluje" << std::endl;
  auto s = StrategyManager();
  std::cout << "Dalej kompiluje" << std::endl;
  /*
    auto configPath = "";
    auto parser = Parser();
    auto config = parser.parseConfig(configPath); // configPath z argsów
    auto game = Game(config);
    game.play();
  */

}
