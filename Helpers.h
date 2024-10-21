#pragma once
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
#include <vector>
#include <thread>
#include <atomic>

static void setColor(int color);
static void printColored(std::string text, int color);
static void printColored(int number, int color);

class Method;
class Sudoku;
class RandomForce;
class ConsecutiveForce;

static void setColor(int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

static void printColored(std::string text, int color)
{
	setColor(color);
	std::cout << text;
	setColor(7);
}

static void printColored(int number, int color)
{
	setColor(color);
	std::cout << number;
	setColor(7);
}
