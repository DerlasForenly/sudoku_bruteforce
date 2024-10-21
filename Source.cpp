#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstdlib> 
#include <ctime>
#include <chrono>
#include <thread>
#include <random>
#include <windows.h>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;

const int S = 9;
int numThreads;
long long totalIterations = 0;
atomic<bool> stopThreads(false);
int methodId = 2;

static void readMatrixFromFile(const string& filename, int m[S][S]);
static void printFormattedMatrix(int m[S][S], int c[S][S]);
static void fullRandBruteForce(int m[S][S]);
static void consecutiveBruteForce(int m[S][S], int unknown);
static void setRandomZeros(int m[S][S], int n);
static void setColor(int color);
static bool isSudokuSolved(int m[S][S]);
static int* incrementSequence(int* s, int l);

int main() 
{
    int n;
    int m[S][S];
    readMatrixFromFile("solved.txt", m);

    cout << "Enter number of unknown items: ";
    setColor(6);
    cin >> n;
    setColor(7);
    cout << "Enter number of threads (CPU " << thread::hardware_concurrency() << "): ";
    setColor(6);
    cin >> numThreads;
    setColor(7);
    cout << "Chance to generate valid solution: ";
    setColor(6);
    cout << 1 / pow(9, n) * 100 << "%" << endl;
    setColor(7);
    cout << "My speed is ";
    setColor(6);
    cout << "~26 681 854";
    setColor(7);
    cout << " iterations/second" << endl << endl;

    setRandomZeros(m, n);
    cout << "Sudoku:" << endl;
    printFormattedMatrix(m, m);

    // Main execution
    auto start = chrono::high_resolution_clock::now();

    if (methodId == 1)
    {
        vector<thread> threads;

        for (int i = 0; i < numThreads; ++i) {
            threads.push_back(thread(fullRandBruteForce, m));
        }

        for (auto& t : threads) {
            t.join();
        }
    }
    else if (methodId == 2) {
        consecutiveBruteForce(m, n);
    }

    auto end = chrono::high_resolution_clock::now();
    // Finished main execution

    chrono::duration<double, milli> duration = end - start;
    cout << "Elapsed time: ";
    setColor(6);
    cout << duration.count();
    setColor(7);
    cout << " milliseconds" << endl;

    cout << "Final speed was ";
    setColor(6);
    cout << fixed << setprecision(0) << totalIterations / duration.count() * 1000;
    setColor(7);
    cout << " iterations/second" << endl << endl;

    system("pause");
    return 0;
}

void readMatrixFromFile(const string& filename, int m[S][S]) {
    ifstream file(filename);

    for (int i = 0; i < S; ++i)
    {
        for (int j = 0; j < S; ++j)
        {
            file >> m[i][j];
        }
    }

    file.close();
}

void printFormattedMatrix(int m[S][S], int c[S][S]) {
    for (int i = 0; i < S; ++i)
    {
        for (int j = 0; j < S; ++j)
        {
            if (m[i][j] == 0) {
                cout << " " << " ";
            }
            else {
                if (m[i][j] != c[i][j]) {
                    setColor(9);
                }

                cout << m[i][j] << " ";

                setColor(7);
            }

            if ((j + 1) % 3 == 0 && j < 8)
            {
                setColor(6);
                cout << "| ";
                setColor(7);
            }
        }

        cout << endl;

        if ((i + 1) % 3 == 0 && i < 8)
        {
            setColor(6);
            cout << "- - - | - - - | - - -" << endl;
            setColor(7);
        }
    }
}

void fullRandBruteForce(int m[S][S])
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 9);
    long long iterations = 0;
    int tm[S][S]{};
    
    while (true)
    {
        refill:

        if (stopThreads.load()) {
            totalIterations += iterations;
            return;
        }

        iterations++;

        for (int i = 0; i < S; i++)
        {
            int rowItems[S] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            int colItems[S] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

            for (int j = 0; j < S; j++)
            {
                tm[i][j] = m[i][j] == 0 ? distrib(gen) : m[i][j];
                tm[j][i] = m[j][i] == 0 ? distrib(gen) : m[j][i];

                int ri = tm[i][j];
                rowItems[ri - 1]++;

                int ci = tm[j][i];
                colItems[ci - 1]++;

                if (colItems[ci - 1] > 1 || rowItems[ri - 1] > 1) {
                    goto refill;
                }
            }
        }

        for (int i = 0; i < S; i++)
        {
            int sectionItems[S] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

            for (int j = 0; j < S; j++)
            {
                int tmi = ((j - (j % 3)) / 3) + (i - (i % 3));
                int tmj = (j % 3) + (i % 3) * 3;

                int si = tm[tmi][tmj];
                sectionItems[si - 1]++;

                if (sectionItems[si - 1] > 1) {
                    goto refill;
                }
            }
        }

        break;
    }

    stopThreads.store(true);

    totalIterations += iterations;

    cout << endl;
    setColor(2);
    cout << "Sudoku is solved!" << endl;
    setColor(7);
    cout << "Number of iterations: ";
    setColor(6);
    cout << totalIterations << endl;
    setColor(7);
    printFormattedMatrix(tm, m);
}

void consecutiveBruteForce(int m[S][S], int unknown)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 9);
    int* sequence = new int[unknown];
    int tm[S][S]{};

    for (int i = 0; i < unknown; i++) 
    {
        sequence[i] = 1;
    }

    for (int i = 0; i < S; i++)
    {
        for (int j = 0; j < S; j++)
        {
            tm[i][j] = m[i][j];
        }
    }

    while (!isSudokuSolved(tm))
    {
        for (int x = 0; x < unknown;)
        {
            for (int i = 0; i < S; i++)
            {
                for (int j = 0; j < S; j++)
                {
                    if (m[i][j] == 0)
                    {
                        tm[i][j] = sequence[x];
                        x++;
                    }
                }
            }
        }

        sequence = incrementSequence(sequence, unknown);
    }

    delete[] sequence;

    cout << endl;
    setColor(2);
    cout << "Sudoku is solved!" << endl;
    setColor(7);
    printFormattedMatrix(tm, m);
}

void setRandomZeros(int m[S][S], int n)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 9);

    for (int i = 0; i < n; ++i) {
        int a = distrib(gen) - 1;
        int b = distrib(gen) - 1;

        if (m[a][b] != 0)
        {
            m[a][b] = 0;
        }
        else {
            i--;
        }
    }
}

void setColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

bool isSudokuSolved(int m[S][S])
{
    for (int i = 0; i < S; i++)
    {
        int rowItems[S]{ 0 };
        int colItems[S]{ 0 };

        for (int j = 0; j < S; j++)
        {
            int ri = m[i][j];
            rowItems[ri - 1]++;

            int ci = m[j][i];
            colItems[ci - 1]++;

            if (colItems[ci - 1] > 1 || rowItems[ri - 1] > 1) {
                return false;
            }
        }
    }

    for (int i = 0; i < S; i++)
    {
        int sectionItems[S]{ 0 };

        for (int j = 0; j < S; j++)
        {
            int tmi = ((j - (j % 3)) / 3) + (i - (i % 3));
            int tmj = (j % 3) + (i % 3) * 3;

            int si = m[tmi][tmj];
            sectionItems[si - 1]++;

            if (sectionItems[si - 1] > 1) {
                return false;
            }
        }
    }

    return true;
}

int* incrementSequence(int* s, int l)
{
    int i = 0;

    while (i < l)
    {
        s[i]++;

        if (s[i] > S)
        {
            s[i] = 1;
            i++;
        }
        else
        {
            break;
        }
    }

    return s;
}
