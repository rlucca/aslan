#include "general_test.hpp"

int main()
{
	// Preparing set to test
	char a_lex[] = "a";
	Expression *contextEquals;
	Expression *contextAssigns;
	contextEquals = new Expression(new ConstantExpression(24, strdup("0")));
	contextAssigns = new Expression(new ConstantExpression(24, strdup("0")));
	contextEquals->add(new ConstantExpression(26, strdup("2")));
	contextAssigns->add(new ConstantExpression(26, strdup("2")));
	contextEquals->setOp(EQUAL_CMP);
	contextAssigns->setOp(ASSIGNMENT);
	// Starting to test
	{
		Functor *head = new Functor(22, a_lex, NULL, NULL);
		Belief belief1(head, NULL);
		assert(belief1.getId() > 0); // always true?
		assert(belief1.firstLine() == 22);
		assert(belief1.lastLine() == 22);
		assert(belief1.manyComponents() == 1);
		assert(belief1.type() == BELIEF_TYPE_SYMBOL);
		assert(strcmp(belief1.lexema(), "a") == 0);
		assert(belief1.context() == NULL);
	}
	{
		// rules has a lexema just the head,
		// not head + context
		Functor *head = new Functor(22, a_lex, NULL, NULL);
		Belief belief1(head, contextEquals);
		assert(belief1.getId() > 0); // always true?
		assert(belief1.firstLine() == 22);
		assert(belief1.lastLine() == 26);
		assert(belief1.manyComponents() == 3);
		assert(belief1.type() == BELIEF_TYPE_SYMBOL);
		assert(strcmp(belief1.lexema(), "a") == 0);
		assert(belief1.context() == contextEquals);
		assert(((Expression*)belief1.context())->op() == EQUAL_CMP);
	}
	{
		// rules has a lexema just the head,
		// not head + context
		Functor *head = new Functor(22, a_lex, NULL, NULL);
		Belief belief1(head, contextAssigns);
		assert(belief1.getId() > 0); // always true?
		assert(belief1.firstLine() == 22);
		assert(belief1.lastLine() == 26);
		assert(belief1.manyComponents() == 3);
		assert(belief1.type() == BELIEF_TYPE_SYMBOL);
		assert(strcmp(belief1.lexema(), "a") == 0);
		assert(belief1.context() == contextAssigns);
		assert(((Expression*)belief1.context())->op() == ASSIGNMENT);
	}


	return 0;
}
