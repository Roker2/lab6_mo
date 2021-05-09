#include "DerivativeCalculator.h"

FuncPtr DerivativeCalculator::calculateDerivative(FuncCPtr func, const std::string &var)
{
	if (var.empty())
		throw CustomException("DerivativeCalculator calculateDerivative Func ex: var is empty");
	if (!func)
		throw CustomException("DerivativeCalculator calculateDerivative Func ex: null func");

	switch (func->tokensPost.size())
	{
	case 1:
		return calculateDerivativeSingle(func, var);
	case 2:
		return calculateDerivativeDouble(func, var);
	case 3:
		return calculateDerivativeTriple(func, var);
	default:
		throw CustomException("DerivativeCalculator calculateDerivative Func ex: "
							  "wrong func tokens size == " + std::to_string(func->tokensPost.size())
							  + ", func == " + func->getInf());
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

FuncPtr DerivativeCalculator::calculateDerivativeSingle(FuncCPtr func, const std::string &var)
{
	return calculateDerivative(func->tokensPost[0], var);
}

FuncPtr DerivativeCalculator::calculateDerivativeDouble(FuncCPtr func, const std::string &var)
{
	if (!(   func->tokensPost[0].isOperand()
		  && func->tokensPost[1].isAction()))
		throw CustomException("DerivativeCalculator calculateDerivativeDouble Func ex: "
							  "func have wrong tokens, func == " + func->getInf());

	const auto& act = func->tokensPost[1];
	const auto& t = func->tokensPost[0];
	auto f = Func::makeFunc(static_cast<std::string>(t));
	auto fder = calculateDerivative(t, var);

	throw CustomException("DerivativeCalculator calculateDerivativeDouble ex: "
						  "unsupported actions");
}

FuncPtr DerivativeCalculator::calculateDerivativeTriple(FuncCPtr func, const std::string &var)
{
	if (!(   func->tokensPost[0].isOperand()
		  && func->tokensPost[1].isOperand()
		  && func->tokensPost[2].isOperator()))
		throw CustomException("DerivativeCalculator calculateDerivativeTriple Func ex: "
							  "func have wrong tokens, func == " + func->getInf());

	const auto& op = func->tokensPost[2];
	const auto& t1 = func->tokensPost[0],
				t2 = func->tokensPost[1];
	auto f1 = Func::makeFunc(static_cast<std::string>(t1)),
		 f2 = Func::makeFunc(static_cast<std::string>(t2));
	auto f1der = calculateDerivative(t1, var),
		 f2der = calculateDerivative(t2, var);

	if (t1.getType() == TokenType::Number && t2.getType() == TokenType::Number)
		return Func::makeFunc("0");

	switch (op.getStr()[0])
	{
	case '+':
		return f1der + f2der;
	case '-':
		return f1der - f2der;
	case '*':
	{
		if (t1.getType() == TokenType::Number)
			return f1 * f2der;
		if (t2.getType() == TokenType::Number)
			return f1der * f2;
		else
			return (f1der * f2) + (f1 * f2der);
	}
	case '/':
	{
		if (t2.getType() == TokenType::Number)
			return f1der / f2;
		else
			return (f1der * f2 - f1 * f2der) / (f2 ^ Func::makeFunc("2"));
	}
	case '^':
	{
		if (t1.getType() == TokenType::Number)
			return (f1 ^ f2) * ln(f1) * f2der;
		else if (t2.getType() == TokenType::Number)
			return (f1 ^ f2) * f2 / f1 * f1der;
		else
			return (f1 ^ f2) * (f2der * ln(f1) + f2 / f1 * f1der);
	}
	default:
		throw CustomException("DerivativeCalculator calculateDerivativeTriple Func ex: "
							  "unexpected operator token == " + op.getStr());
	}
}
