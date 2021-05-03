#ifndef RESOLVER_H
#define RESOLVER_H

#include "Appxomate.h"
#include "GaussMethod.h"
#include "Calculator/Tests.h"
#include "Calculator/Func.h"
#include "Calculator/Translator.h"
#include "Calculator/Property.h"

class Resolver
{
public:
    Resolver() = delete;
    static void resolver(std::vector<Func>& gfuncs, const Properties& vectorx);
};

#endif // RESOLVER_H
