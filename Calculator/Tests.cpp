#include "Tests.h"

#include "global.h"
#include "Translator.h"
#include "Calculator.h"

#define TEST(x) ((x() == true) \
		? "test completed " + std::string(#x) + '\n' \
		: "test failed    " + std::string(#x) + '\n' )

#define TRANSLATOR_TEST(TEST_NUM, FUNC_INFIX, FUNC_POST_EXPECTED) \
bool translatorTest##TEST_NUM() \
{ \
	FuncPtr func = Func::makeFunc(FUNC_INFIX); \
	if (!func->isComplete()) return false; \
	std::cout << static_cast<std::string>(*func) << " --> " << func->getPost() << std::endl; \
	return func->getPost() == FUNC_POST_EXPECTED; \
}

#define CALCULATION_TEST(TEST_NUM, REAL_ERROR, FUNC_INFIX, \
		FUNC_RESULT_EXPECTED, FUNC_PROPS) \
bool calculationTest##TEST_NUM() \
{ \
	FuncPtr func = Func::makeFunc(FUNC_INFIX); \
	if (!func->isComplete()) return false; \
	auto result = func->calculate(FUNC_PROPS); \
	std::cout << static_cast<std::string>(*func) << " == " << result \
			  << ", expected == " << FUNC_RESULT_EXPECTED << std::endl; \
	return std::abs(result - FUNC_RESULT_EXPECTED) < REAL_ERROR; \
}

#define FRAGMENTATION_TEST(TEST_NUM, FUNC_INFIX, SUBFUNC_COUNT_EXPECTED) \
bool fragmentationTest##TEST_NUM() \
{ \
	FuncPtr func = Func::makeFunc(FUNC_INFIX); \
	if (!func->isComplete()) return false; \
	std::vector<FuncPtr> subfuncs = func->fragmentate(); \
	std::cout << FUNC_INFIX << " | expected " << SUBFUNC_COUNT_EXPECTED \
			  << " fragments" << std::endl; \
	for (unsigned int i = 0; i < subfuncs.size(); i++) \
		std::cout << i + 1 << ": " << static_cast<std::string>(*(subfuncs[i])) << std::endl; \
	return subfuncs.size() == SUBFUNC_COUNT_EXPECTED; \
}

#define OPERATORS_TEST(TEST_NUM, FUNC_INFIX1, FUNC_INFIX2, OP, FUNC_POST_EXPECTED) \
bool operatorsTest##TEST_NUM() \
{ \
	FuncPtr func1 = Func::makeFunc(FUNC_INFIX1); \
	FuncPtr func2 = Func::makeFunc(FUNC_INFIX2); \
	if (!func1->isComplete()) return false; \
	if (!func2->isComplete()) return false; \
	auto result = func1 OP func2; \
	std::cout << '\t' << FUNC_INFIX1 << "  " << #OP << "  " << FUNC_INFIX2 << std::endl; \
	std::cout << "\tresult ==   " << result->getPost() << std::endl; \
	std::cout << "\texpected == " << FUNC_POST_EXPECTED << std::endl; \
	return result->getPost() == FUNC_POST_EXPECTED; \
}

TRANSLATOR_TEST(0, "a + b - c + d", "a b + c - d + ")
TRANSLATOR_TEST(1, "x1 * 2", "x1 2 * ")
TRANSLATOR_TEST(2, "sin(4 * asd1f * y6z)", "4 asd1f * y6z * sin ")
TRANSLATOR_TEST(3, "x^3 - 3*x + y^3 - 3*y", "x 3 ^ 3 x * - y 3 ^ + 3 y * - ")
TRANSLATOR_TEST(4, "sqrt(x*x+y*y) + 3 * cos(sqrt(x*x+y*y)) + 5",
				"x x * y y * + sqrt 3 x x * y y * + sqrt cos * + 5 + ")
TRANSLATOR_TEST(5, "5 + (-sqrt(1-x^2-(y-abs(x))^2)) * cos(30*((1-x^2-(y-abs(x))^2)))",
				"5 0 1 x 2 ^ - y x abs - 2 ^ - sqrt - 30 1 x 2 ^ - y x abs - 2 ^ - * cos * + ")

CALCULATION_TEST(1, 0.1, "x1*5 - 2", 19.5,
				 (Properties{{"x1", 4.3}}))
CALCULATION_TEST(2, 0.1, "tg(4 * asd1f * y6z) + 1", -1.394715716,
				 (Properties{{"asd1f", 5.3}, {"y6z", -0.5}}))
CALCULATION_TEST(3, 0.1, "x^2.3 + 5*x - y^3.7 + 4*y", 141.641826487,
				 (Properties{{"x", 7.5}, {"y", 0.3}}))
CALCULATION_TEST(4, 0.1, "7 + (-sqrt(1-x^2-y+(y-abs(x))^4)) * cos(27*((1-x^2+(y-abs(x))^2)))",
				 27.197, (Properties{{"x", 1.7}, {"y", 7.3}}))

FRAGMENTATION_TEST(1, "x^3 - 3*x + y^3 - 3*y", 7)
FRAGMENTATION_TEST(2, "sin(4 * asd1f * y6z)", 3)
FRAGMENTATION_TEST(3, "5 + (-sqrt(1-x^2-(y-abs(x))^2)) * cos(30*((1-x^2-(y-abs(x))^2)))", 18)

OPERATORS_TEST(1, "x1", "2", ^, "x1 2 ^ ")
OPERATORS_TEST(2, "x^3 - 3*x", "y^3 - 3*y", +, "x 3 ^ 3 x * - y 3 ^ 3 y * - + ")
OPERATORS_TEST(3, "sqrt(x*x+y*y) + 3", "cos(sqrt(x*x+y*y)) + 5", *,
				"x x * y y * + sqrt 3 + x x * y y * + sqrt cos 5 + * ")
OPERATORS_TEST(4, "5 + (-sqrt(1-x^2-(y-abs(x))^2))", "cos(30*((1-x^2-(y-abs(x))^2)))", /,
				"5 0 1 x 2 ^ - y x abs - 2 ^ - sqrt - + 30 1 x 2 ^ - y x abs - 2 ^ - * cos / ")

void tests()
{
	std::cout << TEST(translatorTest0);
	std::cout << TEST(translatorTest1);
	std::cout << TEST(translatorTest2);
	std::cout << TEST(translatorTest3);
	std::cout << TEST(translatorTest4);
	std::cout << TEST(translatorTest5);

	std::cout << TEST(calculationTest1);
	std::cout << TEST(calculationTest2);
	std::cout << TEST(calculationTest3);
	std::cout << TEST(calculationTest4);

	std::cout << TEST(fragmentationTest1);
	std::cout << TEST(fragmentationTest2);
	std::cout << TEST(fragmentationTest3);

	std::cout << TEST(operatorsTest1);
	std::cout << TEST(operatorsTest2);
	std::cout << TEST(operatorsTest3);
	std::cout << TEST(operatorsTest4);
}
