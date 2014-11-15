#include "AllSymbol.hpp"

EventType::EventType(unsigned line, char *lex)
	: Symbol(EVENT_TYPE_SYMBOL, line, lex)
{
	// VOID
}

EventType::~EventType()
{
	// VOID
}

BeliefEvent::BeliefEvent()
	: EventType(0, NULL)
{
	// VOID
}

unsigned char BeliefEvent::eventAbout()
{
	return 'B';
}

GoalEvent::GoalEvent(unsigned line, char *lex)
	: EventType(line, lex)
{
	// VOID
}

unsigned char GoalEvent::eventAbout()
{
	return 'G';
}

TestEvent::TestEvent(unsigned line, char *lex)
	: EventType(line, lex)
{
	// VOID
}

unsigned char TestEvent::eventAbout()
{
	return 'T';
}
