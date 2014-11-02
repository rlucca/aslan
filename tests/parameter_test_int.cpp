#include "general_test.hpp"


int main()
{
	// Basically this is a stacked symbol
	ConstantExpression *ce = new ConstantExpression(strdup("42"), 17);
	Parameter aux(ce->firstLine(), ce);
	assert(aux.firstLine() == 17);
	assert(strcmp(aux.lexema(), "42") == 0);
	free(ce); // I don't call delete because strdup("42") is shared
	return 0;
}