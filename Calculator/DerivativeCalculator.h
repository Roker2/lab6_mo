#pragma once

#include <cmath>

#include "CustomException.h"
#include "Property.h"
#include "Func.h"

class DerivativeCalculator
{
public:
	static FuncPtr calculateDerivative(FuncCPtr func, const std::string &var);
	static void calculateDerivative(FuncPtr func, const std::string &var);
};
