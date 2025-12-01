#include <string>
#include <vector>
#include <memory>
#include "empty.hpp"

// Moduł config
class Config {};
class Parser {
    public:
        Config parseConfig(std::string configPath);
};

// Output
class Output {

};

// Moduł gry
class Game {
    public:
        Game(Config config);
        Output play();
};

// Moduł strategii
class Strategy {
    public:
        virtual int makeDecision(std::vector<int> gameHistoryWithPlayer) = 0;
};

// Moduł gracza
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


// Ewaluator



int main() { // TODO: dodac argsy
    auto configPath = "";
    auto parser = Parser();
    auto config = parser.parseConfig(configPath); // configPath z argsów
    auto game = Game(config);
    game.play();

}
