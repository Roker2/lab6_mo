#include "DerivativeCalculator.h"


FuncPtr DerivativeCalculator::calculateDerivative(FuncCPtr func, const std::string &var)
{
	if (var.empty())
		throw CustomException("DerivativeCalculator calculateDerivative Func ex: var is empty");
	if (func->tokensPost.size() != 3)
		throw CustomException("DerivativeCalculator calculateDerivative Func ex: func tokens size != 3, func == " + func->getInf());
	if (!(   (func->tokensPost[0].getType() == TokenType::Variable
				|| func->tokensPost[0].getType() != TokenType::Number)
		  && (func->tokensPost[1].getType() == TokenType::Variable
				|| func->tokensPost[1].getType() != TokenType::Number)
		  && (func->tokensPost[2].getType() == TokenType::Operator)))
		throw CustomException("DerivativeCalculator calculateDerivative Func ex: func have wrong tokens, func == " + func->getInf());

	const auto& op = func->tokensPost[2];
	const auto& t1 = func->tokensPost[0],
				t2 = func->tokensPost[1];
	auto f1 = Func::makeFunc(static_cast<std::string>(t1)),
		 f2 = Func::makeFunc(static_cast<std::string>(t2));
	auto f1der = calculateDerivative(t1, var),
		 f2der = calculateDerivative(t2, var);

	switch (op.getStr()[0])
	{
	case '+':
		return f1der + f2der;
	case '-':
		return f1der - f2der;
	case '*':
		return (f1der * f2) + (f1 * f2der);
	case '/':
		return (f1der * f2 - f1 * f2der) / (f2 ^ Func::makeFunc("2"));
	case '^':
		return (f1 ^ f2) * (f2der * ln(f1) + f2 / f1 * f1der);
	default:
		throw CustomException("DerivativeCalculator calculateDerivative Func ex: "
							  "unexpected operator token == " + op.getStr());
	}
}

FuncPtr DerivativeCalculator::calculateDerivative(const Token &t, const std::string &var)
{
	if (var.empty())
		throw CustomException("DerivativeCalculator calculateDerivative Token ex: var is empty");
	switch (t.getType())
	{
	case TokenType::Variable:
		if (t.getStr() == var)
		{
			return Func::makeFunc("1");
		}
		[[fallthrough]];
	case TokenType::Number:
		return Func::makeFunc("0");
	case TokenType::Subfunc:
	{
		if (!t.getSubfunc())
			throw CustomException("Calculator calculate Func ex: invalid subfunc");
		return calculateDerivative(FuncCPtr(t.getSubfunc()), var);
	}
	default:
		throw CustomException("DerivativeCalculator calculateDerivative Token ex: "
							  "unexpected TokenType == "
							  + std::to_string(static_cast<int>(t.getType())));
	}
}
