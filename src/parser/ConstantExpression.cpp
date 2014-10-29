#include "AllSymbol.hpp"

ConstantExpression::ConstantExpression(char *lex, unsigned line)
	: Symbol(CONSTANT_EXPRESSION_SYMBOL, line, lex)
{ }

ConstantExpression::~ConstantExpression()
{ }

std::ostream& operator<<(std::ostream& os, ConstantExpression *ce)
{
	// Constant Expression is similar to a literal
	os << ce->lexema();
	return os;
}
