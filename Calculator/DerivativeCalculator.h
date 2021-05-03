#pragma once

#include <cmath>

#include "CustomException.h"
#include "Property.h"
#include "Func.h"

class DerivativeCalculator
{
public:
	static Func calculateDerivative(const Func& func);
	static void calculateDerivative(Func& func);
};
