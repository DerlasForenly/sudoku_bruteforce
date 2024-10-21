#include "ConsecutiveForce.h"
#include "Method.h"
#include "Sudoku.h"

void ConsecutiveForce::incrementSequence(int l)
{
    int i = 0;

    while (i < l)
    {
        sequence[i]++;

        if (sequence[i] > Sudoku::SIZE)
        {
            sequence[i] = 1;
            i++;
        }
        else
        {
            break;
        }
    }
}

void ConsecutiveForce::execute(Sudoku* sudoku)
{
    start = chrono::high_resolution_clock::now();
    int numberOfUnknowns = sudoku->getNumberOfUnknown();
    sequence = new int[numberOfUnknowns];

    for (int i = 0; i < numberOfUnknowns; i++)
    {
        sequence[i] = 1;
    }


    while (!sudoku->isSolved())
    {
        for (int x = 0; x < numberOfUnknowns;)
        {
            for (int i = 0; i < Sudoku::SIZE; i++)
            {
                for (int j = 0; j < Sudoku::SIZE; j++)
                {
                    if (sudoku->getOriginalItem(i, j) == 0)
                    {
                        sudoku->setMatrixItem(i, j, sequence[x]);
                        x++;
                    }
                }
            }
        }

        incrementSequence(numberOfUnknowns);
    }

    delete[] sequence;
    end = chrono::high_resolution_clock::now();
}

void ConsecutiveForce::prepare()
{
}

void ConsecutiveForce::printMeta(const Sudoku* sudoku)
{
    cout << "Elapsed time: ";
    printColored(countTime(), 6);
    cout << " milliseconds" << endl;
}
