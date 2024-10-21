#include "RandomForce.h"
using namespace std;

void RandomForce::execute(Sudoku* sudoku)
{
    start = chrono::high_resolution_clock::now();

    while (true)
    {
    refill:
        iterations++;
        for (int i = 0; i < Sudoku::SIZE; i++)
        {
            int rowItems[Sudoku::SIZE]{ 0 };
            int colItems[Sudoku::SIZE]{ 0 };

            for (int j = 0; j < Sudoku::SIZE; j++)
            {
                int originalItem = sudoku->getOriginalItem(i, j);
                int value = originalItem == 0 ? random() : originalItem;
                sudoku->setMatrixItem(i, j, value);
                int ri = value;
                rowItems[ri - 1]++;

                originalItem = sudoku->getOriginalItem(j, i);
                value = originalItem == 0 ? random() : originalItem;
                sudoku->setMatrixItem(j, i, value);
                int ci = value;
                colItems[ci - 1]++;

                if (colItems[ci - 1] > 1 || rowItems[ri - 1] > 1) {
                    goto refill;
                }
            }
        }

        for (int i = 0; i < Sudoku::SIZE; i++)
        {
            int sectionItems[Sudoku::SIZE]{ 0 };

            for (int j = 0; j < Sudoku::SIZE; j++)
            {
                int tmi = ((j - (j % 3)) / 3) + (i - (i % 3));
                int tmj = (j % 3) + (i % 3) * 3;

                int si = sudoku->getMatrixItem(tmi, tmj);
                sectionItems[si - 1]++;

                if (sectionItems[si - 1] > 1) {
                    goto refill;
                }
            }
        }

        break;
    }

    end = chrono::high_resolution_clock::now();
}

void RandomForce::prepare()
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
}
