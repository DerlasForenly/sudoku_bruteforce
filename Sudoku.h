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
	int number_of_unknown_ = 81;
	unique_ptr<Method> method_;

	void createRandomEmptyFields();

public:
	Sudoku(unique_ptr<Method>&& method = {}) : method_(move(method)) {}

	void setMethod(unique_ptr<Method>&& method);
	void setMatrixItem(int row, int column, int value);

	void solve();
	void prepare();
	void loadFromFile(const string filename);
	void print(bool withMeta = false) const;
	bool isSolved() const;

	int getMatrixItem(int row, int column) const;
	int getOriginalItem(int row, int column) const;
	int getNumberOfUnknown() const;
};

