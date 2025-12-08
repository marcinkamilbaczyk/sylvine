#ifndef PLAYER_FACTORY_H
#define PLAYER_FACTORY_H
#include "player.hpp"

class PlayerFactory {
    Player makePlayer(int id, std::shared_ptr<Strategy> strategy);
};

#endif // PLAYER_FACTORY_H   