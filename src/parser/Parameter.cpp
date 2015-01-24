#include "AllSymbol.hpp"

Parameter::Parameter(Symbol *s)
	: StackedSymbol(PARAMETER_SYMBOL, s)
{
	// VOID
}

Parameter::~Parameter()
{
	// VOID
}

std::ostream& operator<<(std::ostream& os, Parameter* right)
{
	return operator<<(os, static_cast<StackedSymbol*>(right));
}
