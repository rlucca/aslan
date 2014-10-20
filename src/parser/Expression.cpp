#include "AllSymbol.hpp"
#include "Utils.hpp"
#include <cstdio>

Expression::Expression(Symbol *left)
	: Symbol('E', left->firstLine(), NULL), m_left(left), m_right(0), m_op(0)
{
	m_beginLine = left->firstLine();
	m_endLine = left->lastLine();
	m_many = left->manyComponents();
}

Expression::~Expression()
{ }

void Expression::setOp(int operation)
{ m_op = operation; }

int Expression::op()
{ return m_op; }

void Expression::add(Symbol *right)
{
	m_right = right;
	m_lexema = lexema_cat(m_lexema, right->lexema());
	m_endLine = right->lastLine();
	m_many += right->manyComponents();
}
