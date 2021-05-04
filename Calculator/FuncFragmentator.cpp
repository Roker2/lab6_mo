#include "FuncFragmentator.h"

std::vector<FuncPtr> FuncFragmentator::fragmentate(FuncPtr func)
{
	if (!func || !func->isComplete())
		throw CustomException("FuncFragmentator fragmentate ex: func is incomplete, func == "
							  + static_cast<std::string>(*func));
	std::vector<FuncPtr> fragments;
	std::stack<Token> stack;
	for (unsigned int i = 0; i < func->tokensPost.size(); i++)
	{
		auto& t = func->tokensPost[i];
		switch (t.getType())
		{
		case TokenType::Subfunc:
			[[fallthrough]];
		case TokenType::Number:
			[[fallthrough]];
		case TokenType::Variable:
			stack.push(t);
			break;
		case TokenType::Action:
		case TokenType::Operator:
		{
			if (stack.size() < 2)
				throw CustomException("FuncFragmentator fragmentate ex: operators count is greater than operands count");
			auto op2 = stack.top();
			stack.pop();
			auto op1 = stack.top();
			stack.pop();
			auto subfunc = Func::makeFunc();
			subfunc->funcInf = static_cast<std::string>(op1) + ' '
							   + static_cast<std::string>(t) + ' '
							   + static_cast<std::string>(op2);
			subfunc->tokensInf.push_back(op1);
			subfunc->tokensInf.push_back(t);
			subfunc->tokensInf.push_back(op2);

			subfunc->tokensPost.push_back(op1);
			subfunc->tokensPost.push_back(op2);
			subfunc->tokensPost.push_back(t);
			stack.push(Token("", TokenType::Subfunc, std::nullopt, subfunc));
			break;
		}
		default:
			throw CustomException("FuncFragmentator fragmentate ex: "
								  "unexpected TokenType == "
								  + std::to_string(static_cast<int>(t.getType())));
		}
	}
	return fragments;
}
