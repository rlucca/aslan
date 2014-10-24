#include "AllSymbol.hpp"

ConstantExpression::ConstantExpression(char *lex, unsigned line)
	: Symbol('C', line, lex)
{ }

ConstantExpression::~ConstantExpression()
{ }

