#include <vector>

class Strategy {
    public:
        virtual int makeDecision(std::vector<int> gameHistoryWithPlayer) = 0;
};

class AlwaysPositives: public Strategy {
    
};

class AlwaysNegatives: public Strategy {

};

class RandomDecision: public Strategy {

};
