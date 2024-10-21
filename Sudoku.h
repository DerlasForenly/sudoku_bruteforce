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
	int matrix_[SIZE][SIZE]{ 0 };
	int original_[SIZE][SIZE]{ 0 };

	// Used for fast access to unknown items
	int** variables;

	int number_of_unknown_ = 81;
	unique_ptr<Method> method_;

	void createRandomEmptyFields();

public:
	Sudoku(unique_ptr<Method>&& method = {}) : method_(move(method)) {}
	Sudoku(Sudoku* sudoku);
	~Sudoku();

	void solve();
	void prepare();
	void loadFromFile(const string filename);
	void print(bool withMeta = false) const;
	bool isSolved() const;

	int getMatrixItem(int row, int column) const;
	int* getMatrixItemAddress(int row, int column);
	int getOriginalItem(int row, int column) const;
	int getNumberOfUnknown() const;
	int** getVariables();

	void setMethod(unique_ptr<Method>&& method);
	void setMatrixItem(int row, int column, int value);
	void setMatrix(Sudoku* sudoku);
};

