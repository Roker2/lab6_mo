#ifndef RESOLVER_H
#define RESOLVER_H

#include "Appxomate.h"
#include "GaussMethod.h"
#include "Calculator/Func.h"
#include "Calculator/Property.h"

class Resolver
{
public:
    Resolver() = delete;
    static void resolver(std::vector<FuncPtr>& gFuncs, const Properties& vectorx, FuncCPtr fFunc);
};

#endif // RESOLVER_H
