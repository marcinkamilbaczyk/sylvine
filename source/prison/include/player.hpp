#ifndef PLAYER_H
#define PLAYER_H
#include <memory>
#include <map>
#include "strategy.hpp"

class Memory {
    private:
        std::map<int, std::vector<int>> memory;
    public:
        void set(int key, int value);
        std::vector<int> get(int key);
};

class Player {
    public:
        Player(int id, std::shared_ptr<Strategy> strategy): id(id), strategy(strategy), points(0) {}
        int getId();
        int getPoints();
        std::shared_ptr<Strategy> getStrategy();

        int makeDecision(int playerAgainst);

        void updateHistory(int playerAgainst, int decision);

        void updatePoints(int pointsToAdd);

        std::vector<int> getMeAgainstPlayer(int playerAgainst);

        std::vector<int> getPlayerAgainstMe(int playerAgainst);
    
    private:
        int id;
        std::shared_ptr<Strategy> strategy;
        Memory meAgainstPlayer; // <id, <0, 1>
        Memory playerAgainstMe; // <playerAgainst, <0, 1>
        int points;
};

class PlayerFactory {
    public:
        static Player makePlayer(int id, std::shared_ptr<Strategy> strategy);
};

#endif // PLAYER_H   