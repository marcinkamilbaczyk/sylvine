#include <string>
#include <vector>
#include <memory>
#include <map>
#include <fstream>
#include "game.hpp"
#include "config.hpp"

int main() { // TODO: dodac argsy
    auto configPath = "";
    auto parser = Parser();
    auto config = parser.parseConfig(configPath); // configPath z argsów
    auto game = Game(config);
    auto output = game.play();
    output.saveToFile("scoreHistory.txt", "decisionsHistory.txt"); // ścieżka z argsów
    return 0;
}
