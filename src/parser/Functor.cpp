#include "AllSymbol.hpp"
#include "Utils.hpp"

Functor::Functor(unsigned identifier_line, char *identifier,
				Parameter* ps, Array* as)
	: Symbol(FUNCTOR_SYMBOL, identifier_line,
			lexema_cat(identifier, NULL)),
	  m_parms(ps), m_annots(as)
{
	if (m_parms) m_many += m_parms->manyComponents();
	if (m_annots) m_many += m_annots->manyComponents();
}

Functor::~Functor()
{
	delete m_parms; m_parms = 0;
	delete m_annots; m_annots = 0;
}

Parameter *Functor::parms()
{ return m_parms; }

Array *Functor::annots()
{ return m_annots; }

std::ostream& operator<<(std::ostream& os, Functor* right)
{
	os << "functor(\"" << right->lexema() << "\")[";

	right->print_helpers(os);

	if (right->parms())
	{
		os << ",";
		operator<<(os, right->parms());
	}

	if (right->annots())
	{
		os << ",";
		operator<<(os, right->annots());
	}

	os << "]";
	return os;
}
