#include "AllSymbol.hpp"

Parameter::Parameter(unsigned line, Symbol *s)
	: StackedSymbol(PARAMETER_SYMBOL, s)
{
	// VOID
}

Parameter::~Parameter()
{
	// VOID
}
