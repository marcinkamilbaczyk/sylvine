#ifndef STRATEGY_H
#define STRATEGY_H
#include <vector>

class Strategy {
    public:
        virtual int makeDecision(std::vector<int> gameHistoryWithPlayer) = 0;
};

#endif // STRATEGY_H   