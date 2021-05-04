#pragma once

#include <vector>
#include <stack>

#include "CustomException.h"
#include "Func.h"

class FuncFragmentator
{
public:
	std::vector<FuncPtr> fragmentate(FuncPtr func);
};
