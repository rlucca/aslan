#include "general_test.hpp"


int main()
{
	// Basically this is a stacked symbol
	ConstantExpression *ce = new ConstantExpression(3, strdup("42"));
	Action aux(ce);
	assert(aux.firstLine() == 3);
	assert(strcmp(aux.lexema(), "42") == 0);
	free(ce); // the lexema is shared by ConstantExpression and Action::Symbol
	return 0;
}
