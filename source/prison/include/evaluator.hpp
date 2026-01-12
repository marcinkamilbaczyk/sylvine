#ifndef EVALUATOR_HPP
#define EVALUATOR_HPP
#include <vector>

class RoundDecisionMatrix {
    public:
        RoundDecisionMatrix(int numPlayers) {
            numCols = numPlayers;
            decisionFlattenedArray = std::vector<int>(numPlayers*numPlayers);
        }

        void updateDecision(int i, int j, int decision) {
            decisionFlattenedArray.at(numCols*i + j) = decision;
        }

        int getDecision(int i, int j) {
            return decisionFlattenedArray.at(numCols*i + j);
        }

        int getNumCols() {
            return numCols;
        }

    private:
        int numCols;
        std::vector<int> decisionFlattenedArray;
};

class Evaluator {
    public:
        std::vector<int> evaluateScoring(RoundDecisionMatrix roundDecisionMatrix);
};


#endif