#pragma once
#include "Helpers.h"
#include "Sudoku.h"
#include "Method.h"
#include "RandomForce.h"
#include "ConsecutiveForce.h"
#include "MyBrainForce.h"
#include "RandomFromPossibleForce.h"
using namespace std;

class Sudoku
{
public:
	static const int SIZE = 9;

protected:
	// Work grid, can be updated during solving
	int matrix_[SIZE][SIZE]{ 0 };

	// Original grid, should contain its original empty spaces
	int original_[SIZE][SIZE]{ 0 };

	// Used for fast access to unknown items
	int** variables_;

	// Number of items in original_ grid with value 0
	int number_of_unknown_ = 81;

	// Solving method
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
	vector<int> getPossible(int row, int column) const;

	void setMethod(unique_ptr<Method>&& method);
	void setMatrixItem(int row, int column, int value);
	void setMatrix(Sudoku* sudoku);
};

