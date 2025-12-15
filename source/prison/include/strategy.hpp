#ifndef STRATEGY_H
#define STRATEGY_H
#include <vector>

class Strategy {
    public:
        virtual int makeDecision(std::vector<int> gameHistoryWithPlayer) = 0;
};

class BaseStrategy: public Strategy {
    public:
        int makeDecision(std::vector<int> gameHistoryWithPlayer) override {
            return 1;
        }
};

#endif // STRATEGY_H   