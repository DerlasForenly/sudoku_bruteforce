#pragma once
#include "Helpers.h"
#include "Method.h"
#include "Sudoku.h"

class RandomForce :
    public Method
{
protected:
    int threadsNumber;
public:
    void execute(Sudoku* sudoku);
    void prepare();
    void printMeta(const Sudoku* sudoku);
};

