#pragma once

class Plan  : public Symbol
{
	public:
		Plan(int trigger_ev, int type_ev, Symbol *functor);

		Plan* addContext(Symbol *);
		Plan* addActions(Symbol *);

  protected:
		Symbol *m_functor;
		Symbol *m_context;
		Symbol *m_action;
};
