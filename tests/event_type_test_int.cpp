#include "general_test.hpp"

int main()
{
	{
		BeliefEvent be1;
		assert(be1.eventAbout() == 'B');
		assert(be1.lexema() == NULL);
		assert(be1.type() == EVENT_TYPE_SYMBOL);
	}
	{
		GoalEvent ge1(strdup("doggy"), 23);
		assert(ge1.eventAbout() == 'G');
		assert(strcmp(ge1.lexema(), "doggy") == 0);
		assert(ge1.firstLine() == ge1.lastLine());
		assert(ge1.firstLine() == 23);
		assert(ge1.type() == EVENT_TYPE_SYMBOL);
	}
	{
		TestEvent te1(strdup("fun"), 166);
		assert(te1.eventAbout() == 'T');
		assert(strcmp(te1.lexema(), "fun") == 0);
		assert(te1.firstLine() == te1.lastLine());
		assert(te1.lastLine() == 166);
		assert(te1.type() == EVENT_TYPE_SYMBOL);
	}
	return 0;
}
