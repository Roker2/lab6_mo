#include "Calculator.h"

double Calculator::calculate(const Func &func, const std::map<std::string, Property>& props)
{
	if (!func.isComplete())
		throw CustomException("Calculator calculate ex: func is incomplete, func == "
							  + static_cast<std::string>(func));
	std::stack<double> stack;
	for (const auto& t : func.tokensPost)
	{
		switch (t.getType())
		{
		case TokenType::Number:
			stack.push(t.getValue());
			break;
		case TokenType::Variable:
			if (props.count(t.getStr()) == 0)
				throw CustomException("Calculator calculate ex: var" + t.getStr() + " doesn't exist");
			stack.push(props.at(t.getStr()).value);
			break;
		case TokenType::Func:
		{
			if (stack.size() < 1)
				throw CustomException("Calculator calculate Func ex: operators count is greater than operands count");
			auto op = stack.top();
			stack.pop();
			auto funcIndex = std::distance(allowableActions.begin(),
					std::find(allowableActions.begin(), allowableActions.end(), t.getStr()));
			stack.push(funcActions[static_cast<std::size_t>(funcIndex)](op));
			break;
		}
		case TokenType::Operator:
		{
			if (stack.size() < 2)
				throw CustomException("Calculator calculate Operator ex: operators count is greater than operands count");
			auto op2 = stack.top();
			stack.pop();
			auto op1 = stack.top();
			stack.pop();
			auto opIndex = std::distance(operators.begin(),
					std::find(operators.begin(), operators.end(), t.getStr()[0]));
			stack.push(funcOperators[static_cast<std::size_t>(opIndex)](op1, op2));
			break;
		}
		default:
			throw CustomException("Calculator calculate ex:"
								  "unexpected TokenType == "
								  + std::to_string(static_cast<int>(t.getType())));
		}
	}
	if (stack.size() != 1)
		throw CustomException("Calculator calculate ex: stack is "
							  + std::to_string(stack.size()) + " size");
	return stack.top();
}
