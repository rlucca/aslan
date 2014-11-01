#include "general_test.hpp"

int main()
{
	ConstantExpression *ce = new ConstantExpression(strdup("61"),
													__LINE__);
	ConstantExpression *ce2 = new ConstantExpression(strdup("0"),
													__LINE__);
	Array a(__LINE__, ce);
	// I just need test the tail stuff
	assert(a.tail() == NULL);
	a.setTail(ce2->firstLine(), ce2);
	assert(a.tail() == ce2);
	assert(strcmp(a.tail()->lexema(), "0") == 0);
	// I do not need worry about the destruction of ce2,
	// however the lexema in ce is shared and will result in
	// double free. So...
	free(ce);
	return 0;
}
