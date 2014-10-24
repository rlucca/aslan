#pragma once

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
		virtual void add(Symbol *);

	protected:
		char m_type; //< Symbol type
		unsigned m_id; //< unique identifier
		unsigned m_many; //< how many others are used to compose
		unsigned m_beginLine; //< line of the first symbol
		unsigned m_endLine; //< line of the last symbol
		char *m_lexema; //< textual representation of the symbol itself
		static unsigned m_lastId; //< last identifier generated
};
