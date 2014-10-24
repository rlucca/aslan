#pragma once

class Belief  : public Symbol
{
 public:
	Belief(Symbol *head, Symbol *opt_context);
};
