#include "AllSymbol.hpp"

ConstantExpression::ConstantExpression(unsigned line, char *lex)
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
