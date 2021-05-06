#pragma once

#include <cmath>

#include "CustomException.h"
#include "Property.h"
#include "Func.h"

/*
static constexpr std::array<std::string_view, 15> allowableActions =
{
"sin", "cos", "tg", "ctg", "sqrt",
"abs", "round", "ceil", "floor",
"asin", "acos", "atg", "actg",
"ln", "log"
};
*/

/*static const std::array<std::function<FuncPtr(FuncCPtr)>, 1> funcActionsDerivatives =
{
		[](FuncCPtr func){ return nullptr; }
};*/

class DerivativeCalculator
{
public:
	static FuncPtr calculateDerivative(FuncCPtr func, const std::string &var);

	static FuncPtr calculateDerivative(const Token& t, const std::string &var);

private:
	static FuncPtr calculateDerivativeSingle(FuncCPtr func, const std::string &var);
	static FuncPtr calculateDerivativeDouble(FuncCPtr func, const std::string &var);
	static FuncPtr calculateDerivativeTriple(FuncCPtr func, const std::string &var);
};
