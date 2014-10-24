#include "Symbol.hpp"
#include <cstdlib>
#include <cstdio>

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

void Symbol::add(Symbol *right)
{
	fprintf(stderr, "%s:%d: NOT IMPLEMENTED -- Symbol(id=%d,"
					"lexema=|%s|,lines=[%d..%d],components=%d).\n",
					__FILE__, __LINE__, right->getId(),
					(!right->lexema() ? "" : right->lexema()),
					right->firstLine(), right->lastLine(),
					right->manyComponents());
}
