#pragma once

class Trigger : public Symbol
{
	public:
		Trigger(unsigned line, char *lex);
		virtual ~Trigger();
		virtual unsigned char triggerType() = 0;
};

class AdditionTrigger : public Trigger
{
	public:
		AdditionTrigger(unsigned line, char *lex);
		virtual unsigned char triggerType();
};

class DeletionTrigger : public Trigger
{
	public:
		DeletionTrigger(unsigned line, char *lex);
		virtual unsigned char triggerType();
};
