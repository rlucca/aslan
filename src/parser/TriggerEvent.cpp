#include "AllSymbol.hpp"

Trigger::Trigger(char *lex, unsigned line)
	: Symbol(CONSTANT_EXPRESSION_SYMBOL, line, lex)
{
	// VOID
}

Trigger::~Trigger()
{
	// VOID
}

AdditionTrigger::AdditionTrigger(char *lex, unsigned line)
	: Trigger(lex, line)
{
	// VOID
}

unsigned char AdditionTrigger::triggerType()
{
	return 'A';
};

DeletionTrigger::DeletionTrigger(char *lex, unsigned line)
	: Trigger(lex, line)
{
	// VOID
}

unsigned char DeletionTrigger::triggerType()
{
	return 'D';
}
