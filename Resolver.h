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
};

#endif // RESOLVER_H
