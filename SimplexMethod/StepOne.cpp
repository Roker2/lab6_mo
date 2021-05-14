#include "StepOne.h"

Matrix StepOne::getU(const Matrix& c, const Matrix& B, const std::set<int>& Jb)
{
    Matrix cb = getCb(c, Jb);
    Matrix u = cb * B;
    return u;
}

SquareMatrix StepOne::getBFromA(const Matrix &A, const std::set<int> &Jb)
{
    bool exists;
    SquareMatrix B = getAb(A, Jb).inverse(exists);
    if (!exists)
        throw CustomException("No inverse matrix");
    return B;
}

SquareMatrix StepOne::getAb(const Matrix& A, const std::set<int>& Jb)
{
    SquareMatrix Ab(A.getM());
    unsigned long i = 0;
    for (int j : Jb) {
		Ab.setColumnAt(i, A.getColumnAt(j));
        i++;
    }
    return Ab;
}

Matrix StepOne::getCb(const Matrix& c, const std::set<int>& Jb)
{
    Matrix cb(1, Jb.size()); // create matrix with 1 row and Jb.size() colums
    unsigned long i = 0;
    for (int j : Jb) {
		cb[0][i] = c[0][j];
        i++;
    }
    return cb;
}

int StepOne::getIndexDeltaJLessThenZero(const Matrix& A,
										const SquareMatrix& B,
										const Matrix& c,
										const std::set<int>& Jb,
										const std::set<int>& Jn)
{
    for (int j : Jn) {
        // u' * Aj is one digit
		double deltaJ = (getU(c, B, Jb) * A.getColumnAt(j)).getRowAt(0)[0][0] - c[0][j];
        // it is step two, but better to check it here
        if (deltaJ < 0)
            return j;
    }
    return -1;
}

std::set<int> StepOne::generateJn(int n, const std::set<int>& Jb)
{
    std::set<int> Jn;
    for (int i = 0; i < n; i++) {
        if (!Jb.count(i)) {
            Jn.insert(i);
        }
    }
    return Jn;
}
