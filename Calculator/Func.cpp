#include "Func.h"
#include "Translator.h"
#include "Calculator.h"
#include "FuncFragmentator.h"
#include "DerivativeCalculator.h"

#define FUNC_OPERATOR(OP) \
FuncPtr operator OP(FuncCPtr f1, FuncCPtr f2) \
{ \
	return Func::makeFunc("(" + f1->getInf() + ") " + std::string(#OP) + " (" + f2->getInf() + ")"); \
}

#define FUNC_ACTION(ACT) \
FuncPtr ACT(FuncPtr f) \
{ \
	return Func::makeFunc(std::string(#ACT) + "(" + f->getInf() + ")"); \
}

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

FuncPtr Func::derivative(const std::string& var) const noexcept
{
	auto subfuncs = fragmentate();
	if (subfuncs.size() == 0)
		return nullptr;
	PROTECTED(return DerivativeCalculator::calculateDerivative(subfuncs.back(), var);, "Func derivative ex: ")
	return nullptr;
}

void Func::setDerivative(const std::string& var) noexcept
{
	auto derivative = Func::derivative(var);
	if (!derivative)
		return;
	this->funcInf = derivative->funcInf;
	this->tokensInf = derivative->tokensInf;
	this->tokensPost = derivative->tokensPost;
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

FUNC_ACTION(sin)
FUNC_ACTION(cos)
FUNC_ACTION(tg)
FUNC_ACTION(ctg)
FUNC_ACTION(sqrt)
FUNC_ACTION(abs)
FUNC_ACTION(round)
FUNC_ACTION(ceil)
FUNC_ACTION(floor)
FUNC_ACTION(asin)
FUNC_ACTION(acos)
FUNC_ACTION(atg)
FUNC_ACTION(actg)
FUNC_ACTION(ln)
FUNC_ACTION(log)

FUNC_OPERATOR(+)
FUNC_OPERATOR(-)
FUNC_OPERATOR(*)
FUNC_OPERATOR(/)
FUNC_OPERATOR(^)
