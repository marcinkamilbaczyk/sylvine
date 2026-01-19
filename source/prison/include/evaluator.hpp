#ifndef EVALUATOR_HPP
#define EVALUATOR_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "evaluator.hpp"

enum DECISION
{
    COOPERATE = 0,
    DEFECT,
};

class RoundDecisionMatrix
{
public:
    RoundDecisionMatrix(int numPlayers);

    void updateDecision(int i, int j, int decision);
    int getDecision(int i, int j);

private:
    int numCols;
    std::vector<int> decisionFlattenedArray;
};

class ResultsMatrix
{
public:
    ResultsMatrix(int numPlayers);
    void updateResults(int i, int j, int result);

    int getResult(int i, int j);

private:
    int numCols;
    std::vector<int> resultsFlattenedArray;
};

class RulesMatrix
{
public:
    RulesMatrix(std::vector<int> payoff_matrix)
    {
        R = payoff_matrix[0];
        S = payoff_matrix[1];
        T = payoff_matrix[2];
        P = payoff_matrix[3];
    };

    std::vector<int> getResults(int d1, int d2);
    int R, S, T, P;
};

class Evaluator
{
public:
    Evaluator(int payoff_matrix[4]);
    ResultsMatrix evaluateScoring(RoundDecisionMatrix _decisionMatrix, int N);

private:
    std::shared_ptr<RulesMatrix> rulesMatrix;
};

#endif // EVALUATOR_HPP