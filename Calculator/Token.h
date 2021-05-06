#pragma once

#include <string>
#include <vector>
#include <optional>
#include <memory>

#include "global.h"
#include "TokenType.h"
#include "Priority.h"

class Token
{
	using FuncPtr = std::shared_ptr<class Func>;
	using FuncCPtr = std::shared_ptr<const class Func>;
public:
	Token(const std::string& t,
		  TokenType type = TokenType::Undefined,
		  std::optional<double> value = std::nullopt,
		  FuncPtr subfuncPtr = nullptr);

	inline const std::string& getStr() const noexcept { return t; }
	inline TokenType getType() const noexcept { return type; }
	inline Priority getPriority() const noexcept { return priority; }
	inline double getValue() const noexcept { return value.value_or(0.0); }
	inline FuncPtr getSubfunc() const noexcept { return subfuncPtr; }

	static Token parse(std::string& str);
	static void parseTokens(const std::string& str, std::vector<Token>& tokens);

	operator std::string() const noexcept;

private:
	std::string t;
	TokenType type;
	Priority priority;
	std::optional<double> value;
	std::shared_ptr<Func> subfuncPtr;
};
