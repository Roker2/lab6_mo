#pragma once

#include <vector>
#include <stack>

#include "CustomException.h"
#include "Func.h"

class FuncFragmentator
{
public:
    static std::vector<FuncPtr> fragmentate(FuncCPtr func);
};
