#include "Tests.h"

#include "global.h"
#include "Translator.h"
#include "Calculator.h"

#define TRANSLATOR_TEST(TEST_NUM, FUNC_INF, FUNC_POST_EXPECTED) \
bool translatorTest##TEST_NUM() \
{ \
	Func func(FUNC_INF); \
	PROTECTED(Translator::translate(func);, "Translator test ex: ") \
	if (!func.isComplete()) return false; \
	std::cout << std::string(func) << " --> " << func.getPost() << std::endl; \
	return func.getPost() == FUNC_POST_EXPECTED; \
}

#define CALCULATION_TEST(TEST_NUM, FUNC_INF, FUNC_RESULT_EXPECTED) \
bool calculationTest##TEST_NUM(const std::map<std::string, Property>& props = {}) \
{ \
	Func func(FUNC_INF); \
	PROTECTED(Translator::translate(func);, "calculator test ex: ") \
	if (!func.isComplete()) return false; \
	std::cout << std::string(func) << " == " << func(props) << std::endl; \
	return func.getPost() == FUNC_POST_EXPECTED; \
}

TRANSLATOR_TEST(1, "x1 * 2", "x1 2 * ")
TRANSLATOR_TEST(2, "sin(4 * asd1f * y6z)", "4 asd1f y6z * * sin ")
TRANSLATOR_TEST(3, "x^3 - 3*x + y^3 - 3*y", "x 3 ^ 3 x * y 3 ^ 3 y * - + - ")
TRANSLATOR_TEST(4, "sqrt(x*x+y*y) + 3 * cos(sqrt(x*x+y*y)) + 5",
				"x x * y y * + sqrt 3 x x * y y * + sqrt cos * 5 + + ")
TRANSLATOR_TEST(5, "5 + (-sqrt(1-x^2-(y-abs(x))^2)) * cos(30*((1-x^2-(y-abs(x))^2)))",
				"5 0 1 x 2 ^ y x abs - 2 ^ - - sqrt - 30 1 x 2 ^ y x abs - 2 ^ - - * cos * + ")

void tests()
{
	std::cout << TEST(translatorTest1);
	std::cout << TEST(translatorTest2);
	std::cout << TEST(translatorTest3);
	std::cout << TEST(translatorTest4);
	std::cout << TEST(translatorTest5);
}
