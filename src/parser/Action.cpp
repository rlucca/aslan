#include "AllSymbol.hpp"

Action::Action(unsigned line, Symbol *s)
	: StackedSymbol(ACTION_TYPE_SYMBOL, s)
{
	// VOID
}

Action::~Action()
{
	// VOID
}
