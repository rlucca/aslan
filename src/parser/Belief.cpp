#include "AllSymbol.hpp"
#include "Utils.hpp"
#include <algorithm>

Belief::Belief(Functor *h, Symbol *opt_context)
	: Symbol(BELIEF_TYPE_SYMBOL, h->firstLine(),
			lexema_cat(h->lexema(), NULL)),
	  m_context(opt_context), m_head(h)
{
	m_many = h->manyComponents();

	if (opt_context)
	{
		m_beginLine = std::min(opt_context->firstLine(), m_beginLine);
		m_endLine = std::max(opt_context->lastLine(), m_endLine);
		m_many += opt_context->manyComponents();
	}
}

Belief::~Belief()
{
	delete m_head; m_head = NULL;
	delete m_context; m_context = NULL;
}

Functor *Belief::head()
{ return m_head; }

Symbol *Belief::context()
{ return m_context; }

std::ostream& operator<<(std::ostream& os, Belief* right)
{
	os << "belief[";
	os << "head(";
	operator<<(os, right->head());
	os << ")";

	if (right->context())
	{
		os << ",context(";
		operator<<(os, right->context());
		os << ")";
	}

	os << "].\n";
	return os;
}
