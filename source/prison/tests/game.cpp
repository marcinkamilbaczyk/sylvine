#include <catch2/catch_test_macros.hpp>
#include <filesystem>
#include <vector>

#include "game.hpp"

TEST_CASE("test 1", "[cdl]")
{
    Config cfg(std::filesystem::path{SYLVINE_TEST_CONFIG_PATH}.string());
    CHECK_NOTHROW(Game(cfg).play().addToScoreHistory(std::vector<int>{1,2,3}));
}

