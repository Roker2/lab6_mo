#pragma once
#include <set>
#include <map>
#include <vector>
#include <iostream>
#include <iomanip>
#include <exception>
#include <functional>
#include <cmath>

#include "CustomException.h"

class Matrix
{
public:
	Matrix();
	Matrix(int m, int n);
	Matrix(int m, int n, const std::vector<std::vector<double>>& data);
	Matrix(const Matrix& other);
	virtual ~Matrix() = default;

	Matrix getRowAt(unsigned int index) const;
	Matrix getColumnAt(unsigned int index) const;

	void setRowAt(unsigned int index, const Matrix& row);
	void setColumnAt(unsigned int index, const Matrix& column);

	void transpose();

	bool operator ==(const Matrix& other) const;
    Matrix& operator =(const Matrix& other);

    Matrix operator *(const Matrix& right) const;
    Matrix operator +(const Matrix& right) const;
    Matrix operator -(const Matrix& right) const;

    Matrix operator *(const double& right) const;

    std::vector<double>& operator [](int index);
    const std::vector<double>& operator [](int index) const;

	friend std::ostream& operator<<(std::ostream& os, const Matrix& matrixBase);

	virtual void resize(int m, int n);
	virtual int getM() const;
	virtual int getN() const;

	void doForMatrix(std::function<void(Matrix&, int, int)> func);
	void doForMatrix(std::function<void(const Matrix&, int, int)> func) const;

protected:
    std::vector<std::vector<double>>& getData();
    const std::vector<std::vector<double>>& getData() const;

public:
	static Matrix getEkRow(int m, int k, double value = 1.0);
	static Matrix getEkColumn(int n, int k, double value = 1.0);

private:
	// strings count
    int m;
	// columns count
    int n;
    std::vector<std::vector<double>> data;
};

template <class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
	os << "( ";
	for (const auto& item : vec)
		os << std::setw(4) << item << ' ';
	os << ")";
	return os;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& set)
{
	os << "{ ";
	for (const auto& item : set)
		os << item << ' ';
	os << "}";
	return os;
}

