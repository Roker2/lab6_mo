#include "GaussMethod.h"

Matrix GaussMethod::method(SquareMatrix a, Matrix y)
{
    // m - количество строк матрицы, т. е. количество уравнений
    Matrix x(a.getSize(), 1);
    int k = 0, index;
    double max;
    int n = a.getSize();
    while (k < n) {
        // Поиск строки с максимальным a[i][k]
        max = std::abs(a[k][k]);
        index = k;
        for (int i = k + 1; i < n; i++) {
            if (Approximate<double>::greater(fabs(a[i][k]), max)) {
                max = fabs(a[i][k]);
                index = i;
            }
        }
        if (Approximate<double>::equal(max, 0)) {
            throw CustomException("Cannot to get result");
        }
        for (int j = 0; j < n; j++) {
            double temp = a[k][j];
            a[k][j] = a[index][j];
            a[index][j] = temp;
        }
        double temp = y[k][0];
        y[k][0] = y[index][0];
        y[index][0] = temp;

        // Нормализация уравнений
        for (int i = k; i < n; i++) {
            double temp = a[i][k];
            if (Approximate<double>::equal(fabs(temp), 0))
                continue; // для нулевого коэффициента пропустить
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] / temp;
            y[i][0] = y[i][0] / temp;
            if (i == k)
                continue; // уравнение не вычитать само из себя
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] - a[k][j];
            y[i][0] = y[i][0] - y[k][0];
        }
        k++;
    }

    // обратная подстановка
    for (k = n - 1; k >= 0; k--)
    {
        x[k][0] = y[k][0];
        for (int i = 0; i < k; i++)
            y[i][0] = y[i][0] - a[i][k] * x[k][0];
    }
    return x;
}
