#include "AllSymbol.hpp"
#include <cstdlib>

unsigned Symbol::m_lastId = 0;

Symbol::Symbol(char symbol_type, unsigned symbol_line, char *symbol)
	: m_type(symbol_type),
	  m_id(++m_lastId),
	  m_many(1),
	  m_beginLine(symbol_line), m_endLine(symbol_line),
	  m_lexema(symbol)
{
	// EMPTY
}

Symbol::~Symbol()
{ free(m_lexema); }

unsigned Symbol::firstLine() const
{ return m_beginLine; }

unsigned Symbol::lastLine() const
{ return m_endLine; }

unsigned Symbol::manyComponents() const
{ return m_many; }

unsigned Symbol::getId() const
{ return m_id; }

char Symbol::type() const
{ return m_type; }

char *Symbol::lexema()
{ return m_lexema; }

std::ostream& operator<<(std::ostream& os, Symbol* right)
{
	os << "Symbol(lexema=\""
		<< (!right->lexema() ? "" : right->lexema())
		<< "\",lines=[" << right->firstLine()
		<< "," << right->lastLine() << "],components="
		<< right->manyComponents() << ",id=" << right->getId()
		<< ",type='" << right->type() << "')";
	return os;
}
