#include <vector>
#include <map>
#include <fstream>
#include "config.hpp"
#include "player.hpp"
#include "evaluator.hpp"
#include "output.hpp"

class Game {
    public:
        Game(Config config);
        Output play();
};
