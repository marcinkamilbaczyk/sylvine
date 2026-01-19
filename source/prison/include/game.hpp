#pragma once
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
        std::vector<Player> createPlayers();
        RoundDecisionMatrix playRound(std::vector<Player>& players);
        void updatePointsAndScoreBoard(std::vector<Player>& players, RoundDecisionMatrix& roundDecisionMatrix, Output& output, Evaluator& evaluator);
        void updatePlayersMemory(std::vector<Player>& players, RoundDecisionMatrix& roundDecisionMatrix);

    private:
        size_t numRounds;
        std::map<std::string, int> playersStrategyMap;
        int scoringMatrix[2][2];
};
