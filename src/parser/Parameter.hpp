#pragma once

class Parameter : public StackedSymbol
{
 public:
	Parameter(Symbol *s);
	virtual ~Parameter();
};

std::ostream& operator<<(std::ostream& os, Parameter* right);
