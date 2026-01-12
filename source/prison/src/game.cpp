#include <vector>
#include <map>
#include <fstream>
#include "config.hpp"
#include "evaluator.hpp"
#include "player.hpp"
#include "output.hpp"

// Game - Zajko, Dębek, Prędota
class Game {
    private:
        Game(Config config) {
            // TODO: kiedyś powstanie
        }
        std::vector<Player> createPlayers() {
            auto players = std::vector<Player>();
            auto playerFactory = PlayerFactory();
            for (auto pair: playersStrategyMap) {
                for (int i = 0; i < pair.second; i++) {
                    players.push_back(playerFactory.makePlayer(pair.first));
                }
            }
            return players;
        }
        RoundDecisionMatrix playRound(std::vector<Player>& players) {
            auto roundDecisionMatrix = RoundDecisionMatrix(players.size());
            for (size_t i = 0; i < players.size(); i++) {
                for (size_t j = 0; j < players.size(); j++) {
                    if (i == j) continue;
                    roundDecisionMatrix.updateDecision(i, j, players.at(i).makeDecision(j));
                }
            }
            return roundDecisionMatrix;
        }
        void updatePointsAndScoreBoard(std::vector<Player>& players, RoundDecisionMatrix& roundDecisionMatrix, Output& output, Evaluator& evaluator) {
            auto pointsIncrements = evaluator.evaluateScoring(roundDecisionMatrix);
            auto scoreBoard = std::vector<int>();
            for (size_t i = 0; i < players.size(); i++) {
                players.at(i).updatePoints(pointsIncrements.at(i));
                scoreBoard.push_back(players.at(i).getPoints());
            }
            output.addToScoreHistory(scoreBoard);
            output.addToDecisionsHistory(roundDecisionMatrix);
        }
        void updatePlayersMemory(std::vector<Player>& players, RoundDecisionMatrix& roundDecisionMatrix) {
            for (size_t i = 0; i < players.size(); i++) {
                for (size_t j = 0; j < players.size(); j++) {
                    if (i == j) continue;
                    players.at(i).updateMemory(j, roundDecisionMatrix.getDecision(j, i));
                }
            }
        }
    public:
        Output play() {
            // Utwórz graczy
            auto players = createPlayers();
            // Zagraj gre
            auto output = Output();
            auto evaluator = Evaluator();
            for (size_t i = 0; i < numRounds; i++) {
                auto roundDecisionMatrix = playRound(players);
                // Policz punkty dla każdego gracza
                updatePointsAndScoreBoard(players, roundDecisionMatrix, output, evaluator);

                // Zupdatuj pamięć graczy o decyzjach przeciwników
                updatePlayersMemory(players, roundDecisionMatrix);
            }
            return output;
        }
    
    private:
        size_t numRounds;
        std::map<std::string, int> playersStrategyMap;
        int scoringMatrix[2][2];
};
