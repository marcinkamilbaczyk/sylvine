#include "player_factory.hpp"

Player PlayerFactory::makePlayer(int id, std::shared_ptr<Strategy> strategy) {
    return Player(id, strategy);
}