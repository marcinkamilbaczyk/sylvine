#include "player.hpp"
#include "strategy.hpp"

// Memory

void Memory::set(int key, int value) {
    memory[key].push_back(value);
}

std::vector<int> Memory::get(int key) {
    if (memory.contains(key)) {
        return memory.at(key);
    } else {
        return {};
    }
}

// Player

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
    int decision = strategy->makeDecision(meAgainstPlayer.get(playerAgainst), playerAgainstMe.get(playerAgainst));  
    meAgainstPlayer.set(playerAgainst, decision);
    return decision;
}

void Player::updateHistory(int playerAgainst, int decision) {
    playerAgainstMe.set(playerAgainst, decision);
}

void Player::updatePoints(int pointsToAdd) {
    this->points += pointsToAdd;
}

std::vector<int> Player::getPlayerAgainstMe(int playerAgainst) {
    return playerAgainstMe.get(playerAgainst);
}

std::vector<int> Player::getMeAgainstPlayer(int playerAgainst) {
    return meAgainstPlayer.get(playerAgainst);
}

// PlayerFactory

Player PlayerFactory::makePlayer(int id, std::shared_ptr<Strategy> strategy) {
    return Player(id, strategy);
}