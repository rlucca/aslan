#include "AllSymbol.hpp"

Plan::Plan(int trigger_ev, int type_ev, Symbol *functor)
	: Symbol('P', functor->firstLine(), functor->lexema()),
		m_functor(functor), m_context(0), m_action(0)
{ }

Plan* Plan::addContext(Symbol *ctx)
{
	m_context = ctx;
	return this;
}

Plan* Plan::addActions(Symbol *act)
{
	m_action = act;
	return this;
}
