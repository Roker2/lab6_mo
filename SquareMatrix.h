#pragma once
#include "Matrix.h"

class SquareMatrix : public Matrix
{
public:
	SquareMatrix() = default;
    SquareMatrix(int size);
    SquareMatrix(int size, const std::vector<std::vector<double>>& data);
	SquareMatrix(const SquareMatrix& other);
	SquareMatrix(const Matrix& other);

	SquareMatrix& operator =(const SquareMatrix& other);
	SquareMatrix& operator =(const Matrix& other);
    SquareMatrix operator *(const SquareMatrix& right) const;	

	SquareMatrix& setToIdentity();

    int getSize() const;

    SquareMatrix inverse(bool& exists) const;

	virtual void resize(int size);
protected:
	virtual void resize(int m, int n);
	virtual int getM() const;
	virtual int getN() const;

	static SquareMatrix getDMatrix(int n, int k, const Matrix& z);

	static double getAlpha(const Matrix& ek,
        const SquareMatrix& b,
		const Matrix& ck);

private:
    static bool inverseInternal(const SquareMatrix& matrix,
        unsigned int iteration,
        SquareMatrix& forwardI,
        SquareMatrix& inversedI,
        std::set<int>& jIndices,
        std::map<int, int>& sIndices);
};

