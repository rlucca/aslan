#pragma once

#include <vector>

class StackedSymbol : public Symbol
{
	public:
		StackedSymbol(char, Symbol*);
		virtual ~StackedSymbol();

		virtual void push(Symbol *);
		virtual void pop();
		virtual Symbol *top(unsigned pos = 0);
		virtual bool empty();
		virtual unsigned size();

	private:
		std::vector<Symbol*> data;
};
