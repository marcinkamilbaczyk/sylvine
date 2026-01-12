#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp> 
#include "strategy.hpp"
#include <vector>

const std::vector<int> emptyHist;

TEST_CASE("AlwaysPositives Strategy", "[strategies]") {
    AlwaysPositives strategy;

    SECTION("Always returns 1 regardless of history") {

        REQUIRE(strategy.makeDecision(emptyHist, emptyHist) == 1);


        std::vector<int> history = { 0, 0, 0, 0 };
        REQUIRE(strategy.makeDecision(history, history) == 1);
    }
}
TEST_CASE("AlwaysNegatives Strategy", "[strategies]") {
    AlwaysNegatives strategy;

    SECTION("Always returns 0 regardless of history") {
        REQUIRE(strategy.makeDecision(emptyHist, emptyHist) == 0);

        std::vector<int> history = { 1, 1, 1 };
        REQUIRE(strategy.makeDecision(history, history) == 0);
    }
}

TEST_CASE("TitForTat Strategy", "[strategies]") {
    TitForTat strategy;

    SECTION("First move (empty history) should be cooperative (1)") {
        REQUIRE(strategy.makeDecision(emptyHist, emptyHist) == 1);
    }

    SECTION("Copies opponent's last move - Cooperation") {
        std::vector<int> playerHist = { 1 };
        std::vector<int> opponentHist = { 1 }; // Przeciwnik wspó³pracowa³

        REQUIRE(strategy.makeDecision(playerHist, opponentHist) == 1);
    }

    SECTION("Copies opponent's last move - Defection") {
        std::vector<int> playerHist = { 1 };
        std::vector<int> opponentHist = { 0 }; // Przeciwnik zdradzi³

        REQUIRE(strategy.makeDecision(playerHist, opponentHist) == 0);
    }
}

TEST_CASE("RandomDecision Strategy", "[strategies]") {
    RandomDecision strategy;

    SECTION("Returns valid move (0 or 1)") {
        int result = strategy.makeDecision(emptyHist, emptyHist);
        bool isValidMove = (result == 0 || result == 1);

        REQUIRE(isValidMove);
    }
}

TEST_CASE("StrategyManager Integration", "[manager]") {
    StrategyManager manager;

    SECTION("Executes AlwaysPositives correctly via name") {
        int result = manager.Execute("AlwaysPositives", emptyHist, emptyHist);
        REQUIRE(result == 1);
    }

    SECTION("Executes AlwaysNegatives correctly via name") {
        int result = manager.Execute("AlwaysNegatives", emptyHist, emptyHist);
        REQUIRE(result == 0);
    }

    SECTION("Executes TitForTat correctly via name") {
        std::vector<int> pHist = { 1 };
        std::vector<int> oHist = { 0 }; //

        int result = manager.Execute("TitForTat", pHist, oHist);
        REQUIRE(result == 0);
    }
}