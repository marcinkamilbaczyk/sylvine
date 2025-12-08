#include "player.hpp"
#include "strategy.hpp"

int Player::getId() {
    return id;
}

int Player::makeDecision() {
    return strategy->makeDecision(gameHistory.at(id));
}

void Player::addDecision(int userId, int decision) {
    gameHistory[userId].push_back(decision);
}

void Player::addPoints(int points) {
    this->points += points;
}