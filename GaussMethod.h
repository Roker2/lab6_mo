#ifndef GAUSSMETHOD_H
#define GAUSSMETHOD_H

#include "Approximate.h"
#include "SquareMatrix.h"

class GaussMethod
{
public:
    GaussMethod() = delete;
    // a - уравнения в виде матрицы
    // y - правая часть уравнения в виде вектора
    static Matrix method(SquareMatrix a, Matrix y);
};

#endif // GAUSSMETHOD_H
