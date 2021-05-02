#pragma once

enum class Priority : signed char
{
	Var = -1,
	Bracket = 1,
	Addiction = 2,
	Multiplication = 3,
	Power = 4,
	Func = 5
};
