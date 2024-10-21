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
        if (stop_threads_.load()) {
            iterations_ += localIterations;
            return;
        }

        for (int i = 0; i < numberOfUnknowns; i++)
        {
            *vars[i] = distrib(gen);
        }

        localIterations++;
    }

    stop_threads_.store(true);
    iterations_ += localIterations;
    sudoku->setMatrix(&temp);
}

void RandomForce::prepare(Sudoku* sudoku)
{
    cout << "Enter number of threads (CPU " << thread::hardware_concurrency() << "): ";
    setColor(6);
    cin >> threads_number_;
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
    printColored(iterations_, 6);
    cout << endl;

    cout << "Iterations per second: ";
    setColor(6);
    cout << fixed << setprecision(0) << iterations_ / countTime() * 1000;
    setColor(7);
    cout << endl;
}
