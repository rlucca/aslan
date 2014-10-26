#include "AllSymbol.hpp"

ConstantExpression::ConstantExpression(char *lex, unsigned line)
	: Symbol(CONSTANT_EXPRESSION_SYMBOL, line, lex)
{ }

ConstantExpression::~ConstantExpression()
{ }

