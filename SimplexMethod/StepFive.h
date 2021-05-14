#pragma once

#include "SquareMatrix.h"

class StepFive
{
public:
	StepFive() = delete;

	static void buildNewX(double theta,
						  int j0,
						  int js,
						  const Matrix& z,
						  const std::set<int> &Jn,
						  std::vector<double> &x,
						  std::set<int> &Jb);
};
