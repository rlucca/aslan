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
	os << "Parameter("
		<< static_cast<StackedSymbol*>(right)
		<< ")";
	return os;
}
