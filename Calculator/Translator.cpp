#include "Translator.h"

void Translator::translate(Func &func)
{

}

bool Translator::bracketsCompensed(const Func& func)
{
	int opened=0, closed=0;
	for (const auto& ch : func.funcInf)
	{
		if (ch == '(')
			opened++;
		else if (ch == ')')
			closed++;

		if (closed > opened)
			return false;
	}
	return opened == closed;
}

Priority Translator::getprior(char ii)//получить приоритет символа-оператора действия
{
	switch (ii)
	{
	case '(':
	case ')': return Priority::Bracket;
	case '-':
	case '+': return Priority::Addiction;

	case '*':
	case '/': return Priority::Multiplication;
	case '^': return Priority::Power;

	case 's':
	case 'c':
	case 'p':
	case 'g':
	case 'q':

	case 'a':
	case 'r':
	case 'l':
	case 'f':

	case 'v':
	case 'b':
	case 'i':
	case 'm':

	case 'n':
	case 'u': return Priority::Func;

	default: return Priority::Var;
	}
}
