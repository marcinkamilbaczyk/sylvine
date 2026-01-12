# include<memory>
#include <map>
#include <vector>
#include "strategy.hpp"

class Player {
    public:
        Player(int id, std::shared_ptr<Strategy> strategy);
        int makeDecision(int playerAgainst);
        void updatePoints(int pointsToAdd);
        void updateMemory(int player, int decision);
        int getId();
        int getPoints();
};

class PlayerFactory {
    public:
        Player makePlayer(std::string strategyName);
};