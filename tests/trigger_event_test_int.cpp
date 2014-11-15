#include "general_test.hpp"

int main()
{
	{
		AdditionTrigger at(666, strdup("+"));
		assert(at.firstLine() == 666);
		assert(at.lastLine() == 666);
		assert(at.triggerType() == 'A');
		assert(at.type() == TRIGGER_EVENT_SYMBOL);
		assert(strcmp(at.lexema(), "+") == 0);
	}
	{
		DeletionTrigger dt(123, strdup("-"));
		assert(dt.firstLine() == 123);
		assert(dt.lastLine() == 123);
		assert(dt.triggerType() == 'D');
		assert(dt.type() == TRIGGER_EVENT_SYMBOL);
		assert(strcmp(dt.lexema(), "-") == 0);
	}
	return 0;
}
