#pragma once

class Functor : public Symbol
{
 public:
	Functor(char *identifier, unsigned identifier_line,
			Symbol* parms = 0, Symbol* annots = 0);
};
