#pragma once

class Functor : public Symbol
{
 public:
	Functor(unsigned identifier_line, char *identifier,
			Symbol* ps = 0, Symbol* as = 0);
	virtual ~Functor();

	Symbol *parms();
	Symbol *annots();

 protected:
	Symbol *m_parms;
	Symbol *m_annots;
};
