#pragma once
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
#include <vector>
#include <thread>
#include <atomic>
using namespace std;

static void setColor(int color);
static int random();

template <typename T>
static void printColored(T item, int color);

class Method;
class Sudoku;
class RandomForce;
class ConsecutiveForce;

static void setColor(int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

template <typename T>
static void printColored(T item, int color)
{
	setColor(color);
	cout << item;
	setColor(7);
}

static int random()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distrib(1, 9);

	return distrib(gen);
}
