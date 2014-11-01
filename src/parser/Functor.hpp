#pragma once

class Functor : public Symbol
{
 public:
	Functor(char *identifier, unsigned identifier_line,
			Symbol* ps = 0, Symbol* as = 0);
	virtual ~Functor();

	Symbol *parms();
	Symbol *annots();

 protected:
	Symbol *m_parms;
	Symbol *m_annots;
};
