#pragma once
#include "Helpers.h"
#include "Method.h"
#include "Sudoku.h"

class RandomForce :
    public Method
{
protected:
    void run(Sudoku* sudoku);
public:
    void prepare(Sudoku* sudoku);
    void printMeta(const Sudoku* sudoku);
};

