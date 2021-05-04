#pragma once

#include <map>
#include <stack>
#include <cmath>

#include "CustomException.h"
#include "Property.h"
#include "Func.h"

class Calculator
{
public:
	static double calculate(FuncCPtr func, const Properties& props = {});
};
