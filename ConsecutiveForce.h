#pragma once
#include "Helpers.h"
#include "Method.h"

class ConsecutiveForce :
    public Method
{
protected:
    int* sequence;
    void incrementSequence(int l);
public:
    void execute(Sudoku* sudoku);
    void prepare();
    void printMeta(const Sudoku* sudoku);
};

