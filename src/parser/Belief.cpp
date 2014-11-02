#include "AllSymbol.hpp"
#include "Utils.hpp"
#include <algorithm>

Belief::Belief(Symbol *head, Symbol *opt_context)
	: Symbol(BELIEF_TYPE_SYMBOL, head->firstLine(),
			lexema_cat(head->lexema(), NULL)),
	  m_context(opt_context)
{
	if (opt_context)
	{
		m_beginLine = std::min(opt_context->firstLine(), m_beginLine);
		m_endLine = std::max(opt_context->lastLine(), m_endLine);
		m_many += opt_context->manyComponents();
	}
}

Belief::~Belief()
{
	delete m_context; m_context = NULL;
}

Symbol *Belief::context()
{ return m_context; }
