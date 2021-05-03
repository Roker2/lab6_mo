#pragma once

#include <string>
#include <vector>
#include <optional>

#include "global.h"
#include "TokenType.h"
#include "Priority.h"

class Token
{
public:
	Token(const std::string& t,
		  TokenType type = TokenType::Undefined,
		  std::optional<double> value = std::nullopt);

	inline const std::string& getStr() const noexcept { return t; }
	inline TokenType getType() const noexcept { return type; }
	inline Priority getPriority() const noexcept { return priority; }
	inline double getValue() const noexcept { return value.value_or(0.0); }

	static Token parse(std::string& str);
	static void parseTokens(const std::string& str, std::vector<Token>& tokens);

private:
	std::string t;
	TokenType type;
	Priority priority;
	std::optional<double> value;
};
