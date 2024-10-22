#include "MyBrainForce.h"

void MyBrainForce::run(Sudoku* sudoku)
{
    Sudoku temp(sudoku);
    int numberOfUnknowns = sudoku->getNumberOfUnknown();
    int** vars = temp.getVariables();

    while (!temp.isSolved())
    {
        cout << "Thinking..." << endl;
    }

    sudoku->setMatrix(&temp);
}

void MyBrainForce::prepare(Sudoku* sudoku)
{
    cout << "Enter number of threads (CPU " << thread::hardware_concurrency() << "): ";
    setColor(6);
    cin >> threads_number_;
    setColor(7);
    cout << "No way, I have only 1 brain" << endl;
}

void MyBrainForce::printMeta(const Sudoku* sudoku)
{
    cout << "Elapsed time: ";
    printColored(countTime(), 6);
    cout << " milliseconds" << endl;
}
