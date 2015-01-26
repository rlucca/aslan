#include "AllSymbol.hpp"
#include <cstdlib>

unsigned Symbol::m_lastId = 0;

Symbol::Symbol(char symbol_type, unsigned symbol_line, char *symbol)
	: m_many(1),
	  m_beginLine(symbol_line), m_endLine(symbol_line),
	  m_lexema(symbol),
	  m_type(symbol_type),
	  m_id(++m_lastId)
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

void Symbol::print_helpers(std::ostream &os) const
{
	print_lines(os);
	print_components(os);
	print_id(os);
}

void Symbol::print_lines(std::ostream &os) const
{
	os << "lineBegin(" << firstLine() << "),"
		<< "lineEnd(" << firstLine() << "),";
}

void Symbol::print_components(std::ostream &os) const
{
	os << "components(" << manyComponents() << "),";
}

void Symbol::print_id(std::ostream &os) const
{
	os << "id(" << getId() << ")";
}

std::ostream& operator<<(std::ostream& os, Symbol* right)
{
    if (right->type() == BELIEF_TYPE_SYMBOL)
        return operator<<(os, static_cast<Belief*>(right) );
    if (right->type() == FUNCTOR_SYMBOL)
        return operator<<(os, static_cast<Functor*>(right) );

	os << "Symbol("
		<< "lexema(\"" << (!right->lexema() ? "" : right->lexema()) << "\"),";

	right->print_helpers(os);

	os << ","
		<< "type(" << right->type() << ")"
		<< ")";

	return os;
}
