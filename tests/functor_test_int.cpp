#include "general_test.hpp"

int main()
{
	char *file = strdup(__FILE__);

	// It will just test the new functionality
	{
		Functor fun(file, __LINE__, NULL, NULL);
		assert(fun.parms() == NULL);
		assert(fun.annots() == NULL);
	}
	{
		ConstantExpression *cep = new ConstantExpression(strdup("foo"), 12);
		Parameter *parm = new Parameter(12, cep);
		Functor fun(file, __LINE__, parm, NULL);
		assert(fun.parms() == parm);
		assert(((StackedSymbol *) fun.parms())->size() == 1);
		assert(fun.annots() == NULL);
		free(cep); // lexema foo is shared
	}
	{
		ConstantExpression *ce = new ConstantExpression(strdup("foo"), 12);
		Array *annot = new Array(12, ce);
		Functor fun(file, __LINE__, NULL, annot);
		assert(fun.parms() == NULL);
		assert(fun.annots() == annot);
		free(ce); // lexema foo is shared
	}
	{
		ConstantExpression *cep = new ConstantExpression(strdup("foo"), 12);
		Parameter *parm = new Parameter(12, cep);
		ConstantExpression *ce = new ConstantExpression(strdup("foo"), 12);
		Array *annot = new Array(12, ce);
		Functor fun(file, __LINE__, parm, annot);
		assert(fun.parms() == parm);
		assert(((StackedSymbol *) fun.parms())->size() == 1);
		assert(fun.annots() == annot);
		free(cep); // lexema foo is shared
		free(ce); // lexema foo is shared
	}
	free(file);
	return 0;
}
