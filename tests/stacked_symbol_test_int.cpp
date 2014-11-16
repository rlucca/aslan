#include "general_test.hpp"

int main()
{
	// Preparing data
	char *lexema_value = strdup("true");
	ConstantExpression *ce = new ConstantExpression(1, lexema_value);
	StackedSymbol ss('?', ce);
	ConstantExpression *aux;
	// Recover top element and test to be equal
	aux = (ConstantExpression *) ss.top();
	assert(aux->type() == 'I');
	assert(strcmp(aux->lexema(), lexema_value) == 0);
	assert(aux == ce); // Test the pointers
	// Test of stack
	assert(ss.type() == '?');
	assert(ss.type() == '?');
	assert(ss.empty() == false);
	assert(ss.size() == 1);
	// Lets remove the last element and try get the top
	ss.pop();
	assert(ss.empty() == true);
	assert(ss.top() == NULL);
	// I'm not sure about this stuff... should I keep a nulled
	// element stacked or should I do not insert it?
	// For now the easy stuff is to keep the element stacked
	ss.push(123, NULL);
	ss.push(124, NULL);
	assert(ss.empty() == false);
	assert(ss.size() == 2);
	assert(ss.top() == NULL);
	ss.pop();
	assert(ss.empty() == false);
	assert(ss.size() == 1);
	assert(ss.top() == NULL);
	ss.pop();
	assert(ss.empty() == true);
	assert(ss.size() == 0);
	assert(ss.top() == NULL);
	// I have a problem here, lexema_value will be
	// destroyed by ConstantExpression and StackedSymbol.
	// So, in this test we will not call the destructor
	// of ConstantExpression class because that!
	free(ce);
	return 0;
}
