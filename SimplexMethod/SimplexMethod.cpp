#include "SimplexMethod.h"

void SimplexMethod::resolveOptimal(const Matrix& A,
									const Matrix& c,
									std::vector<double>& x,
									std::set<int>& Jb,
									bool& exists)
{
	auto B = StepOne::getBFromA(A, Jb);
	exists = iterationInternal(A, c, B, Jb, x);
}

bool SimplexMethod::iterationInternal(const Matrix& A,
									   const Matrix& c,
									   SquareMatrix& B,
									   std::set<int>& Jb,
									   std::vector<double>& x)
{
	int iteration = 0;
	while (iteration < 100)
	{
		std::cout << iteration << ") x == " << x << " | Jb == " << Jb << std::endl;
		std::set<int> Jn = StepOne::generateJn(A.getN(), Jb);
		int j0 = StepOne::getIndexDeltaJLessThenZero(A, B, c, Jb, Jn);
        //std::cout << j0 << std::endl;
		if (j0 == -1)
			return true;
		Matrix z(0, 0);
		if (!StepThree::taskIsRelevant(A, B, j0, z))
			return false;
        //std::cout << z << std::endl;
		int s;
		int js;
		double theta = StepFour::getTheta(x, z, Jb, s, js);
		StepFive::buildNewX(theta, j0, js, z, Jn, x, Jb);
        //std::cout << x << std::endl;
        //B = StepSix::getNewB(s, B, z);
        B = StepOne::getBFromA(A, Jb);
		iteration++;
	}
	return false;
}
