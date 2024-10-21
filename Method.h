#pragma once
#include "Helpers.h"
using namespace std;

class Method
{
protected:
	long long iterations = 0;
	int executionTime = 0;
	chrono::steady_clock::time_point start;
	chrono::steady_clock::time_point end;

	double countTime();
public:
	virtual void printMeta(const Sudoku* sudoku) = 0;
	virtual void prepare() = 0;
	virtual void execute(Sudoku* sudoku) = 0;
};

