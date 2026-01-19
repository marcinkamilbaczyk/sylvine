#ifndef STRATEGY_H
#define STRATEGY_H

#include <map>
#include <string>
#include <vector>
//#include <bits/stdc++.h>
#include <random>
class Strategy {
public:
  Strategy(){}
  virtual int makeDecision(std::vector<int> playerHistory, std::vector<int> gameHistoryWithPlayer) = 0;
  virtual ~Strategy() = default;
};

class AlwaysPositives: public Strategy {
public:
  int makeDecision(std::vector<int> playerHistory, std::vector<int> gameHistoryWithPlayer);
    
};

class AlwaysNegatives: public Strategy {
public:
  int makeDecision(std::vector<int> playerHistory, std::vector<int> gameHistoryWithPlayer);
};

class RandomDecision: public Strategy {
public:
  RandomDecision();
  int makeDecision(std::vector<int> playerHistory, std::vector<int> gameHistoryWithPlayer);
  
};

class TitForTat: public Strategy {
public:
  int makeDecision(std::vector<int> playerHistory, std::vector<int> gameHistoryWithPlayer);
};

/*
class NewStrategy: public Strategy {
public:
  int makeDecision(std::vector<int> playerHistory, std::vector<int> gameHistoryWithPlayer){
    return -1;
  }
};
*/

class StrategyManager {
public:
  StrategyManager();
  int Execute(std::string strategy_name, std::vector<int> playerHistory, std::vector<int> gameHistoryWithPlayer);
private:
  std::map<std::string, std::unique_ptr<Strategy>> look_up_strategy;
};

#endif
