#pragma once
#include "Helpers.h"
using namespace std;

class Method
{
protected:
	int threads_number_ = 1;
	long long iterations_ = 0;
	chrono::steady_clock::time_point start_;
	chrono::steady_clock::time_point end_;
	vector<thread> threads_;
	atomic<bool> stop_threads_{false};

	double countTime();
	virtual void run(Sudoku* sudoku) = 0;
public:
	virtual void printMeta(const Sudoku* sudoku) = 0;
	virtual void prepare(Sudoku* sudoku) = 0;
	void execute(Sudoku* sudoku);
};

