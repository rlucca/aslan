#pragma once

class Trigger : public Symbol
{
	public:
		Trigger(char *, unsigned line);
		virtual ~Trigger();
		virtual unsigned char triggerType() = 0;
};

class AdditionTrigger : public Trigger
{
	public:
		AdditionTrigger(char *lexema, unsigned line);
		virtual unsigned char triggerType();
};

class DeletionTrigger : public Trigger
{
	public:
		DeletionTrigger(char *lexema, unsigned line);
		virtual unsigned char triggerType();
};
