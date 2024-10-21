#pragma once
#include "Helpers.h"
#include "Method.h"

class ConsecutiveForce :
    public Method
{
protected:
    void run(Sudoku* sudoku);
public:
    void prepare(Sudoku* sudoku);
    void printMeta(const Sudoku* sudoku);
};

