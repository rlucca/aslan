#include "AllSymbol.hpp"

StackedSymbol::StackedSymbol(char t, Symbol *s)
	: Symbol(t, s->firstLine(), s->lexema())
{
	push(s);
}

StackedSymbol::~StackedSymbol()
{
	// VOID
}

void StackedSymbol::push(Symbol *s)
{
	data.push(s);
}

void StackedSymbol::pop()
{ data.pop(); }

Symbol *StackedSymbol::top()
{ return (empty()) ? NULL : data.top(); }

bool StackedSymbol::empty()
{ return data.empty(); }

unsigned StackedSymbol::size()
{ return data.size(); }
