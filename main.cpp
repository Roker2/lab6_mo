#include <iostream>
#include <vector>

#include "Resolver.h"
#include "Calculator/Tests.h"
#include "Calculator/Func.h"
#include "Calculator/Property.h"

using namespace std;

int main()
{
    tests();
    Properties vectorx{{"x1", 1}, {"x2", 1}, {"x3", 1}};
    /*std::vector<Func> gfuncs{
        Func("x1 ^ 2 + x3 ^ 2 - 2"),
        Func("x3 - x2"),
        Func("-x1 + 1"),
    };
    Matrix fVector(1, 3, {{0, 0, 3}});
    */
    std::vector<Func> gfuncs{
        Func("(x1 - 2) ^ 2 + (x3 - 2) ^ 2 - 2"),
        Func("-x2 + 1"),
        Func("x1 + x2 + x3 - 10"),
    };
    Matrix fVector(1, 3, {{4, 4, 4}});

    fVector.transpose();
    Resolver::resolver(gfuncs, vectorx, fVector);
    return 0;
}
