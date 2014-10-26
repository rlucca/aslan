#pragma once

#include "TriggerEvent.hpp"
#include "EventType.hpp"

class Plan  : public Symbol
{
	public:
		Plan(int trigger_ev, EventType *, Symbol *functor);
		virtual ~Plan();

		Plan* addContext(Symbol *);
		Plan* addActions(Symbol *);

  protected:
		Symbol *m_functor;
		Symbol *m_context;
		Symbol *m_action;
		EventType *m_about;
};
