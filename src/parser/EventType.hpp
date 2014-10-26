#pragma once

class EventType : public Symbol
{
	public:
		EventType(char *lexema, unsigned line);
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
		GoalEvent(char *lexema, unsigned line);
		virtual unsigned char eventAbout();
};

class TestEvent : public EventType
{
	public:
		TestEvent(char *lexema, unsigned line);
		virtual unsigned char eventAbout();
};
