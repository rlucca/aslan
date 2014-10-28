#include "AllSymbol.hpp"

StackedSymbol::StackedSymbol(char t, unsigned l, Symbol *s)
	: Symbol(t, l, s->lexema())
{
	data.push(s);
}

StackedSymbol::~StackedSymbol()
{
	// VOID
}

void StackedSymbol::push(unsigned line, Symbol *s)
{
	(void) line;
	data.push(s);
}

void StackedSymbol::pop()
{ data.pop(); }

Symbol *StackedSymbol::top()
{ return data.top(); }

bool StackedSymbol::empty()
{ return data.empty(); }

unsigned StackedSymbol::size()
{ return data.size(); }
