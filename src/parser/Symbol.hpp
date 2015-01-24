#pragma once

#include <ostream>

class Symbol
{
	public:
		Symbol(char symbol_type, unsigned symbol_line, char *symbol);
		virtual ~Symbol();

		unsigned firstLine() const;
		unsigned lastLine() const;
		unsigned manyComponents() const;
		unsigned getId() const;
		char type() const;

		char *lexema();

	protected:
		unsigned m_many; //< how many others are used to compose
		unsigned m_beginLine; //< line of the first symbol
		unsigned m_endLine; //< line of the last symbol
		char *m_lexema; //< textual representation of the symbol itself

	private:
		char m_type; //< Symbol type
		unsigned m_id; //< unique identifier
		static unsigned m_lastId; //< last identifier generated
};

// It's not a friend operator because it is not necessary
std::ostream& operator<<(std::ostream& os, Symbol *);
