#pragma once

class Parameter : public StackedSymbol
{
 public:
	Parameter(unsigned line, Symbol *s);
	virtual ~Parameter();
};
