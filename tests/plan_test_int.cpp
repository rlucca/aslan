#include "general_test.hpp"

int main()
{
	char *aux = strdup("~a");
	Trigger *trigger = new AdditionTrigger(33, strdup("+"));
	EventType *ev = new GoalEvent(34, strdup("!"));
	Functor *head = new Functor(35, aux, NULL, NULL);
	Expression *contextSums;
	Expression *contextAssigns;
	free(aux); aux = NULL;
	contextSums = new Expression(new ConstantExpression(44, strdup("1")));
	contextSums->add(new ConstantExpression(46, strdup("1")));
	contextSums->setOp(PLUS); // 1 + 1
	contextAssigns = new Expression(new ConstantExpression(44, strdup("X")));
	contextAssigns->add(contextSums);
	contextAssigns->setOp(ASSIGNMENT); // X = 1 + 1
	ConstantExpression *exta
		= new ConstantExpression(50, strdup("character.front"));
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
