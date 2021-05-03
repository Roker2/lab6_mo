#include "Func.h"
#include "Translator.h"
#include "Calculator.h"
#include "DerivativeCalculator.h"

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
	PROTECTED(Translator::translate(*this);, "Func retranslate ex:")
}

Func Func::derivative() const noexcept
{
	PROTECTED(return DerivativeCalculator::calculateDerivative(*this);, "Func derivative ex:")
	return Func();
}

void Func::makeDerivative() noexcept
{
	PROTECTED(DerivativeCalculator::calculateDerivative(*this);, "Func derivative ex:")
}

double Func::operator()(const Properties& props)
{
	return Calculator::calculate(*this, props);
}

Func::operator std::string() const noexcept
{
	return funcInf;
}
