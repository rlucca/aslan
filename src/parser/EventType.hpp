#pragma once

class EventType : public Symbol
{
	public:
		EventType(unsigned line, char *lex);
		virtual ~EventType();
		virtual unsigned char eventAbout() = 0;
};

class BeliefEvent : public EventType
{
	public:
		BeliefEvent();
		virtual unsigned char eventAbout();
};

class GoalEvent : public EventType
{
	public:
		GoalEvent(unsigned line, char *lex);
		virtual unsigned char eventAbout();
};

class TestEvent : public EventType
{
	public:
		TestEvent(unsigned line, char *lex);
		virtual unsigned char eventAbout();
};
