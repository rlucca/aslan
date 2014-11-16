#pragma once

class Action : public StackedSymbol
{
	public:
		Action(Symbol *s);
		virtual ~Action();
};
