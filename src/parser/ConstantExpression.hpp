#pragma once

class ConstantExpression : public Symbol
{
	public:
		ConstantExpression(char *, unsigned);
		virtual ~ConstantExpression();
};

std::ostream& operator<<(std::ostream& os, ConstantExpression *);
