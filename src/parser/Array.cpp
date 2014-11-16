#include "AllSymbol.hpp"

Array::Array(unsigned line, Symbol *s)
	: StackedSymbol(ARRAY_SET_SYMBOL, s), m_tail(0)
{
	// VOID
}

Array::~Array()
{
	delete m_tail; m_tail = 0;
}


void Array::setTail(Symbol *t)
{
	m_tail = t;
}

Symbol *Array::tail()
{ return m_tail; }
