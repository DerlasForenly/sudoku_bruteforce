#pragma once
#include "Helpers.h"
using namespace std;

class Method
{
protected:
	// Number of threads to solve sudoku
	int threads_number_ = 1;

	// Number of total iterations from all threads
	long long iterations_ = 0;

	// Execution start timestamp
	chrono::steady_clock::time_point start_;

	// Execution end timestamp
	chrono::steady_clock::time_point end_;

	// Vector of threads
	vector<thread> threads_;

	// Flag for threads to stop execution
	atomic<bool> stop_threads_{false};

	double countTime();
	virtual void run(Sudoku* sudoku) = 0;
public:
	virtual void printMeta(const Sudoku* sudoku) = 0;
	virtual void prepare(Sudoku* sudoku) = 0;
	void execute(Sudoku* sudoku);
};

