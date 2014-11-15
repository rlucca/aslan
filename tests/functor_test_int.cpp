#include "general_test.hpp"

int main()
{
	char *file = strdup(__FILE__);

	// It will just test the new functionality
	{
		Functor fun(__LINE__, file, NULL, NULL);
		assert(fun.parms() == NULL);
		assert(fun.annots() == NULL);
	}
	{
		ConstantExpression *cep = new ConstantExpression(12, strdup("foo"));
		Parameter *parm = new Parameter(12, cep);
		Functor fun(__LINE__, file, parm, NULL);
		assert(fun.parms() == parm);
		assert(((StackedSymbol *) fun.parms())->size() == 1);
		assert(fun.annots() == NULL);
		free(cep); // lexema foo is shared
	}
	{
		ConstantExpression *ce = new ConstantExpression(12, strdup("foo"));
		Array *annot = new Array(12, ce);
		Functor fun(__LINE__, file, NULL, annot);
		assert(fun.parms() == NULL);
		assert(fun.annots() == annot);
		free(ce); // lexema foo is shared
	}
	{
		ConstantExpression *cep = new ConstantExpression(12, strdup("foo"));
		Parameter *parm = new Parameter(12, cep);
		ConstantExpression *ce = new ConstantExpression(12, strdup("foo"));
		Array *annot = new Array(12, ce);
		Functor fun(__LINE__, file, parm, annot);
		assert(fun.parms() == parm);
		assert(((StackedSymbol *) fun.parms())->size() == 1);
		assert(fun.annots() == annot);
		free(cep); // lexema foo is shared
		free(ce); // lexema foo is shared
	}
	free(file);
	return 0;
}
