#pragma once

#include <exception>
#include <string>

class CustomException : public std::exception
{
public:
	CustomException(const char* message);
	CustomException(const std::string& message);
	~CustomException() override;
	const char* what() const noexcept override;
private:
	const std::string message;
};
