#pragma once

#include <string>

struct Property
{
	Property(const std::string& var, double value);
	Property(std::string&& var, double&& value);

	std::string var;
	double value;
};
