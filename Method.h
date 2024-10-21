#pragma once
#include "Helpers.h"
using namespace std;

class Method
{
protected:
	int threadsNumber = 1;
	long long iterations = 0;
	int executionTime = 0;
	chrono::steady_clock::time_point start;
	chrono::steady_clock::time_point end;
	vector<thread> threads;
	atomic<bool> stopThreads{false};

	double countTime();
	virtual void run(Sudoku* sudoku) = 0;
public:
	virtual void printMeta(const Sudoku* sudoku) = 0;
	virtual void prepare(Sudoku* sudoku) = 0;

	void execute(Sudoku* sudoku)
	{
		start = chrono::high_resolution_clock::now();

		for (int i = 0; i < threadsNumber; ++i)
		{
			threads.push_back(thread(&Method::run, this, sudoku));
		}

		for (auto& t : threads)
		{
			t.join();
		}

		end = chrono::high_resolution_clock::now();
	};
};

