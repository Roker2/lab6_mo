#pragma once

#include <iostream>

#define TEST(x) ((x() == true) \
		? "test completed " + std::string(#x) + '\n' \
		: "test failed    " + std::string(#x) + '\n' )

void tests();
