#pragma once

#include "SquareMatrix.h"

class StepSix
{
public:
	StepSix() = delete;
	static SquareMatrix getNewB(int s,
								const SquareMatrix& B,
								const Matrix& z);

private:
    static Matrix getDs(const Matrix& z, const int& s);
};
