#include "SimplexMethod.h"

SquareMatrix SimplexMethod::getBasisMatrix(const Matrix& A,
                            const std::set<int>& Jb)
{
    SquareMatrix Ab(Jb.size());
    int i = 0;
    for (const auto& jIndex : Jb)
    {
        Ab.setColumnAt(i, A.getColumnAt(jIndex));
        i++;
    }
    return Ab;
}

std::vector<double> SimplexMethod::calculateXVector(const Matrix& A,
                                     const std::set<int>& Jb,
                                     const Matrix& b)
{
    SquareMatrix Ab = getBasisMatrix(A, Jb);
    bool exists = false;
    SquareMatrix AbInversed = Ab.inverse(exists);
    if (!exists)
        throw CustomException("Ab is singular");
    Matrix x_b(dynamic_cast<const Matrix&>(AbInversed) * b);
    std::vector<double> x;
    x.resize(A.getN(), 0);
    int i = 0;
    for (const auto& jIndex : Jb)
    {
        x[jIndex] = x_b[i][0];
        i++;
    }
    return x;
}

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
