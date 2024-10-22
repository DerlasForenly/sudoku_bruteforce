#include "RandomFromPossibleForce.h"
using namespace std;

void RandomFromPossibleForce::run(Sudoku* sudoku)
{
    random_device rd;
    mt19937 gen(rd());

    Sudoku temp(sudoku);
    int numberOfUnknowns = sudoku->getNumberOfUnknown();
    int** variables = temp.getVariables();
    vector<vector<int>> variants = updateVariants(&temp);

    while (!temp.isSolved())
    {
        if (stop_threads_.load()) {
            return;
        }

        for (int i = 0; i < variants.size(); i++)
        {
            uniform_int_distribution<> distrib(0, variants[i].size() - 1);
            *variables[i] = variants[i][distrib(gen)];
        }
    }

    stop_threads_.store(true);
    sudoku->setMatrix(&temp);
}

vector<vector<int>> RandomFromPossibleForce::updateVariants(const Sudoku temp)
{
    vector<vector<int>> variants;

    for (int i = 0, x = 0; i < Sudoku::SIZE; i++)
    {
        for (int j = 0; j < Sudoku::SIZE; j++)
        {
            if (temp.getMatrixItem(i, j) == 0)
            {
                variants.push_back(temp.getPossible(i, j));
            }
        }
    }

    return variants;
}

void RandomFromPossibleForce::prepare(Sudoku* sudoku)
{
    cout << "Enter number of threads (CPU " << thread::hardware_concurrency() << "): ";
    setColor(6);
    cin >> threads_number_;
    setColor(7);
}

void RandomFromPossibleForce::printMeta(const Sudoku* sudoku)
{
    cout << "Elapsed time: ";
    printColored(countTime(), 6);
    cout << " milliseconds" << endl;
}