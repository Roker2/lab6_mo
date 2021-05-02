#include "Func.h"
#include "Calculator.h"

Func::Func(const std::string& str)
	: funcInf(str)
{}

double Func::operator()(const std::vector<Property> props)
{
	return Calculator::calculate(*this, props);
}

Func::operator std::string() const noexcept
{
	return funcInf;
}
