#pragma once

#include <string>

#include "CustomException.h"
#include "Priority.h"
#include "Func.h"

class Translator
{
public:
	static void translate(Func& func);

private:
	static bool bracketsCompensed(const Func& func);

	static Priority getprior(char ii);
};

