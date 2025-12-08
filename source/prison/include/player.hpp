#ifndef PLAYER_H
#define PLAYER_H
#include <memory>
#include <map>
#include "strategy.hpp"

class Player {
    public:
        Player(int id, std::shared_ptr<Strategy> strategy): id(id), strategy(strategy), points(0) {}
        int getId();

        int makeDecision();

        void addDecision(int userId, int decision);

        void addPoints(int points);
    
    private:
        int id;
        std::shared_ptr<Strategy> strategy;
        std::map<int, std::vector<int>> gameHistory; // <userId, <0, 1>
        int points;
};

#endif // PLAYER_H   