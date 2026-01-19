#include <vector>
#include <string>
#include <fstream>
#include "evaluator.hpp"
#include "output.hpp"

        void Output::addToDecisionsHistory(RoundDecisionMatrix roundDecisionMatrix) {
            decisionsHistory.push_back(roundDecisionMatrix);
        }

        void Output::addToScoreHistory(std::vector<int> scores) {
            scoreHistory.push_back(scores);
        }

        void Output::saveToFile(std::string scoreHistoryFile, std::string decisionsHistoryFile) {
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
