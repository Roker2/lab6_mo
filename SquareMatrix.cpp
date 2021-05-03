#include "SquareMatrix.h"
#include "Appxomate.h"

SquareMatrix::SquareMatrix(int size)
	: Matrix(size, size)
{}

SquareMatrix::SquareMatrix(int size, const std::vector<std::vector<double>>& data)
	: Matrix(size, size, data)
{}

SquareMatrix::SquareMatrix(const SquareMatrix &other)
	: Matrix(other.getSize(), other.getSize())
{
	operator =(other);
}

SquareMatrix::SquareMatrix(const Matrix &other)
	: Matrix(other.getM(), other.getN())
{
	operator =(other);
}

SquareMatrix &SquareMatrix::operator =(const SquareMatrix &other)
{
	if (&other == this)
		return *this;
	resize(other.getSize());
	getData().clear();
	getData() = other.getData();
	return *this;
}

SquareMatrix& SquareMatrix::operator =(const Matrix& other)
{
	if (&other == this)
		return *this;
	getData().clear();
	resize(std::min(other.getM(), other.getN()));
	doForMatrix([&other](Matrix& matrix, int i, int j)
	{
		matrix[i][j] = other[i][j];
	});
	return *this;
}

SquareMatrix SquareMatrix::operator*(const SquareMatrix& right) const
{
    if (getSize() != right.getSize())
		throw CustomException("multipleMatricesWithCast() matrices aren't consistenced");
    SquareMatrix result(getSize());
    for (int i = 0; i < getSize(); i++)
        for (int j = 0; j < getSize(); j++)
            for (int r = 0; r < getSize(); r++)
                result[i][j] += operator[](i)[r] * right[r][j];
    return result;
}

SquareMatrix& SquareMatrix::setToIdentity()
{
	doForMatrix([](Matrix& matrix, int i, int j)
	{
		matrix[i][j] = (i == j ? 1 : 0);
	});
	return *this;
}

int SquareMatrix::getSize() const
{
    return getM();
}

SquareMatrix SquareMatrix::inverse(bool& exists) const
{
    std::set<int> jIndices;
    for (int i = 0; i < getSize(); i++)
        jIndices.emplace(i);
    SquareMatrix forward(getSize()), inversed(getSize());
    forward.setToIdentity();
    inversed.setToIdentity();
    std::map<int, int> sIndices;
    exists = inverseInternal(*this, 0, forward, inversed, jIndices, sIndices);
    return inversed;
}

void SquareMatrix::resize(int size)
{
	resize(size, size);
}

void SquareMatrix::resize(int m, int n)
{
	Matrix::resize(m, n);
}

int SquareMatrix::getM() const
{
	return Matrix::getM();
}

int SquareMatrix::getN() const
{
	return Matrix::getN();
}

SquareMatrix SquareMatrix::getDMatrix(int size, int k, const Matrix& z)
{
    SquareMatrix result(size);
    result.setToIdentity();
    for (int i = 0; i < size; i++)
        result[i][k] = -1 / z[k][0]
            * (i != k ? z[i][0] : -1);
    return result;
}

double SquareMatrix::getAlpha(const Matrix& ek,
    const SquareMatrix& b,
	const Matrix& ck)
{
    auto result = ek * b * ck;
    return result[0][0];
}

bool SquareMatrix::inverseInternal(const SquareMatrix& matrix,
    unsigned int iteration,
    SquareMatrix& forwardI,
    SquareMatrix& inversedI,
    std::set<int>& jIndices,
    std::map<int, int>& sIndices)
{
    if (jIndices.empty())
    {
        SquareMatrix temp(inversedI);
        for (const auto& [key, value] : sIndices)
            inversedI.setRowAt(key, temp.getRowAt(value));
        return true;
    }
    for (const auto& jIndex : jIndices)
    {
        auto ek = getEkRow(matrix.getSize(), iteration);
        auto alphaJ = getAlpha(ek, inversedI, matrix.getColumnAt(jIndex));
        if (!Approximate<double>::equal(alphaJ, 0.0))
        {
            forwardI.setColumnAt(iteration, matrix.getColumnAt(jIndex));
            inversedI = getDMatrix(matrix.getSize(),
                iteration,
				dynamic_cast<Matrix&>(inversedI) * matrix.getColumnAt(jIndex))
                * inversedI;
            sIndices[jIndex] = iteration;
            jIndices.erase(jIndex);
            return inverseInternal(matrix,
                iteration + 1,
                forwardI,
                inversedI,
                jIndices,
                sIndices);
        }
    }
    return false;
}
