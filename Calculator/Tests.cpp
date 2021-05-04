#include "Tests.h"

#include "global.h"
#include "Translator.h"
#include "Calculator.h"

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
}
