#pragma once
#include <cmath>

float f(float x)
{
	return 1/x;
}
bool fexists(float x)
{

	if (abs(x) < 0.001)
		return false;
	else
		return true;

}