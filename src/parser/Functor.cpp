#include "AllSymbol.hpp"
#include "Utils.hpp"

Functor::Functor(char *identifier, unsigned identifier_line,
				Symbol* ps, Symbol* as)
	: Symbol(FUNCTOR_SYMBOL, identifier_line,
			// I do not append the meta information
			// in the lexema
			lexema_cat(identifier, (ps)?ps->lexema():NULL)
			), m_parms(ps), m_annots(as)
{ }

Functor::~Functor()
{
	delete m_parms; m_parms = 0;
	delete m_annots; m_annots = 0;
}

Symbol *Functor::parms()
{ return m_parms; }

Symbol *Functor::annots()
{ return m_annots; }
