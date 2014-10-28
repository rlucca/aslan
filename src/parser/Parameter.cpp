#include "AllSymbol.hpp"

Parameter::Parameter(unsigned line, Symbol *s)
	: StackedSymbol(PARAMETER_SYMBOL, line, s)
{
	// VOID
}

Parameter::~Parameter()
{
	// VOID
}
