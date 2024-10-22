#include "Sudoku.h"

void Sudoku::setMethod(unique_ptr<Method>&& method)
{
    method_ = move(method);
}

Sudoku::Sudoku(Sudoku* sudoku)
{
    if (sudoku != nullptr) {
        variables_ = new int* [sudoku->number_of_unknown_];

        for (int i = 0, x = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                matrix_[i][j] = sudoku->matrix_[i][j];
                original_[i][j] = sudoku->original_[i][j];

                if (original_[i][j] == 0)
                {
                    variables_[x] = &matrix_[i][j];
                    x++;
                }
            }
        }
    }
    else {
        cout << "[Sudoku]: Null pointer received!" << endl;
    }
}

Sudoku::~Sudoku()
{
    delete[] variables_;
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

    variables_ = new int* [number_of_unknown_];
    for (int x = 0; x < number_of_unknown_; x++) 
    {
        for (int i = 0; i < Sudoku::SIZE; i++)
        {
            for (int j = 0; j < Sudoku::SIZE; j++)
            {
                if (original_[i][j] == 0)
                {
                    variables_[x] = &matrix_[i][j];
                    x++;
                }
            }
        }
    }

    int mode = 0;
    cout << "Select method:" << endl;
    cout << "[1] Full random brute force" << endl;
    cout << "[2] Consecutive brute force" << endl;
    cout << "[3] My brain force" << endl;
    cout << "[4] Random from possible force" << endl;
    setColor(6);
    cin >> mode;
    setColor(7);
    while (mode < 1 || mode > 4) {
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
    else if (mode == 3) {
        setMethod(make_unique<MyBrainForce>());
    }
    else if (mode == 4) {
        setMethod(make_unique<RandomFromPossibleForce>());
    }

    method_->prepare(this);
}

void Sudoku::loadFromFile(const string filename)
{
    ifstream file(filename);

    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            file >> matrix_[i][j];
            original_[i][j] = matrix_[i][j];
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

        if (matrix_[a][b] != 0)
        {
            matrix_[a][b] = 0;
            original_[a][b] = 0;
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
            if (matrix_[i][j] == 0) {
                std::cout << " " << " ";
            }
            else {
                if (matrix_[i][j] != original_[i][j]) {
                    setColor(9);
                }

                std::cout << matrix_[i][j] << " ";

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

    cout << endl;
}

bool Sudoku::isSolved() const
{
    /*
    Check all rows and columns
    */
    for (int i = 0; i < SIZE; i++)
    {
        int rowItems[SIZE]{};
        int colItems[SIZE]{};
        int sectionItems[SIZE]{};

        for (int j = 0; j < SIZE; j++)
        {
            int ri = matrix_[i][j];
            rowItems[ri - 1]++;

            int ci = matrix_[j][i];
            colItems[ci - 1]++;

            int tmi = ((j - (j % 3)) / 3) + (i - (i % 3));
            int tmj = (j % 3) + (i % 3) * 3;

            int si = matrix_[tmi][tmj];
            sectionItems[si - 1]++;

            if (colItems[ci - 1] != 1 || rowItems[ri - 1] != 1 || sectionItems[si - 1] != 1) {
                return false;
            }
        }
    }

    return true;
}

int Sudoku::getMatrixItem(int row, int column) const
{
    return matrix_[row][column];
}

int* Sudoku::getMatrixItemAddress(int row, int column)
{
    return &matrix_[row][column];
}

int Sudoku::getOriginalItem(int row, int column) const
{
    return original_[row][column];
}

int Sudoku::getNumberOfUnknown() const
{
    return number_of_unknown_;
}

int** Sudoku::getVariables()
{
    return variables_;
}

vector<int> Sudoku::getPossible(int row, int column) const
{
    bool rowItems[SIZE]{};
    bool colItems[SIZE]{};
    bool sectionItems[SIZE]{};
    vector<int> items;

    for (int j = 0; j < SIZE; j++)
    {
        int ci = matrix_[row][j];
        if (ci != 0) colItems[ci - 1] = true;
    }

    for (int i = 0; i < SIZE; i++)
    {
        int ri = matrix_[i][column];
        if (ri != 0) rowItems[ri - 1] = true;
    }

    for (int i = row - row % 3; i < (row - row % 3) + 3; i++)
    {
        for (int j = column - column % 3; j < (column - column % 3) + 3; j++)
        {
            int si = matrix_[i][j];
            if (si != 0) sectionItems[si - 1] = true;
        }
    }

    for (int i = 0; i < SIZE; i++)
    {
        if (!sectionItems[i] && !colItems[i] && !rowItems[i])
        {
            items.push_back(i + 1);
        }
    }

    return items;
}

void Sudoku::setMatrixItem(int row, int column, int value)
{
    matrix_[row][column] = value;
}

void Sudoku::setMatrix(Sudoku* sudoku)
{
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            this->matrix_[i][j] = sudoku->matrix_[i][j];
            this->original_[i][j] = sudoku->original_[i][j];
        }
    }
}
