#pragma once

#include "SquareMatrix.h"

class StepThree
{
public:
	StepThree() = delete;

	static bool taskIsRelevant(const Matrix& A,
							   const Matrix& B,
							   int j0,
							   Matrix &z);
};
