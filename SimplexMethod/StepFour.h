#pragma once

#include "SquareMatrix.h"

class StepFour
{
public:
	StepFour() = delete;
	static double getTheta(const std::vector<double>& x,
						   const Matrix& z,
						   const std::set<int>& Jb,
						   int &s,
						   int& js);
};

