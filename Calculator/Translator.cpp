#include "Translator.h"

void Translator::translate(FuncPtr func)
{
	if (!func)
		throw CustomException("Translator translate ex: null func");
	if (func->isComplete())
		return;
	if (!bracketsCompensed(func))
		throw CustomException("Translator translate ex: brackets aren't compensed: "
							  + static_cast<std::string>(*func));
	auto funcPrepared = prepareFunc(func);
	translateInternal(funcPrepared);
	func->tokensInf = funcPrepared->tokensInf;
	func->tokensPost = funcPrepared->tokensPost;
}

FuncPtr Translator::prepareFunc(FuncCPtr func)
{
	FuncPtr result = std::make_shared<Func>(*func);
	if (result->funcInf[0] == '-')
		result->funcInf = '0' + result->funcInf;
	for (unsigned int i = 1; i < result->funcInf.length(); i++)
	{
		if (result->funcInf[i] == ',')
			result->funcInf[i] = '.';
		if (result->funcInf[i - 1] == '(' && result->funcInf[i] == '-')
			result->funcInf.insert(i, "0");
	}
	while (true)
	{
		auto space = std::find(result->funcInf.begin(), result->funcInf.end(), ' ');
		if (space == result->funcInf.end())
			break;
		result->funcInf.erase(space);
	}
	return result;
}

void Translator::translateInternal(FuncPtr func)
{
	if (!func || func->funcInf.empty())
		throw CustomException("Translator translateInternal ex: func is empty");

	std::stack<Token> stack;
	Token::parseTokens(func->funcInf, func->tokensInf);
	for (const auto& t : func->tokensInf)
	{
		switch (t.getType())
		{
		case TokenType::Number:
		case TokenType::Variable:
			func->tokensPost.push_back(t);
			break;
		case TokenType::Action:
			stack.push(t);
			break;
		case TokenType::Bracket:
			if (t.getStr() == "(")
				stack.push(t);
			else
			{
				while (stack.top().getStr() != "(")
				{
					func->tokensPost.push_back(stack.top());
					stack.pop();
					if (stack.empty())
						throw CustomException("Translator translateInternal"
											  "complaining brackets ex: stack is empty");
				}
				stack.pop();
			}
			break;
		case TokenType::Operator:
			while (!stack.empty()
				   && (stack.top().getType() == TokenType::Action
					   || stack.top().getPriority() > t.getPriority()
					   || (stack.top().getPriority() == t.getPriority()
						   && t.getPriority() != Priority::Power)))
			{
				func->tokensPost.push_back(stack.top());
				stack.pop();
			}
			stack.push(t);
			break;
		default:
			throw CustomException("Translator translateInternal ex:"
								  "unexpected TokenType == "
								  + std::to_string(static_cast<int>(t.getType())));
		}
	}
	while (!stack.empty())
	{
		func->tokensPost.push_back(stack.top());
		stack.pop();
	}
}

bool Translator::bracketsCompensed(FuncCPtr func)
{
	int opened=0, closed=0;
	for (const auto& ch : func->funcInf)
	{
		if (ch == '(')
			opened++;
		else if (ch == ')')
			closed++;

		if (closed > opened)
			return false;
	}
	return opened == closed;
}
