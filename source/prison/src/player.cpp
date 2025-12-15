#include "player.hpp"
#include "strategy.hpp"

int Player::getId() { 
    return id;
}

int Player::makeDecision(int playerAgainst) {
    return strategy->makeDecision(gameHistory.at(playerAgainst));
}

void Player::updateMemory(int playerAgainst, int decision) {
    gameHistory[playerAgainst].push_back(decision);
}

void Player::updatePoints(int pointsToAdd) {
    this->points += pointsToAdd;
}

Player PlayerFactory::makePlayer(int id, std::shared_ptr<Strategy> strategy) {
    return Player(id, strategy);
}