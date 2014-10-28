#include "AllSymbol.hpp"

Array::Array(unsigned line, Symbol *s)
	: StackedSymbol(ARRAY_SET_SYMBOL, line, s), m_tail(0)
{
	// VOID
}

Array::~Array()
{
	delete m_tail; m_tail = 0;
}


void Array::setTail(unsigned line, Symbol *t)
{
	(void) line;
	m_tail = t;
}

Symbol *Array::tail()
{ return m_tail; }
