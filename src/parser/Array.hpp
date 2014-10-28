#pragma once

class Array : public StackedSymbol
{
	public:
		Array(unsigned, Symbol *);
		virtual ~Array();

		void setTail(unsigned line, Symbol *t);
		Symbol *tail();

	protected:
		Symbol *m_tail;
};
