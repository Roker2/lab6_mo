#include "CustomException.h"

CustomException::CustomException(const char *message)
	:message(message)
{}

CustomException::~CustomException()
{}

const char *CustomException::what() const noexcept
{
	return message;
}


