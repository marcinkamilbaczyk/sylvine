#ifndef STRATEGY_H
#define STRATEGY_H
#include <vector>

class Strategy {
    public:
        virtual int makeDecision(std::vector<int> firstPlayerHistory, std::vector<int> secondPlayerHistory) = 0;
};

class BaseStrategy: public Strategy {
    public:
        int makeDecision(std::vector<int> firstPlayerHistory, std::vector<int> secondPlayerHistory) override {
            return 1;
        }
};

#endif // STRATEGY_H   