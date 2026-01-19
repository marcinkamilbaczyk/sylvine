#include <catch2/catch_test_macros.hpp>

#include "player.hpp"
#include "strategy.hpp"


TEST_CASE("Player initialization and basic logic", "[player]") {
    auto mockStrategy = std::make_shared<BaseStrategy>();
    int playerId = 10;
    Player player(playerId, mockStrategy);

    SECTION("Player has correct initial ID and zero points") {
        REQUIRE(player.getId() == 10);
        REQUIRE(player.getPoints() == 0);
        REQUIRE(player.getStrategy() == mockStrategy);
    }

    SECTION("Points are updated correctly") {
        player.updatePoints(5);
        CHECK(player.getPoints() == 5);

        player.updatePoints(10);
        REQUIRE(player.getPoints() == 15);
        
        player.updatePoints(-20);
        REQUIRE(player.getPoints() == -5);
        
        player.updatePoints(0);
        REQUIRE(player.getPoints() == -5);
    }

    SECTION("Strategy is used to make decisions") {
        int opponentId = 5;
        auto meAgainstPlayer1 = player.getMeAgainstPlayer(opponentId);
        REQUIRE(meAgainstPlayer1.size() == 0);

        int decision = player.makeDecision(opponentId);
        auto meAgainstPlayer2 = player.getMeAgainstPlayer(opponentId);
        REQUIRE(meAgainstPlayer2.size() == 1);
        REQUIRE(decision == 1);
        REQUIRE(meAgainstPlayer2[0] == 1);
    }

    SECTION("Memory (Game History) is updated correctly") {
        int opponentId = 5;
        player.updateHistory(opponentId, 0);
        player.updateHistory(opponentId, 1);
        
        auto playerAgainstMe = player.getPlayerAgainstMe(opponentId);
        REQUIRE(playerAgainstMe.size() == 2);
        REQUIRE(playerAgainstMe[0] == 0);
        REQUIRE(playerAgainstMe[1] == 1);
    }
}

TEST_CASE("PlayerFactory creates instances correctly", "[PlayerFactory]") {
    auto strategy = std::make_shared<BaseStrategy>();
    int testId = 123;

    SECTION("Factory creates a player with the correct ID") {
        Player player = PlayerFactory::makePlayer(testId, strategy);
        REQUIRE(player.getId() == testId);
    }

    SECTION("Factory assigns the correct strategy pointer") {
        Player player = PlayerFactory::makePlayer(testId, strategy);
        REQUIRE(player.getStrategy() == strategy);
        REQUIRE(player.getStrategy() != nullptr);
    }

    SECTION("Factory handles nullptr strategy correctly") {
        Player player = PlayerFactory::makePlayer(99, nullptr);

        REQUIRE(player.getId() == 99);
        REQUIRE(player.getStrategy() == nullptr);
    }
}