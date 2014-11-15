#include "general_test.hpp"

int main()
{
	// Preparing set to test
	char *a_lex = strdup("a");
	char *not_a_lex = strdup("~a");
	Functor head(22, a_lex, NULL, NULL);
	Functor headNegative(22, not_a_lex, NULL, NULL);
	Expression *contextEquals;
	Expression *contextAssigns;
	free(a_lex); a_lex = NULL;
	free(not_a_lex); not_a_lex = NULL;
	contextEquals = new Expression(new ConstantExpression(strdup("0"), 24));
	contextAssigns = new Expression(new ConstantExpression(strdup("0"), 24));
	contextEquals->add(new ConstantExpression(strdup("2"), 26));
	contextAssigns->add(new ConstantExpression(strdup("2"), 26));
	contextEquals->setOp(EQUAL_CMP);
	contextAssigns->setOp(ASSIGNMENT);
	// Starting to test
	{
		Belief belief1(&head, NULL);
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
		Belief belief1(&head, contextEquals);
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
		Belief belief1(&head, contextAssigns);
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
