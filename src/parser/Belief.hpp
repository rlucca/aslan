#pragma once

class Functor;

class Belief  : public Symbol
{
 public:
	Belief(Functor *head, Symbol *opt_context);
	virtual ~Belief();

	Functor *head();
	Symbol *context();

 protected:
	Symbol *m_context;
	Functor *m_head;
};

std::ostream& operator<<(std::ostream& os, Belief* right);
