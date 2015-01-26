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
	if (m_tail)
		m_many -= m_tail->manyComponents();

	m_tail = t;

	if (m_tail)
		m_many += m_tail->manyComponents();
}

Symbol *Array::tail()
{ return m_tail; }

std::ostream& operator<<(std::ostream& os, Array* right)
{
	os << "Array("
		<< static_cast<StackedSymbol*>(right);

	if (right->tail())
	{
		os << ", tail(" << right->tail() << ")";
	}

	os << ")";
	return os;
}
