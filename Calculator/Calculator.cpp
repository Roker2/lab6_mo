#include "Calculator.h"

double Calculator::calculate(const Func &func, const std::vector<Property> props)
{
	if (!func.isComplete())
		throw CustomException("Calculator calculate ex: func is incomplete, func == "
							  + static_cast<std::string>(func));
}
