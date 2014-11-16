#include "AllSymbol.hpp"

Action::Action(Symbol *s)
	: StackedSymbol(ACTION_TYPE_SYMBOL, s)
{
	// VOID
}

Action::~Action()
{
	// VOID
}
