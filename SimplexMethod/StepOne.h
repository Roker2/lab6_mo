#pragma once

#include "SquareMatrix.h"

class StepOne
{
public:
	StepOne() = delete;
	static SquareMatrix getBFromA(const Matrix& A, const std::set<int>& Jb);
	/// WARNING: It return index, which need to minus 1, if you want to get element by this index
	static int getIndexDeltaJLessThenZero(const Matrix& A,
										  const SquareMatrix& B,
										  const Matrix& c,
										  const std::set<int> &Jb,
										  const std::set<int> &Jn);
	static std::set<int> generateJn(int n, const std::set<int> &Jb);

private:
	static Matrix getU(const Matrix &c, const Matrix& B, const std::set<int>& Jb);
	static SquareMatrix getAb(const Matrix &A, const std::set<int> &Jb);
	static Matrix getCb(const Matrix &c, const std::set<int>& Jb); // get basis matrix from vector c
};
