#include <iostream>
#include <vector>

#include "Resolver.h"
#include "Calculator/Tests.h"
#include "Calculator/Func.h"
#include "Calculator/Property.h"

using namespace std;

int main()
{
    //tests();
    Properties vectorx{{"x1", 1}, {"x2", 1}, {"x3", 1}};
    /*std::vector<FuncPtr> gfuncs{
        Func("x1 ^ 2 + x3 ^ 2 - 2"),
        Func("x3 - x2"),
        Func("-x1 + 1"),
    };
    Func fFunc("x1 ^ 2 - 2 * x1 * x2 + x2 ^ 2 + x3 ^ 2");*/
    std::vector<FuncPtr> gfuncs{
        Func::makeFunc("(x1 - 2) ^ 2 + (x3 - 2) ^ 2 - 2"),
        Func::makeFunc("-x2 + 1"),
        Func::makeFunc("x1 + x2 + x3 - 10"),
    };
    FuncCPtr fFunc = Func::makeFunc("x1 ^ 2 + 2 * x1 * x2 + x2 ^ 2 + 2 * x3 ^ 2");

    Resolver::resolver(gfuncs, vectorx, fFunc);
    return 0;
}
