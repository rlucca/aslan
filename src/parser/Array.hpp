#pragma once

class Array : public StackedSymbol
{
	public:
		Array(Symbol *);
		virtual ~Array();

		void setTail(Symbol *t);
		Symbol *tail();

	protected:
		Symbol *m_tail;
};

std::ostream& operator<<(std::ostream& os, Array* right);
