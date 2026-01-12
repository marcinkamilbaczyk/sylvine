#include <vector>
#include <string>
#include <fstream>
#include "evaluator.hpp"

class Output {
    public:
        void addToDecisionsHistory(RoundDecisionMatrix roundDecisionMatrix) {
            decisionsHistory.push_back(roundDecisionMatrix);
        }

        void addToScoreHistory(std::vector<int> scores) {
            scoreHistory.push_back(scores);
        }

        void saveToFile(std::string scoreHistoryFile, std::string decisionsHistoryFile) {
            std::ofstream scoreFile(scoreHistoryFile);
            for (auto scores : scoreHistory) {
                for (auto score : scores) {
                    scoreFile << score << " ";
                }
                scoreFile << "\n";
            }
            scoreFile.close();

            std::ofstream decisionsFile(decisionsHistoryFile);
            for (auto roundDecisionMatrix : decisionsHistory) {
                for (int i = 0; i < roundDecisionMatrix.getNumCols(); i++) {
                    for (int j = 0; j < roundDecisionMatrix.getNumCols(); j++) {
                        decisionsFile << roundDecisionMatrix.getDecision(i, j) << " ";
                    }
                    decisionsFile << "\n";
                }
                decisionsFile << "\n";
            }
            decisionsFile.close();
        }

    private:
        std::vector<RoundDecisionMatrix> decisionsHistory;
        std::vector<std::vector<int>> scoreHistory;
};
