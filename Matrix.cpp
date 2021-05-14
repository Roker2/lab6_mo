#include "Matrix.h"

Matrix::Matrix()
	: Matrix(0, 0)
{}

Matrix::Matrix(int m, int n)
	: m(m), n(n)
{
	resize(m, n);
}

Matrix::Matrix(int m, int n, const std::vector<std::vector<double>>& data)
	: m(m), n(n)
{
	resize(m, n);
	doForMatrix([&data](Matrix& matrix, int i, int j)
	{
		matrix.data[i][j] = data[i][j];
	});
}

Matrix::Matrix(const Matrix& other)
{
	operator=(other);
}

Matrix Matrix::getRowAt(unsigned int index) const
{
	Matrix result(1, n);
	for (int j = 0; j < n; j++)
		result[0][j] = data[index][j];
	return result;
}

Matrix Matrix::getColumnAt(unsigned int index) const
{
	Matrix result(m, 1);
	for (int i = 0; i < m; i++)
		result[i][0] = data[i][index];
	return result;
}

void Matrix::setRowAt(unsigned int index, const Matrix& row)
{
	if (n != row.n)
		throw CustomException("Matrix::setRowAt: incompatible sizes");
	for (int j = 0; j < n; j++)
		data[index][j] = row[0][j];
}

void Matrix::setColumnAt(unsigned int index, const Matrix& column)
{
	if (m != column.m)
		throw CustomException("Matrix::setRowAt: incompatible sizes");
	for (int i = 0; i < m; i++)
		data[i][index] = column[i][0];
}

void Matrix::transpose()
{
	std::vector<std::vector<double>> oldData = data;
	resize(n, m);
	doForMatrix([&oldData](Matrix& matrix, int i, int j)
	{
		matrix.data[i][j] = oldData[j][i];
	});
}

bool Matrix::operator==(const Matrix& other) const
{
	return m == other.m
		&& n == other.n
		&& data == other.data;
}

Matrix& Matrix::operator=(const Matrix& other)
{
	if (&other == this)
		return *this;
	m = other.m;
	n = other.n;
	data.clear();
	data = other.data;
	return *this;
}

Matrix Matrix::operator*(const Matrix& right) const
{
	if (n != right.m)
		throw CustomException("Matrix::operator* matrices aren't consistenced");
	Matrix result(m, right.n);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < right.n; j++)
			for (int r = 0; r < n; r++)
				result[i][j] += operator[](i)[r] * right[r][j];
	return result;
}

Matrix Matrix::operator+(const Matrix &right) const
{
    //std::cout << n << " " << right.n << std::endl;
    if (n != right.n)
        throw CustomException("Matrix::operator+ matrices has different n");
    if (m != right.m)
        throw CustomException("Matrix::operator+ matrices has different m");
    Matrix result = *this; // copy current matrix
    for (int i = 0; i < getM(); i++)
        for (int j = 0; j < getN(); j++)
            result[i][j] += right[i][j];
            //std::cout << i << " " << j << std::endl;
    return result;
}

Matrix Matrix::operator-(const Matrix &right) const
{
    //std::cout << n << " " << right.n << std::endl;
    if (n != right.n)
        throw CustomException("Matrix::operator+ matrices has different n");
    if (m != right.m)
        throw CustomException("Matrix::operator+ matrices has different m");
    Matrix result = *this; // copy current matrix
    for (int i = 0; i < getM(); i++)
        for (int j = 0; j < getN(); j++)
            result[i][j] -= right[i][j];
            //std::cout << i << " " << j << std::endl;
    return result;
}

Matrix Matrix::operator*(const double& right) const
{
    Matrix result = *this; // copy current matrix
    for (int i = 0; i < getM(); i++)
        for (int j = 0; j < getN(); j++)
            result[i][j] *= right;
    return result;
}

std::vector<double>& Matrix::operator[](int index)
{
	return data[index];
}

const std::vector<double>& Matrix::operator[](int index) const
{
	return data[index];
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{
	matrix.doForMatrix([&os](const Matrix& matrix, int i, int j)
	{
		os << std::setw(12) << matrix[i][j] << (j == matrix.n - 1 ? '\n' : ' ');
	});
	return os;
}

void Matrix::resize(int m, int n)
{
	data.resize(m);
	for (auto& item : data)
		item.resize(n);
	this->m = m;
	this->n = n;
}

int Matrix::getM() const
{
	return m;
}

int Matrix::getN() const
{
	return n;
}

std::vector<std::vector<double>>& Matrix::getData()
{
	return data;
}

const std::vector<std::vector<double>>& Matrix::getData() const
{
	return data;
}

Matrix Matrix::getEkRow(int m, int k, double value)
{
	Matrix result(1, m);
	result[0][k] = value;
	return result;
}

Matrix Matrix::getEkColumn(int n, int k, double value)
{
	Matrix result(n, 1);
	result[k][0] = value;
	return result;
}

void Matrix::doForMatrix(std::function<void (Matrix &, int, int)> func)
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			func(*this, i, j);
}

void Matrix::doForMatrix(std::function<void (const Matrix &, int, int)> func) const
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			func(*this, i, j);
}
