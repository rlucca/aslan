#pragma once

class Parameter : public StackedSymbol
{
 public:
	Parameter(Symbol *s);
	virtual ~Parameter();
};
