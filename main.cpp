#include <iostream>
#include <vector>

#include "Resolver.h"
#include "Calculator/Tests.h"
#include "Calculator/Func.h"
#include "Calculator/Property.h"

using namespace std;

void testTask1()
{
    std::vector<FuncPtr> gfuncs{
            Func::makeFunc("x1 ^ 2 + x3 ^ 2 - 2"),
            Func::makeFunc("x3 - x2"),
            Func::makeFunc("-x1 + 1"),
        };
    FuncCPtr fFunc = Func::makeFunc("x1 ^ 2 - 2 * x1 * x2 + x2 ^ 2 + x3 ^ 2");
    Properties vectorx{{"x1", 1}, {"x2", 1}, {"x3", 1}};

    Resolver::resolver(gfuncs, vectorx, fFunc);
}

void testTask2()
{
    std::vector<FuncPtr> gfuncs{
            Func::makeFunc("(x1 - 2) ^ 2 + (x3 - 2) ^ 2 - 2"),
            Func::makeFunc("-x2 + 1"),
            Func::makeFunc("x1 + x2 + x3 - 10"),
        };
    FuncCPtr fFunc = Func::makeFunc("x1 ^ 2 + 2 * x1 * x2 + x2 ^ 2 + 2 * x3 ^ 2");
    Properties vectorx{{"x1", 1}, {"x2", 1}, {"x3", 1}};

    Resolver::resolver(gfuncs, vectorx, fFunc);
}

void dimaTask()
{
    std::vector<FuncPtr> gfuncs{
        Func::makeFunc("(x1 + x2) ^ 2 + (x3 - 1) ^ 2 - 5"),
        Func::makeFunc("-2 * x1 + 3 * x2 + x3 ^ 2 - 4"),
        Func::makeFunc("-x1"),
    };
    FuncCPtr fFunc = Func::makeFunc("(x1 - 2 * x2 - x3) ^ 2 + 3 * x1 - 4 * x2 +x3");
    Properties vectorx{{"x1", 0}, {"x2", 1}, {"x3", -1}};

    Resolver::resolver(gfuncs, vectorx, fFunc);
}

int main()
{
    //tests();
    //dimaTask();
    testTask2();
    return 0;
}
