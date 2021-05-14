#include "StepSix.h"

SquareMatrix StepSix::getNewB(int s,
							  const SquareMatrix& B,
							  const Matrix& z)
{
    SquareMatrix M(B.getSize());
    for (int i = 0; i < M.getSize(); i++) {
		if (i == s)
			M.setColumnAt(i, getDs(z, s));
        else
			M.setColumnAt(i, Matrix::getEkColumn(M.getSize(), i));
    }
	return M * B;
}

Matrix StepSix::getDs(const Matrix &z, const int& s)
{
    Matrix ds(z.getM(), 1);
    for (int i = 0; i < z.getM(); i++) {
        if (i == s)
            ds[i][0] = 1 / z[s][0];
        else
            ds[i][0] = - z[i][0] / z[s][0];
    }
    return ds;
}
