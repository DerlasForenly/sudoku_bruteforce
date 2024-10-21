#include "Method.h"

double Method::countTime()
{
	chrono::duration<double, milli> duration = end - start;
	return duration.count();
}
