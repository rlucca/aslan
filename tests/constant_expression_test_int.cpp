#include "general_test.hpp"

int main()
{
	{
		ConstantExpression literalZero(24, strdup("0"));
		std::ostringstream oss;
		std::string aux;
		assert(literalZero.getId() > 0);
		assert(literalZero.firstLine() == literalZero.lastLine());
		assert(literalZero.firstLine() == 24);
		assert(literalZero.manyComponents() == 1);
		assert(literalZero.type() == CONSTANT_EXPRESSION_SYMBOL);
		assert(strcmp(literalZero.lexema(), "0") == 0);
		oss << (&literalZero);
		aux = oss.str();
		assert(aux == std::string("0"));
	}
	{
		ConstantExpression literalString(26, strdup("\"fruit is good\""));
		std::ostringstream oss;
		std::string aux;
		assert(literalString.getId() > 0);
		assert(literalString.firstLine() == literalString.lastLine());
		assert(literalString.firstLine() == 26);
		assert(literalString.manyComponents() == 1);
		assert(literalString.type() == CONSTANT_EXPRESSION_SYMBOL);
		assert(strcmp(literalString.lexema(), "\"fruit is good\"") == 0);
		oss << (&literalString);
		aux = oss.str();
		assert(aux == std::string("\"fruit is good\""));
	}


	return 0;
}
