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
	static double calculate(const Func& func, const std::map<std::string, Property>& props = {});
};
