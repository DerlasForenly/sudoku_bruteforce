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

const int S = 9;
const bool DEBUG = false;

static void readMatrixFromFile(const std::string& filename, int m[S][S]);
static void printFormattedMatrix(int m[S][S], int c[S][S]);
static void fullRandBruteForce(int m[S][S]);
static void setZeros(int m[S][S], int n);
static void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

int main() 
{
    int n;
    int m[S][S];
    readMatrixFromFile("solved.txt", m);

    std::cout << "Enter number of unknown items: ";
    setColor(6);
    std::cin >> n;
    setColor(7);
    std::cout << "Chance to generate valid solution: ";
    setColor(6);
    std::cout << 1 / pow(9, n) * 100 << "%" << std::endl;
    setColor(7);
    std::cout << "My speed is ";
    setColor(6);
    std::cout << "~26 681 854";
    setColor(7);
    std::cout << " iterations/second" << std::endl << std::endl;

    setZeros(m, n);
    std::cout << "Sudoku:" << std::endl;
    printFormattedMatrix(m, m);

    auto start = std::chrono::high_resolution_clock::now();
    fullRandBruteForce(m);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Elapsed time: ";
    setColor(6);
    std::cout << duration.count();
    setColor(7);
    std::cout << " milliseconds" << std::endl << std::endl;

    system("pause");
    return 0;
}

static void readMatrixFromFile(const std::string& filename, int m[S][S]) {
    std::ifstream file(filename);

    for (int i = 0; i < S; ++i)
    {
        for (int j = 0; j < S; ++j)
        {
            file >> m[i][j];
        }
    }

    file.close();
}

static void printFormattedMatrix(int m[S][S], int c[S][S]) {
    for (int i = 0; i < S; ++i)
    {
        for (int j = 0; j < S; ++j)
        {
            if (m[i][j] == 0) {
                std::cout << " " << " ";
            }
            else {
                if (m[i][j] != c[i][j]) {
                    setColor(9);
                }

                std::cout << m[i][j] << " ";

                setColor(7);
            }

            if ((j + 1) % 3 == 0 && j < 8)
            {
                setColor(6);
                std::cout << "| ";
                setColor(7);
            }
        }

        std::cout << std::endl;

        if ((i + 1) % 3 == 0 && i < 8)
        {
            setColor(6);
            std::cout << "- - - | - - - | - - -" << std::endl;
            setColor(7);
        }
    }
}

static void fullRandBruteForce(int m[S][S])
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 9);

    long iterations = 0;
    int tm[S][S] = {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    };
    
    while (true)
    {
        refill:
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

    std::cout << std::endl;
    setColor(2);
    std::cout << "Sudoku is solved!" << std::endl;
    setColor(7);
    std::cout << "Number of iterations: ";
    setColor(6);
    std::cout << iterations << std::endl;
    setColor(7);
    printFormattedMatrix(tm, m);
}

static void setZeros(int m[S][S], int n)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 9);

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
