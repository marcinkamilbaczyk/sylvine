#include "strategy.hpp"



//Positive strategy
int AlwaysPositives::makeDecision(std::vector<int> playerHistory, std::vector<int> gameHistoryWithPlayer){
  return 1;
}

//Negative strategy
int AlwaysNegatives::makeDecision(std::vector<int> playerHistory, std::vector<int> gameHistoryWithPlayer){
  return 0;
}

//Random strategy
RandomDecision::RandomDecision(){
  std::srand(std::time(0));
}

int RandomDecision::makeDecision(std::vector<int> playerHistory, std::vector<int> gameHistoryWithPlayer){
  return std::rand()%2;
}  


//Tot for tat strategy
int TitForTat::makeDecision(std::vector<int> playerHistory, std::vector<int> gameHistoryWithPlayer){
    if (playerHistory.empty()){
	return 1;
      }
    else{
      return gameHistoryWithPlayer.back();
    }
  }

//Strategy Manager
StrategyManager::StrategyManager(){
  look_up_strategy["AlwaysPositives"] = std::make_unique<AlwaysPositives>();
  look_up_strategy["AlwaysNegatives"] = std::make_unique<AlwaysNegatives>();
  look_up_strategy["RandomDecision"] = std::make_unique<RandomDecision>();
  look_up_strategy["TitForTat"] = std::make_unique<TitForTat>();

}

int StrategyManager::Execute(std::string strategy_name, std::vector<int> playerHistory, std::vector<int> gameHistoryWithPlayer)
{
  look_up_strategy[strategy_name]->makeDecision(playerHistory, gameHistoryWithPlayer);
  return -1;
}
