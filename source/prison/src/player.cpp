#include "player.hpp"
#include "strategy.hpp"

int Player::getId() { 
    return id;
}

int Player::getPoints() { 
    return points;
}

std::shared_ptr<Strategy> Player::getStrategy() { 
    return strategy;
}

int Player::makeDecision(int playerAgainst) {
    return strategy->makeDecision(getMemory(playerAgainst));  
}

void Player::updateMemory(int playerAgainst, int decision) {
    gameHistory[playerAgainst].push_back(decision);
}

void Player::updatePoints(int pointsToAdd) {
    this->points += pointsToAdd;
}

std::vector<int> Player::getMemory(int playerAgainst) {
    if (gameHistory.contains(playerAgainst)) {
        return gameHistory.at(playerAgainst);
    } else {
        return {};
    }
}

Player PlayerFactory::makePlayer(int id, std::shared_ptr<Strategy> strategy) {
    return Player(id, strategy);
}