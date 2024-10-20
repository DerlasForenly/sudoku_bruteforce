#include "Sudoku.h"

void Sudoku::setMethod(unique_ptr<Method>&& method)
{
    method_ = move(method);
}

void Sudoku::solve()
{
    if (method_) {
        method_->execute(this);
    }
    else {
        std::cout << "[Sudoku]: Method isn't set!" << endl;
    }
}

void Sudoku::prepare()
{
    loadFromFile("solved.txt");

    cout << "Enter number of unknown items (max: 81): ";
    setColor(6);
    cin >> number_of_unknown_;
    setColor(7);
    while (number_of_unknown_ > 81) {
        cout << "Number of unknowns is more than 81, enter again: ";
        setColor(6);
        cin >> number_of_unknown_;
        setColor(7);
    }
    createRandomEmptyFields();

    int mode = 0;
    cout << "Select method:" << endl;
    cout << "[1] Full random brute force" << endl;
    cout << "[2] Consecutive brute force" << endl;
    setColor(6);
    cin >> mode;
    setColor(7);
    while (mode < 1 || mode > 2) {
        cout << "Wrong number, enter again: ";
        setColor(6);
        cin >> mode;
        setColor(7);
    }

    if (mode == 1) {
        setMethod(make_unique<RandomForce>());
    }
    else if (mode == 2) {
        setMethod(make_unique<ConsecutiveForce>());
    }

    method_->prepare();
}

void Sudoku::loadFromFile(const string filename)
{
    ifstream file(filename);

    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            file >> matrix[i][j];
            original[i][j] = matrix[i][j];
        }
    }

    file.close();
}

void Sudoku::createRandomEmptyFields()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 9);

    for (int i = 0; i < number_of_unknown_; ++i) {
        int a = distrib(gen) - 1;
        int b = distrib(gen) - 1;

        if (matrix[a][b] != 0)
        {
            matrix[a][b] = 0;
            original[a][b] = 0;
        }
        else {
            i--;
        }
    }
}

void Sudoku::print(bool withMeta) const
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            if (matrix[i][j] == 0) {
                std::cout << " " << " ";
            }
            else {
                if (matrix[i][j] != original[i][j]) {
                    setColor(9);
                }

                std::cout << matrix[i][j] << " ";

                setColor(7);
            }

            if ((j + 1) % 3 == 0 && j < 8)
            {
                setColor(6);
                std::cout << "| ";
                setColor(7);
            }
        }

        std::cout << endl;

        if ((i + 1) % 3 == 0 && i < 8)
        {
            setColor(6);
            std::cout << "- - - | - - - | - - -" << endl;
            setColor(7);
        }
    }

    if (withMeta) {
        method_->printMeta(this);
    }
}

bool Sudoku::isSolved() const
{
    /*
    Check all rows and columns
    */
    for (int i = 0; i < SIZE; i++)
    {
        int rowItems[SIZE]{ 0 };
        int colItems[SIZE]{ 0 };

        for (int j = 0; j < SIZE; j++)
        {
            int ri = matrix[i][j];
            rowItems[ri - 1]++;

            int ci = matrix[j][i];
            colItems[ci - 1]++;

            if (colItems[ci - 1] > 1 || rowItems[ri - 1] > 1) {
                return false;
            }
        }
    }

    /*
    Check for sections
    */
    for (int i = 0; i < SIZE; i++)
    {
        int sectionItems[SIZE]{ 0 };

        for (int j = 0; j < SIZE; j++)
        {
            int tmi = ((j - (j % 3)) / 3) + (i - (i % 3));
            int tmj = (j % 3) + (i % 3) * 3;

            int si = matrix[tmi][tmj];
            sectionItems[si - 1]++;

            if (sectionItems[si - 1] > 1) {
                return false;
            }
        }
    }

    return true;
}

int Sudoku::getMatrixItem(int row, int column) const
{
    return matrix[row][column];
}

int Sudoku::getOriginalItem(int row, int column) const
{
    return original[row][column];
}

int Sudoku::getNumberOfUnknown() const
{
    return number_of_unknown_;
}

void Sudoku::setMatrixItem(int row, int column, int value)
{
    matrix[row][column] = value;
}
