#include "general_test.hpp"

int main()
{
	ConstantExpression *ce = new ConstantExpression(6, strdup("61"));
	ConstantExpression *ce2 = new ConstantExpression(8, strdup("0"));
	Array a(9, ce);
	// I just need test the tail stuff
	assert(a.tail() == NULL);
	a.setTail(ce2);
	assert(a.tail() == ce2);
	assert(strcmp(a.tail()->lexema(), "0") == 0);
	// I do not need worry about the destruction of ce2,
	// however the lexema in ce is shared and will result in
	// double free. So...
	free(ce);
	return 0;
}
