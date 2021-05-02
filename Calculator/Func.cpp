#include "Func.h"
#include "Calculator.h"

Func::Func(const std::string& funcInf)
	: funcInf(funcInf)
{}

std::string Func::getPost() const noexcept
{
	std::string result;
	for (const auto& t : tokensPost)
		result += t.getStr() + " ";
	return result;
}

double Func::operator()(const std::map<std::string, Property>& props)
{
	return Calculator::calculate(*this, props);
}

Func::operator std::string() const noexcept
{
	return funcInf;
}
