#include "Func.h"
#include "Translator.h"
#include "Calculator.h"

Func::Func(const std::string& funcInf)
	: funcInf(funcInf)
{
	Translator::translate(*this);
}

std::string Func::getPost() const noexcept
{
	std::string result;
	for (const auto& t : tokensPost)
		result += t.getStr() + " ";
	return result;
}

void Func::retranslate() noexcept
{
	tokensPost.clear();
	Translator::translate(*this);
}

double Func::operator()(const Properties& props)
{
	return Calculator::calculate(*this, props);
}

Func::operator std::string() const noexcept
{
	return funcInf;
}
