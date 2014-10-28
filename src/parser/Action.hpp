#pragma once

class Action : public StackedSymbol
{
	public:
		Action(unsigned line, Symbol *s);
		virtual ~Action();
};
