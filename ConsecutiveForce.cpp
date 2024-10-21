#include "ConsecutiveForce.h"
#include "Method.h"
#include "Sudoku.h"

void ConsecutiveForce::run(Sudoku* sudoku)
{
    Sudoku temp(sudoku);
    long long localIterations = 0;
    int numberOfUnknowns = sudoku->getNumberOfUnknown();
    int** vars = temp.getVariables();
    for (int i = 0; i < numberOfUnknowns; i++) *vars[i] = 1;

    while (!temp.isSolved())
    {
        if (stop_threads_.load()) {
            iterations_ += localIterations;
            return;
        }

        int i = 0;

        while (i < numberOfUnknowns)
        {
            *vars[i] += 1;

            if (*vars[i] > Sudoku::SIZE)
            {
                *vars[i] = 1;
                i++;
            }
            else
            {
                break;
            }
        }

        localIterations++;
    }

    stop_threads_.store(true);
    iterations_ += localIterations;
    sudoku->setMatrix(&temp);
}

void ConsecutiveForce::prepare(Sudoku* sudoku)
{
    int threads_number_ = 1;
    cout << "Currently number of threads for this method is always 1" << endl;
}

void ConsecutiveForce::printMeta(const Sudoku* sudoku)
{
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
