#ifndef PLAYER_H
#define PLAYER_H
#include <memory>
#include <map>
#include "strategy.hpp"

class Player {
    public:
        Player(int id, std::shared_ptr<Strategy> strategy): id(id), strategy(strategy), points(0) {}
        int getId();

        int makeDecision(int playerAgainst);

        void updateMemory(int playerAgainst, int decision);

        void updatePoints(int pointsToAdd);
    
    private:
        int id;
        std::shared_ptr<Strategy> strategy;
        std::map<int, std::vector<int>> gameHistory; // <playerAgainst, <0, 1>
        int points;
};

class PlayerFactory {
    public:
        Player makePlayer(int id, std::shared_ptr<Strategy> strategy);
};

#endif // PLAYER_H   