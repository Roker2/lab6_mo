#include "StepThree.h"
#include "Approximate.h"

bool StepThree::taskIsRelevant(const Matrix& A,
							   const Matrix& B,
							   int j0,
							   Matrix& z)
{
	auto Aj0 = A.getColumnAt(j0);
	z = B * Aj0;
	bool isGreaterThenZero = false;
	z.doForMatrix([&isGreaterThenZero](const Matrix& matrix, int i, int j)
	{
		isGreaterThenZero = isGreaterThenZero || Approximate<double>::greater(matrix[i][j], 0.0);
	});
	return isGreaterThenZero;
}
