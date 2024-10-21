#include "Sudoku.h"
using namespace std;

int main() 
{
    Sudoku sudoku;
    sudoku.prepare();

    printColored("\nYour sudoku to solve:\n", 6);
    sudoku.print();

    sudoku.solve();

    printColored("\nSolved sudoku:\n", 6);
    sudoku.print(true);

    system("pause");
    return 0;
}
