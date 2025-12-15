#include <string>
#include <vector>
#include <memory>
#include <bits/stdc++.h>
#include "empty.hpp"


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
class Strategy {
public:
  Strategy(){}
  virtual int makeDecision(std::vector<int> gameHistoryWithPlayer) = 0;
  virtual ~Strategy() = default;
};

class AlwaysPositives: public Strategy {
public:
  int makeDecision(std::vector<int> gameHistoryWithPlayer){
    return 1;
  }
    
};

class AlwaysNegatives: public Strategy {
public:
  int makeDecision(std::vector<int> gameHistoryWithPlayer){
    return 0;
  }
};

class RandomDecision: public Strategy {
public:
  RandomDecision(){
    std::srand(std::time(0));
  }
  int makeDecision(std::vector<int> gameHistoryWithPlayer){
    return std::rand()%2;
  }  
  
};

class StrategyManager {
public:
  StrategyManager(){
    look_up_strategy["AlwaysPositives"] = std::make_unique<AlwaysPositives>();
    look_up_strategy["AlwaysNegatives"] = std::make_unique<AlwaysNegatives>();
    look_up_strategy["RandomDecision"] = std::make_unique<RandomDecision>();
  }

  int Execute(std::string strategy_name, std::vector<int> playerHistory, std::vector<int> gameHistoryWithPlayer)
  {
    return -1;
  }
private:
  std::map<std::string, std::unique_ptr<Strategy>> look_up_strategy;
};
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
  /*
    auto configPath = "";
    auto parser = Parser();
    auto config = parser.parseConfig(configPath); // configPath z argsów
    auto game = Game(config);
    game.play();
  */

}
