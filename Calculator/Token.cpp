#include "Token.h"
#include "Func.h"
#include "Translator.h"

Token::Token(const std::string &t,
			 TokenType type,
			 std::optional<double> value,
			 FuncPtr subfuncPtr)
	: t(t),
	  type(type),
	  priority(::getPriority(this->t)),
	  value(value),
	  subfuncPtr(subfuncPtr)
{}

Token Token::parse(std::string &str)
{
	unsigned int size = 0;
	std::string tokenStr;
	auto type = TokenType::Undefined;
	std::optional<double> value;

	if (str.empty())
		throw CustomException("Token parse ex: empty string");
	///number
	if (auto iter = std::find(digits.begin(), digits.end(), str[0]);
			iter != digits.cend())
	{
		for (unsigned int i = 0; i < str.length(); i++)
			if (std::find(digits.begin(), digits.end(), str[i]) != digits.cend())
				size++;
			else
				break;
		tokenStr = std::string(str.c_str(), size);
		value = std::stod(tokenStr);
		type = TokenType::Number;
	}
	//operator
	else if (auto iter = std::find(operators.begin(), operators.end(), str[0]);
			 iter != operators.cend())
	{
		size = 1;
		tokenStr = str[0];
		type = (str[0] == '(' || str[0] == ')')
				? TokenType::Bracket : TokenType::Operator;
	}
	else
	{
		///Func
		bool isAction = false;
		for (const auto& action : allowableActions)
		{
			if (action == str.substr(0, action.length()))
			{
				isAction = true;
				size = static_cast<unsigned int>(action.length());
				tokenStr = action;
				type = TokenType::Action;
				break;
			}
		}
		///Variable
		if (!isAction)
		{
			for (unsigned int i = 0; i < str.length(); i++)
				if (std::find(variables.begin(), variables.end(), str[i]) != variables.cend())
					size++;
				else
					break;
			tokenStr = std::string(str.c_str(), size);
			type = TokenType::Variable;
		}
	}
	str.erase(0, size);
	return Token(tokenStr, type, value);
}

void Token::parseTokens(const std::string &str, std::vector<Token> &tokens)
{
	auto copy = str;
	while(!copy.empty())
	{
		tokens.push_back(parse(copy));
	}
}

Token::operator std::string() const noexcept
{
	if (type == TokenType::Subfunc && !subfuncPtr.expired())
		return subfuncPtr.lock()->getPost();
	return getStr();
}
