//
// Created by adrian on 8.12.2025.
//
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "evaluator.hpp"


RoundDecisionMatrix::RoundDecisionMatrix(int numPlayers) 
{
            numCols = numPlayers;
            decisionFlattenedArray = std::vector<int>(numPlayers*numPlayers);
    }

void RoundDecisionMatrix::updateDecision(int i, int j, int decision) 
{
            decisionFlattenedArray.at(numCols*i + j) = decision;
    }

int RoundDecisionMatrix::getDecision(int i, int j) 
{
            return decisionFlattenedArray.at(numCols*i + j);
        }

//////////////////////////////////////////////////////////////////////////////////////

ResultsMatrix::ResultsMatrix(int numPlayers) {
    numCols = numPlayers;
    resultsFlattenedArray = std::vector<int>(numPlayers*numPlayers);
}
void ResultsMatrix::updateResults(int i, int j, int result) {
    resultsFlattenedArray.at(numCols*i + j) = result;
}

int ResultsMatrix::getResult(int i, int j) {
    return resultsFlattenedArray.at(numCols*i + j);
}

std::vector<int> RulesMatrix::getResults(int d1, int d2)
    {
        std::vector<int> out(2); // TODO do sprawdzenia xd

        if(d1 == COOPERATE && d2 == COOPERATE)
        {
            out[0] = 3;
            out[1] = 3;
        }
        else if(d1 == COOPERATE && d2 == DEFECT)
        {
            out[0] = 0;
            out[1] = 10;
        }
        else if(d1 == DEFECT && d2 == COOPERATE)
        {
            out[0] = 10;
            out[1] = 0;
        }
        else if(d1 == DEFECT && d2 == DEFECT)
        {
            out[0] = 2;
            out[1] = 2;
        }

    return out;

    }

/////////////////////////////////////////////////////////////////////////////////////////////

Evaluator::Evaluator( std::shared_ptr<RulesMatrix> _rulesMatrix) 
    {
        rulesMatrix = _rulesMatrix;
    }


// evaluateScoring zwraca obiekt typu ResultsMatrix
// z ResultsMatrix mo¿na u¿yæ getResult(int i, int j);
ResultsMatrix Evaluator::evaluateScoring(RoundDecisionMatrix _decisionMatrix, int N) 
{

    ResultsMatrix results(N);

    for(int i = 0; i< N; ++i)
    {
        for(int j = i+1; j< N; ++j)
        {
                int d1 = _decisionMatrix.getDecision(i,j);
                int d2 = _decisionMatrix.getDecision(j,i);

                std::vector<int> rules = rulesMatrix->getResults(d1, d2);

                results.updateResults(i, j, rules[0]);
                results.updateResults(j, i, rules[1]);
        }
    }

    return results;
}

 