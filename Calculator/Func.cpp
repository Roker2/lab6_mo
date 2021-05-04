#include "Func.h"
#include "Translator.h"
#include "Calculator.h"
#include "FuncFragmentator.h"
#include "DerivativeCalculator.h"

Func::Func(const std::string& funcInf)
	: funcInf(funcInf)
{}

FuncPtr Func::makeFunc(const std::string &funcInf) noexcept
{
	Func temp(funcInf);
	auto func = std::make_shared<Func>(std::move(temp));
    func->retranslate();
    return func;
}

FuncPtr Func::makeFunc(FuncCPtr func) noexcept
{
	if (!func)
        return nullptr;
	return std::make_shared<Func>(*func);
}

const std::string &Func::getInf() const noexcept
{
	return funcInf;
}

std::string Func::getPost() const noexcept
{
	std::string result;
	for (const auto& t : tokensPost)
		result += static_cast<std::string>(t) + " ";
	return result;
}

void Func::retranslate() noexcept
{
	tokensInf.clear();
	tokensPost.clear();
	if (!funcInf.empty())
		PROTECTED(Translator::translate(shared_from_this());, "Func retranslate ex: ")
}

FuncPtr Func::derivative(const std::string &var) const noexcept
{
	PROTECTED(return DerivativeCalculator::calculateDerivative(shared_from_this(), var);, "Func derivative ex: ")
	return nullptr;
}

void Func::setDerivative(const std::string &var) noexcept
{
	PROTECTED(DerivativeCalculator::calculateDerivative(shared_from_this(), var);, "Func derivative ex: ")
}

double Func::calculate(const Properties &props) const noexcept
{
    PROTECTED(return Calculator::calculate(shared_from_this(), props);, "Func calculate ex: ")
    return 0.0;
}

std::vector<FuncPtr> Func::fragmentate() const noexcept
{
    PROTECTED(return FuncFragmentator::fragmentate(shared_from_this());, "Func fragmentate ex: ")
    return {};
}

double Func::operator()(const Properties& props) const noexcept
{
	return calculate(props);
}

Func::operator std::string() const noexcept
{
	return funcInf;
}
