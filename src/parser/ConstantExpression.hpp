#pragma once

class ConstantExpression : public Symbol
{
	public:
		ConstantExpression(unsigned, char *);
		virtual ~ConstantExpression();
};

std::ostream& operator<<(std::ostream& os, ConstantExpression *);
