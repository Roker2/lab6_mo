#pragma once

#include <array>
#include <string>
#include <functional>
#include <cmath>

#define PROTECTED(x, ERR_MSG) \
	try\
	{\
		x\
	}\
	catch (const std::exception& ex)\
	{\
		std::cerr << ERR_MSG << ex.what() << std::endl;\
	}\
	catch (...)\
	{\
		std::cerr << ERR_MSG << "..." << std::endl;\
	}

#define PROTECTED_SYNC(x, ERR_MSG) \
	PROTECTED(std::lock_guard{ mutex }; x, ERR_MSG)

static constexpr double PI_2 = 1.57079632679;

static constexpr std::string_view digits = "0123456789.";
static constexpr std::string_view variables = "abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"0123456789";
static constexpr std::string_view operators = "+-*/^()";
static constexpr std::array<std::string_view, 15> allowableActions =
{
"sin", "cos", "tg", "ctg", "sqrt",
"abs", "round", "ceil", "floor",
"asin", "acos", "atg", "actg",
"ln", "log"
};

static const std::array<std::function<double(double,double)>, 5> funcOperators =
{
	[](double op1, double op2) { return op1 + op2; },
	[](double op1, double op2) { return op1 - op2; },
	[](double op1, double op2) { return op1 * op2; },
	[](double op1, double op2) { return op1 / op2; },
	[](double op1, double op2) { return std::pow(op1, op2); },
};

static const std::array<std::function<double(double)>, 15> funcActions =
{
	[](double op) { return std::sin(op); },
	[](double op) { return std::cos(op); },
	[](double op) { return std::tan(op); },
    [](double op) { return std::tan(PI_2 - op); },
	[](double op) { return std::sqrt(op); },
	[](double op) { return std::abs(op); },
	[](double op) { return std::round(op); },
	[](double op) { return std::ceil(op); },
	[](double op) { return std::floor(op); },
	[](double op) { return std::asin(op); },
	[](double op) { return std::acos(op); },
	[](double op) { return std::atan(op); },
    [](double op) { return PI_2 - std::atan(op); },
	[](double op) { return std::log(op); },
	[](double op) { return std::log10(op); },
};
