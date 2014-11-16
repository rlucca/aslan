#pragma once

#include <stack>

class StackedSymbol : public Symbol
{
	public:
		StackedSymbol(char, Symbol*);
		virtual ~StackedSymbol();

		virtual void push(unsigned, Symbol *);
		virtual void pop();
		virtual Symbol *top();
		virtual bool empty();
		virtual unsigned size();

	private:
		std::stack<Symbol*> data;
};
