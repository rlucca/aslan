#include "AllSymbol.hpp"

Array::Array(Symbol *s)
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

std::ostream& operator<<(std::ostream& os, Array* right)
{
	return operator<<(os, static_cast<StackedSymbol*>(right));
}
