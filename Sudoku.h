#pragma once
#include "Helpers.h"
#include "Sudoku.h"
#include "Method.h"
#include "RandomForce.h"
#include "ConsecutiveForce.h"
using namespace std;

class Sudoku
{
public:
	static const int SIZE = 9;

protected:
	int matrix[SIZE][SIZE]{ 0 };
	int original[SIZE][SIZE]{ 0 };
	int numberOfUnknown_ = 81;
	unique_ptr<Method> method_;

	void createRandomEmptyFields();

public:
	Sudoku(unique_ptr<Method>&& method = {}) : method_(move(method)) {}
	void setMethod(unique_ptr<Method>&& method);
	void solve();
	void prepare();
	void loadFromFile(const string filename);
	void print(bool withMeta = false) const;
	bool isSolved() const;

	void setMatrixItem(int row, int column, int value)
	{
		matrix[row][column] = value;
	}

	int getMatrixItem(int row, int column) const
	{
		return matrix[row][column];
	}

	int getOriginalItem(int row, int column) const
	{
		return original[row][column];
	}

	int getNumberOfUnknown() const
	{
		return numberOfUnknown_;
	}
};

