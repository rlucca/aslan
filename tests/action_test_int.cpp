#include "general_test.hpp"


int main()
{
	// Basically this is a stacked symbol
	ConstantExpression *ce = new ConstantExpression(strdup("42"), 3);
	Action aux(ce->firstLine(), ce);
	assert(aux.firstLine() == 3);
	assert(strcmp(aux.lexema(), "42") == 0);
	free(ce); // the lexema is shared by ConstantExpression and Action::Symbol
	return 0;
}