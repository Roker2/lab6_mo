#ifndef RESOLVER_H
#define RESOLVER_H

#include "Approximate.h"
#include "GaussMethod.h"
#include "Calculator/Func.h"
#include "Calculator/Property.h"
#include "SimplexMethod/SimplexMethod.h"

class Resolver
{
public:
    Resolver() = delete;
    static void resolver(std::vector<FuncPtr>& gFuncs, const Properties& vectorx, FuncCPtr fFunc);
    static double getAlpha(Matrix fVector, Matrix l0, Matrix deltaX);
    static double getT(Matrix vectorXStar, Matrix l0, Matrix deltaX, double fRes, FuncCPtr fFunc, std::vector<FuncPtr> gFuncs, double alpha);
    static Properties getXt(Matrix vectorXStar, Matrix l0, Matrix deltaX, double t, double alpha);
};

#endif // RESOLVER_H
