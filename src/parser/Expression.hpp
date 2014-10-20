#pragma once

class Expression : public Symbol
{
	public:
		Expression(Symbol *left);
		virtual ~Expression();

		void setOp(int operation);
		int op();

		virtual void add(Symbol *);

	protected:
		Symbol *m_left;
		Symbol *m_right;
		int m_op;
};

