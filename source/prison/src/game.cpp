#include <vector>
#include <map>
#include <fstream>
#include "config.hpp"
#include "evaluator.hpp"
#include "player.hpp"
#include "output.hpp"

// Game - Zajko, Dębek, Prędota
class Game {
    public:
        Game(Config config) {
            // TODO: kiedyś powstanie
        }

        Output play() {
            // Utwórz graczy
            auto players = std::vector<Player>();
            auto playerFactory = PlayerFactory();
            for (auto pair: playersStrategyMap) {
                for (int i = 0; i < pair.second; i++) {
                    players.push_back(playerFactory.makePlayer(pair.first));
                }
            }
            // Zagraj gre
            auto evaluator = Evaluator();
            for (size_t i = 0; i < numRounds; i++) {
                auto roundDecisionMatrix = RoundDecisionMatrix(players.size());
                for (size_t j = 0; j < players.size(); j++) {
                    if (i == j) continue;
                    roundDecisionMatrix.updateDecision(i, j, players.at(i).makeDecision(j));
                }
                // Policz punkty dla każdego gracza
                auto pointsIncrements = evaluator.evaluateScoring(roundDecisionMatrix);
                for (size_t j = 0; j < players.size(); j++) {
                    players.at(j).updatePoints(pointsIncrements.at(j));
                }
                // Zupdatuj pamięć graczy o decyzjach przeciwników
                for (size_t j = 0; j < players.size(); j++) {
                    for (size_t k = 0; k < players.size(); k++) {
                        if (j == k) continue;
                        players.at(j).updateMemory(k, roundDecisionMatrix.getDecision(k, j));
                    }
                }
            }
            return Output();
        }
    
    private:
        size_t numRounds;
        std::map<std::string, int> playersStrategyMap;
        int scoringMatrix[2][2];
};
