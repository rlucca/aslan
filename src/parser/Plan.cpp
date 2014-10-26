#include "AllSymbol.hpp"

Plan::Plan(int trigger_ev, EventType *type_ev, Symbol *functor)
	: Symbol('P', functor->firstLine(), functor->lexema()),
		m_functor(functor), m_context(0), m_action(0),
		m_about(type_ev)
{ }

Plan::~Plan()
{
	delete m_functor;
	delete m_context;
	delete m_action;
	delete m_about;
}

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
