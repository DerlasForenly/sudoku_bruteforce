#pragma once
#include "Helpers.h"
#include "Method.h"
#include "Sudoku.h"
using namespace std;

/*
Check every unknown for possible variants.
Try random items from this set.
*/
class RandomFromPossibleForce :
    public Method
{
protected:
    void run(Sudoku* sudoku);
    vector<vector<int>> updateVariants(const Sudoku temp);
public:
    void prepare(Sudoku* sudoku);
    void printMeta(const Sudoku* sudoku);
};

