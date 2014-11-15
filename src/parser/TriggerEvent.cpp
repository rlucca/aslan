#include "AllSymbol.hpp"

Trigger::Trigger(unsigned line, char *lex)
	: Symbol(TRIGGER_EVENT_SYMBOL, line, lex)
{
	// VOID
}

Trigger::~Trigger()
{
	// VOID
}

AdditionTrigger::AdditionTrigger(unsigned line, char *lex)
	: Trigger(line, lex)
{
	// VOID
}

unsigned char AdditionTrigger::triggerType()
{
	return 'A';
};

DeletionTrigger::DeletionTrigger(unsigned line, char *lex)
	: Trigger(line, lex)
{
	// VOID
}

unsigned char DeletionTrigger::triggerType()
{
	return 'D';
}
