#include "general_test.hpp"

int main()
{
	char *aux = strdup("~a");
	Trigger *trigger = new AdditionTrigger(33, strdup("+"));
	EventType *ev = new GoalEvent(strdup("!"), 34);
	Functor *head = new Functor(aux, 35, NULL, NULL);
	Expression *contextSums;
	Expression *contextAssigns;
	free(aux); aux = NULL;
	contextSums = new Expression(new ConstantExpression(strdup("1"), 44));
	contextSums->add(new ConstantExpression(strdup("1"), 46));
	contextSums->setOp(PLUS); // 1 + 1
	contextAssigns = new Expression(new ConstantExpression(strdup("X"), 44));
	contextAssigns->add(contextSums);
	contextAssigns->setOp(ASSIGNMENT); // X = 1 + 1
	ConstantExpression *exta
		= new ConstantExpression(strdup("character.front"), 50);
	Plan plan(trigger, ev, head);
	assert(plan.trigger() == 'A');
	assert(plan.about() == 'G');
	assert(plan.type() == PLAN_TYPE_SYMBOL);
	assert(plan.firstLine() == 33);
	assert(plan.lastLine() == 35);
	plan.addContext(contextAssigns)->addAction(NULL);
	assert(plan.context() == contextAssigns);
	assert(plan.firstLine() == 33);
	assert(plan.lastLine() == 46);
	plan.addAction(exta);
	assert(plan.context() == contextAssigns);
	assert(plan.action() == exta);
	assert(plan.firstLine() == 33);
	assert(plan.lastLine() == 50);

	return 0;
}
