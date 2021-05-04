#include "Priority.h"
#include "global.h"
#include "CustomException.h"

Priority getPriority(const std::string &str)
{
	if (str.empty())
		throw CustomException("getPriority ex: str empty");
	switch (str[0])
	{
	case '(':
	case ')': return Priority::Bracket;
	case '-':
	case '+': return Priority::Addiction;

	case '*':
	case '/': return Priority::Multiplication;
	case '^': return Priority::Power;

	default:
	{
		for (const auto& action : allowableActions)
		{
			if (action == str)
				return Priority::Func;
		}
		return Priority::Var;
	}
	}
}
