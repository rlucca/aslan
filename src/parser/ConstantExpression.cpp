#include "AllSymbol.hpp"
#include <cstdio>

ConstantExpression::ConstantExpression(char *lex, unsigned line)
	: Symbol('C', line, lex)
{ }

ConstantExpression::~ConstantExpression()
{ }

void ConstantExpression::add(Symbol *)
{
	fprintf(stderr, "%s:%d: not implemented\n", __FILE__, __LINE__);
}
