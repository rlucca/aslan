#pragma once

#include "TriggerEvent.hpp"
#include "EventType.hpp"

class Plan  : public Symbol
{
	public:
		Plan(Trigger *, EventType *, Symbol *functor);
		virtual ~Plan();

		Plan* addContext(Symbol *);
		Plan* addAction(Symbol *);

  protected:
		Symbol *m_functor;
		Symbol *m_context;
		Symbol *m_action;
		Trigger *m_trigger;
		EventType *m_about;
};
