#include <catch2/catch_test_macros.hpp>
#include "evaluator.hpp"
#include "empty.hpp"

// czy da si� stworzy� ewaluator
TEST_CASE("evaluator is corectly inicialised", "[evaluator]")
{
    int rules_matrix[4];
    auto fun = [&] {Evaluator evaluator(rules_matrix); };

    CHECK_NOTHROW(fun);
}


// test outputu evaluatora 1
TEST_CASE("test 1 eval", "[cdl]")
{
    int N = 2; // number of players

    int payoff_matrix[4] = { 1, 2, 3, 4 };

    // input: RoundDecisionMatrix
    RoundDecisionMatrix input(N);

    input.updateDecision(0, 1, COOPERATE);
    input.updateDecision(1, 0, DEFECT);

    std::shared_ptr<RulesMatrix> _rulesMatrix;
    Evaluator evaluator(payoff_matrix);

    //output: ResultsMatrix
    ResultsMatrix output = evaluator.evaluateScoring(input, N);

    int r1 = output.getResult(0, 1);
    int r2 = output.getResult(1, 0);

    CHECK(r1 == payoff_matrix[1]);
}

// test outputu evaluatora
TEST_CASE("test 2 eval", "[cdl]")
{
    int N = 2; // number of players

    int payoff_matrix[4] = { 1, 2, 3, 4 };

    // input: RoundDecisionMatrix
    RoundDecisionMatrix input(N);

    input.updateDecision(0, 1, COOPERATE);
    input.updateDecision(1, 0, DEFECT);

    std::shared_ptr<RulesMatrix> _rulesMatrix;
    Evaluator evaluator(payoff_matrix);

    //output: ResultsMatrix
    ResultsMatrix output = evaluator.evaluateScoring(input, N);

    int r1 = output.getResult(0, 1);
    int r2 = output.getResult(1, 0);

    CHECK(r2 == payoff_matrix[2]);
}

// test outputu evaluatora (3 graczy)
TEST_CASE("test 3 eval", "[cdl]")
{
    int N = 3; // number of players

    int payoff_matrix[4] = { 1, 2, 3, 4 };

    // input: RoundDecisionMatrix
    RoundDecisionMatrix input(N);

    input.updateDecision(0, 1, COOPERATE);
    input.updateDecision(0, 2, DEFECT);

    input.updateDecision(1, 0, DEFECT);
    input.updateDecision(1, 2, COOPERATE);

    input.updateDecision(2, 0, COOPERATE);
    input.updateDecision(2, 1, DEFECT);

    std::shared_ptr<RulesMatrix> _rulesMatrix;
    Evaluator evaluator(payoff_matrix);

    //output: ResultsMatrix
    ResultsMatrix output = evaluator.evaluateScoring(input, N);

    int r12 = output.getResult(0, 1);
    int r13 = output.getResult(0, 2);

    int r21 = output.getResult(1, 0);
    int r23 = output.getResult(1, 2);

    int r31 = output.getResult(2, 0);
    int r32 = output.getResult(2, 1);

    CHECK(r12 == payoff_matrix[1]);
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

// czy da si� stworzy� ewaluator
TEST_CASE("test 4", "[cdl]")
{
    CHECK(fun(1, 2) == 3);
}


