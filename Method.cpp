#include "Method.h"

double Method::countTime()
{
	chrono::duration<double, milli> duration = end_ - start_;
	return duration.count();
}

void Method::execute(Sudoku* sudoku)
{
	start_ = chrono::high_resolution_clock::now();

	for (int i = 0; i < threads_number_; ++i)
	{
		threads_.push_back(thread(&Method::run, this, sudoku));
	}

	for (auto& t : threads_)
	{
		t.join();
	}

	end_ = chrono::high_resolution_clock::now();
}