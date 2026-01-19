#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include "config.hpp"
#include "evaluator.hpp"
#include "player.hpp"
#include "output.hpp"
#include "game.hpp"

// Game - Zajko, Dębek, Prędota

Game::Game(Config config)
{
    numRounds = config.getNumRounds();
    std::cout << "Number of rounds: " << numRounds << std::endl;
    for (const auto &[strategyName, percentage] : config.getStrategies())
    {
        int count = config.getNumPrisonersForStrategy(strategyName);
        playersStrategyMap[strategyName] = count;
    }
    auto payoff = config.getPayoffMatrix();
    scoringMatrix[0] = payoff[0]; // R
    scoringMatrix[1] = payoff[1]; // S
    scoringMatrix[2] = payoff[2]; // T
    scoringMatrix[3] = payoff[3]; // P
}

std::unique_ptr<Strategy> makeStrategyByName(const std::string &strategyName)
{
    if (strategyName == "AlwaysPositives")
    {
        return std::make_unique<AlwaysPositives>();
    }
    else if (strategyName == "AlwaysNegatives")
    {
        return std::make_unique<AlwaysNegatives>();
    }
    else if (strategyName == "RandomDecision")
    {
        return std::make_unique<RandomDecision>();
    }
    else if (strategyName == "TitForTat")
    {
        return std::make_unique<TitForTat>();
    }
    else
    {
        throw std::invalid_argument("Unknown strategy name: " + strategyName);
    }
}

std::vector<Player> Game::createPlayers()
{
    auto players = std::vector<Player>();
    auto playerFactory = PlayerFactory();
    for (auto pair : playersStrategyMap)
    {
        for (int i = 0; i < pair.second; i++)
        {
            players.push_back(playerFactory.makePlayer(pair.second, makeStrategyByName(pair.first))); // TODO: jak będą strategie
        }
    }
    return players;
}

RoundDecisionMatrix Game::playRound(std::vector<Player> &players)
{
    auto roundDecisionMatrix = RoundDecisionMatrix(players.size());
    for (size_t i = 0; i < players.size(); i++)
    {
        for (size_t j = 0; j < players.size(); j++)
        {
            if (i == j)
                continue;
            roundDecisionMatrix.updateDecision(i, j, players.at(i).makeDecision(j));
        }
    }
    return roundDecisionMatrix;
}

void Game::updatePointsAndScoreBoard(std::vector<Player> &players, RoundDecisionMatrix &roundDecisionMatrix, Output &output, Evaluator &evaluator)
{
    auto pointsIncrements = evaluator.evaluateScoring(roundDecisionMatrix, players.size());
    auto scoreBoard = std::vector<int>();
    for (size_t i = 0; i < players.size(); i++)
    {
        for (size_t j = 0; j < players.size(); j++)
        {
            if (i == j)
                continue;
            players.at(i).updatePoints(pointsIncrements.getResult(i, j));
        }
        scoreBoard.push_back(players.at(i).getPoints());
    }
    output.addToScoreHistory(scoreBoard);
    output.addToDecisionsHistory(roundDecisionMatrix);
}

void Game::updatePlayersMemory(std::vector<Player> &players, RoundDecisionMatrix &roundDecisionMatrix)
{
    for (size_t i = 0; i < players.size(); i++)
    {
        for (size_t j = 0; j < players.size(); j++)
        {
            if (i == j)
                continue;
            players.at(i).updateHistory(j, roundDecisionMatrix.getDecision(j, i));
        }
    }
}

Output Game::play()
{
    // Utwórz graczy
    auto players = createPlayers();
    // Zagraj gre
    auto output = Output();
    auto evaluator = Evaluator(scoringMatrix);
    for (size_t i = 0; i < numRounds; i++)
    {
        auto roundDecisionMatrix = playRound(players);
        // Policz punkty dla każdego gracza
        updatePointsAndScoreBoard(players, roundDecisionMatrix, output, evaluator);

        // Zupdatuj pamięć graczy o decyzjach przeciwników
        updatePlayersMemory(players, roundDecisionMatrix);
    }
    return output;
}
