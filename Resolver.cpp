#include "Resolver.h"

void Resolver::resolver(std::vector<Func>& gfuncs, const Properties& vectorx)
{
    std::vector<bool> activeFuncs;
    for (size_t i = 0; i < gfuncs.size(); i++) {
        Translator::translate(gfuncs[i]);
        double res = gfuncs[i](vectorx);
        if(Approximate<double>::lessEqual(res, 0))
            // если ограничение работает как равенство, то ограничение активное
            if(Approximate<double>::equal(res, 0))
                activeFuncs.push_back(true);
            // в противном случае неактивное
            else
                activeFuncs.push_back(false);
        else {
            std::cout << "x is invalid plan" << std::endl;
            return;
        }
    }

    const int n = 3; // TODO: replace it
    Matrix fVector(1, n, {{0, 0, 3}});
    fVector.transpose();
    for (int i = 0; i < n; i++)
        fVector[i][0] *= -1;

    std::cout << fVector << std::endl;

    std::vector<Matrix> gVectors = {
        Matrix(1, n, {{2, 0, 2}}),
        Matrix(1, n, {{0, -1, 1}}),
        Matrix(1, n, {{-1, 0, 0}}),
    };
    for (size_t i = 0; i < gVectors.size(); i++) {
        gVectors[i].transpose();
        std::cout << gVectors[i] << std::endl;
    }

    SquareMatrix A(n);

    for (size_t i = 0; i < gVectors.size(); i++)
        for (int j = 0; j < n; j++) {
            A[j][i] = gVectors[i][j][0];
        }

    std::cout << A << std::endl;

    Matrix lambdasVector = GaussMethod::method(A, fVector);

    std::cout << lambdasVector << std::endl;
    for (int i = 0; i < n; i++)
        if (Approximate<double>::less(lambdasVector[i][0], 0)) {
            std::cout << "lambda" << i << " is negative, vector x is not optimal" << std::endl;
            return;
        }
    std::cout << "vector x is optimal" << std::endl;
}
