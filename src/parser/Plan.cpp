#include "AllSymbol.hpp"
#include <algorithm>
#include <cstring>

Plan::Plan(Trigger *trigger_ev, EventType *type_ev, Symbol *functor)
	: Symbol(PLAN_TYPE_SYMBOL, functor->firstLine(), strdup(functor->lexema())),
		m_functor(functor), m_context(0), m_action(0),
		m_trigger(trigger_ev), m_about(type_ev)
{
	m_beginLine = std::min(trigger_ev->firstLine(),
							std::min(type_ev->firstLine(), m_beginLine));
	m_endLine = std::max(trigger_ev->lastLine(),
							std::max(type_ev->lastLine(), m_endLine));
}

Plan::~Plan()
{
	delete m_functor;
	delete m_context;
	delete m_action;
	delete m_trigger;
	delete m_about;
}

unsigned char Plan::trigger() const
{
	return (m_trigger) ? m_trigger->triggerType() : '?';
}

unsigned char Plan::about() const
{
	return (m_about) ? m_about->eventAbout() : '?';
}

Plan* Plan::addContext(Symbol *ctx)
{
	if (ctx)
	{
		m_context = ctx;
		m_endLine = std::max(m_context->lastLine(), m_endLine);
	}
	return this;
}

Plan* Plan::addAction(Symbol *act)
{
	if (act)
	{
		m_action = act;
		m_endLine = std::max(m_action->lastLine(), m_endLine);
	}
	return this;
}

Symbol* Plan::context()
{
	return m_context;
}

Symbol* Plan::action()
{
	return m_action;
}
