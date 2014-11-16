#include "general_test.hpp"


int main()
{
	// Basically this is a stacked symbol
	ConstantExpression *ce = new ConstantExpression(17, strdup("42"));
	Parameter aux(ce);
	assert(aux.firstLine() == 17);
	assert(strcmp(aux.lexema(), "42") == 0);
	free(ce); // I don't call delete because strdup("42") is shared
	return 0;
}
