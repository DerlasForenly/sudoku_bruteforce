#include "RandomForce.h"
using namespace std;

void RandomForce::run(Sudoku* sudoku)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 9);
    Sudoku temp(sudoku);
    long long localIterations = 0;
    int numberOfUnknowns = sudoku->getNumberOfUnknown();
    int** vars = temp.getVariables();

    while (!temp.isSolved())
    {
        if (stopThreads.load()) {
            iterations += localIterations;
            return;
        }

        for (int i = 0; i < numberOfUnknowns; i++)
        {
            *vars[i] = distrib(gen);
        }

        localIterations++;
    }

    stopThreads.store(true);
    iterations += localIterations;
    sudoku->setMatrix(&temp);
}

void RandomForce::prepare(Sudoku* sudoku)
{
    cout << "Enter number of threads (CPU " << thread::hardware_concurrency() << "): ";
    setColor(6);
    cin >> threadsNumber;
    setColor(7);
}

void RandomForce::printMeta(const Sudoku* sudoku)
{
    cout << "Chance to generate valid solution: ";
    setColor(6);
    cout << 1 / pow(9, sudoku->getNumberOfUnknown()) * 100 << "%" << endl;
    setColor(7);

    cout << "Elapsed time: ";
    printColored(countTime(), 6);
    cout << " milliseconds" << endl;

    cout << "Number of iterations: ";
    printColored(iterations, 6);
    cout << endl;

    cout << "Iterations per second: ";
    setColor(6);
    cout << fixed << setprecision(0) << iterations / countTime() * 1000;
    setColor(7);
    cout << endl;
}
