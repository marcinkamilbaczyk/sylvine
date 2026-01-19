#include <catch2/catch_test_macros.hpp>
#include "evaluator.hpp"
#include "empty.hpp"
#include <cstdlib>
#include <ctime>

void printResults(ResultsMatrix out, int N)
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            std::cout << out.getResult(i, j) << "\t";
        }
    std::cout << "\n";
    }
}

void printDecisions(RoundDecisionMatrix in, int N)
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            std::cout << in.getDecision(i, j) << "\t";
        }
        std::cout << "\n";
    }
}

// czy da siê stworzyæ ewaluator
TEST_CASE("evaluator is corectly inicialised", "[evaluator]")
{
    std::vector<int> rules_matrix(4);
    auto fun = [&] {Evaluator evaluator(rules_matrix); };

    CHECK_NOTHROW(fun);
}


// test outputu evaluatora 1
TEST_CASE("test 1 eval", "[cdl]")
{
    int N = 2; // number of players

    std::vector<int> payoff_matrix{ 1, 2, 3, 4 };

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

    std::vector<int> payoff_matrix{ 1, 2, 3, 4 };

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

    std::vector<int> payoff_matrix{ 1, 2, 3, 4 };

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

// sprawdzenie elementu diagonalnego
TEST_CASE("test 4 eval", "[cdl]")
{
    int N = 3; // number of players

    std::vector<int> payoff_matrix{1, 2, 3, 4};

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

    int diag = output.getResult(0, 0);

    int sum_i = 0;

    for (int i = 0; i < N; ++i) {
        sum_i += output.getResult(0, i);
    }

    std::cout << "Suma dla gracza pierwszego: " << sum_i << std::endl;

    std::cout << "Element diagonalny: " << diag << std::endl;

    CHECK(diag == 0);
}

int losowa_decyzja()
{
    return rand() % 2;
}

// print wynikow (symulacja rundy)
TEST_CASE("test 5 eval", "[cdl]")
{

    srand(time(NULL));
    int N = 8; // number of players

    std::vector<int> payoff_matrix{ 3, 0, 10, 4 };

    // input: RoundDecisionMatrix
    RoundDecisionMatrix input(N);

    for(int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
        {
            if (i != j)
            {
                input.updateDecision(i, j, losowa_decyzja());
            }
        }

    std::shared_ptr<RulesMatrix> _rulesMatrix;
    Evaluator evaluator(payoff_matrix);

    //output: ResultsMatrix
    ResultsMatrix output = evaluator.evaluateScoring(input, N);

    std::cout << "\n";
    std::cout << "Wejscie (RoundDecisionMatrix): " << std::endl;
    printDecisions(input, N);

    std::cout << "\n";
    std::cout << "Wyniki (ResultsMatrix): " << std::endl;
    printResults(output, N);

    std::vector<int> points;

    for (int i = 0; i < N; ++i)
    {
        int sum = 0;
        for (int j = 0; j < N; ++j)
        {
            sum += output.getResult(i, j);
            points.push_back(sum);
        }
    }

    CHECK(1);
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


