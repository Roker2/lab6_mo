#pragma once

#include <string>

static constexpr std::string_view digits = "0123456789.";
static constexpr std::string_view variables = "abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"0123456789";
static constexpr std::string_view operators = "+-*/^()";
//constexpr std::string_view allowableChars = ".0123456789+-*/^()";
static constexpr std::string_view allowableActions[] =
{
"sin", "cos", "tg", "ctg", "sqrt",
"abs", "round", "ceil", "floor",
"asin", "acos", "atg", "actg",
"ln", "log"
};

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
