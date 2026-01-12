#include <catch2/catch_test_macros.hpp>
#include <vector>

#include "game.hpp"

TEST_CASE("test 1", "[cdl]")
{
    CHECK_NOTHROW(Game(Config()).play().addToScoreHistory(std::vector<int>{1,2,3}));
}

