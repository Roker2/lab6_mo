#pragma once

#include <vector>

#include "CustomException.h"
#include "Property.h"
#include "Func.h"

class Calculator
{
public:
	static double calculate(const Func& func, const std::vector<Property> props = {});
};
