#include "AllSymbol.hpp"

StackedSymbol::StackedSymbol(char t, Symbol *s)
	: Symbol(t, s->firstLine(), s->lexema())
{
	/* we need reset the components because
	   when we push the elemnt it became one again */
	m_many = 0;
	push(s);
}

StackedSymbol::~StackedSymbol()
{
	// VOID
}

void StackedSymbol::push(Symbol *s)
{
	data.push_back(s);
	if (s != NULL)
	{
		m_many += s->manyComponents();
	}
}

void StackedSymbol::pop()
{
	std::vector<Symbol*>::iterator it = data.begin() + data.size() - 1;
	if (*it != NULL)
	{
		m_many -= (*it)->manyComponents();
	}
	data.erase(it);
}

Symbol *StackedSymbol::top(unsigned u)
{
	unsigned int idx = data.size();

	if (idx == 0)
		return NULL;

	if (u > 0)
		idx = u;

	return data[idx - 1];
}

bool StackedSymbol::empty()
{ return data.empty(); }

unsigned StackedSymbol::size()
{ return data.size(); }

std::ostream& operator<<(std::ostream& os, StackedSymbol* right)
{
	if (right == NULL)
		return os;

	os << "StackedSymbols(";
	for (unsigned u = 1; u <= right->size(); u++)
	{
		operator<<(os, right->top(u));

		if (u != right->size())
			os << ",";
	}
	os << ")[number_of_elements(" << right->size() << "),";
	right->print_helpers(os);
	os << "]";
	return os;
}
