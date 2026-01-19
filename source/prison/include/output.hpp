#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "evaluator.hpp"

class Output {
    public:
        void addToDecisionsHistory(RoundDecisionMatrix roundDecisionMatrix);

        void addToScoreHistory(std::vector<int> scores);
        void saveToFile(std::string scoreHistoryFile, std::string decisionsHistoryFile);
    private:
        std::vector<RoundDecisionMatrix> decisionsHistory;
        std::vector<std::vector<int>> scoreHistory;
};
