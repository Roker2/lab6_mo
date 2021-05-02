#pragma once

enum class TokenType : signed char
{
	Undefined = 0,
	Variable,
	Number,
	Bracket,
	Operator,
	Func
};
