#pragma once

class ConstantExpression : public Symbol
{
	public:
		ConstantExpression(char *, unsigned);
		virtual ~ConstantExpression();

		virtual void add(Symbol *);
};

