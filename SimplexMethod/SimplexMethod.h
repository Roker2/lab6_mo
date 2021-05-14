#pragma once
#include "StepOne.h"
#include "StepThree.h"
#include "StepFour.h"
#include "StepFive.h"
#include "StepSix.h"
#include "SquareMatrix.h"

class SimplexMethod
{
public:
    SimplexMethod() = delete;

	static void resolveOptimal(const Matrix& A,
							   const Matrix& c,
							   std::vector<double> &x,
							   std::set<int> &Jb,
							   bool &exists);
    static std::vector<double> calculateXVector(const Matrix& A,
                                                const std::set<int>& Jb,
                                                const Matrix& b);

private:
	static bool iterationInternal(const Matrix& A,
								  const Matrix& c,
								  SquareMatrix &B,
								  std::set<int>& Jb,
								  std::vector<double>& x);
    static SquareMatrix getBasisMatrix(const Matrix& A,
                                       const std::set<int>& Jb);
};
