#pragma once

#include <vector>
#include <stack>
#include <string>
#include <algorithm>

#include "global.h"
#include "CustomException.h"
#include "Priority.h"
#include "Func.h"

class Translator
{
public:
	static void translate(Func& func);

private:
	static Func prepareFunc(const Func& func);

	static void translateInternal(Func& func);

	static bool bracketsCompensed(const Func& func);
};

