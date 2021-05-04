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
	static void translate(FuncPtr func);

private:
	static FuncPtr prepareFunc(FuncCPtr func);

	static void translateInternal(FuncPtr func);

	static bool bracketsCompensed(FuncCPtr func);
};

