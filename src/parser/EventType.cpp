#include "AllSymbol.hpp"

EventType::EventType(char *lex, unsigned line)
	: Symbol(EVENT_TYPE_SYMBOL, line, lex)
{
	// VOID
}

EventType::~EventType()
{
	// VOID
}

BeliefEvent::BeliefEvent()
	: EventType(NULL, 0)
{
	// VOID
}

unsigned char BeliefEvent::eventAbout()
{
	return 'B';
}

GoalEvent::GoalEvent(char *lex, unsigned line)
	: EventType(lex, line)
{
	// VOID
}

unsigned char GoalEvent::eventAbout()
{
	return 'G';
}

TestEvent::TestEvent(char *lex, unsigned line)
	: EventType(lex, line)
{
	// VOID
}

unsigned char TestEvent::eventAbout()
{
	return 'T';
}
