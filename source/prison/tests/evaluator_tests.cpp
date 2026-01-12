#include <catch2/catch_test_macros.hpp>
#include "evaluator.hpp"
#include "empty.hpp"

// czy da siê stworzyæ ewaluator
TEST_CASE("evaluator is corectly inicialised", "[evaluator]")
{
    std::shared_ptr<RulesMatrix> _rulesMatrix;
    auto fun = [&] {Evaluator evaluator(_rulesMatrix); };

    CHECK_NOTHROW(fun);
}

// test outputu evaluatora 1
TEST_CASE("test 1 eval", "[cdl]")
{
    int N = 2; // number of players

    // input: RoundDecisionMatrix
    RoundDecisionMatrix input(N);

    input.updateDecision(0, 1, COOPERATE);
    input.updateDecision(1, 0, DEFECT);

    std::shared_ptr<RulesMatrix> _rulesMatrix;
    Evaluator evaluator(_rulesMatrix);

    //output: ResultsMatrix
    ResultsMatrix output = evaluator.evaluateScoring(input, N);

    int r1 = output.getResult(0, 1);
    int r2 = output.getResult(1, 0);

    CHECK(r1 == 0);
}

// test outputu evaluatora
TEST_CASE("test 2 eval", "[cdl]")
{
    int N = 2; // number of players

    // input: RoundDecisionMatrix
    RoundDecisionMatrix input(N);

    input.updateDecision(0, 1, COOPERATE);
    input.updateDecision(1, 0, DEFECT);

    std::shared_ptr<RulesMatrix> _rulesMatrix;
    Evaluator evaluator(_rulesMatrix);

    //output: ResultsMatrix
    ResultsMatrix output = evaluator.evaluateScoring(input, N);

    int r1 = output.getResult(0, 1);
    int r2 = output.getResult(1, 0);

    CHECK(r2 == 10);
}

// test logiki .GetResult
TEST_CASE("test 2", "[cdl]")
{
    CHECK(fun(1, 2) == 3);
}

// czy resultsmatrix ma poprawny rozmiar
TEST_CASE("test 3", "[cdl]")
{
    CHECK(fun(1, 2) == 3);
}

// czy da siê stworzyæ ewaluator
TEST_CASE("test 4", "[cdl]")
{
    CHECK(fun(1, 2) == 3);
}


