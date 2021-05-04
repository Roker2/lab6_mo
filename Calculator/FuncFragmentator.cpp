#include "FuncFragmentator.h"

std::vector<FuncPtr> FuncFragmentator::fragmentate(FuncCPtr func)
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
		{
			if (stack.size() < 1)
				throw CustomException("FuncFragmentator fragmentate Action ex: operators count is greater than operands count");
			auto op = stack.top();
			stack.pop();
			auto subfunc = Func::makeFunc();
			subfunc->funcInf = static_cast<std::string>(t)
							   + '(' + static_cast<std::string>(op) + ')';
			subfunc->tokensInf.push_back(t);
			subfunc->tokensInf.push_back(op);

			subfunc->tokensPost.push_back(op);
			subfunc->tokensPost.push_back(t);
			stack.push(Token("subfunc", TokenType::Subfunc, std::nullopt, subfunc));
			fragments.emplace_back(subfunc);
			break;
		}
		case TokenType::Operator:
		{
			if (stack.size() < 2)
				throw CustomException("FuncFragmentator fragmentate Operator ex: operators count is greater than operands count");
			auto op2 = stack.top();
			stack.pop();
			auto op1 = stack.top();
			stack.pop();
			auto subfunc = Func::makeFunc();
			subfunc->funcInf = '(' + static_cast<std::string>(op1) + ' '
							   + static_cast<std::string>(t) + ' '
							   + static_cast<std::string>(op2) + ')';
			subfunc->tokensInf.push_back(op1);
			subfunc->tokensInf.push_back(t);
			subfunc->tokensInf.push_back(op2);

			subfunc->tokensPost.push_back(op1);
			subfunc->tokensPost.push_back(op2);
			subfunc->tokensPost.push_back(t);
			stack.push(Token("subfunc", TokenType::Subfunc, std::nullopt, subfunc));
			fragments.emplace_back(subfunc);
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
