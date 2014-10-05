#include "general_test.hpp"

#define STRING_TEST_EXPECTED								\
	NEXT;													\
	EXPECTING_LEXEMA("/");									\
	DESTROY_LEXEMA;											\
	NEXT;													\
	EXPECTING_LEXEMA("%");									\
	DESTROY_LEXEMA;											\
	NEXT;													\
	EXPECTING_LEXEMA("*");									\
	DESTROY_LEXEMA;											\
	NEXT;													\
	EXPECTING_LEXEMA("+");									\
	DESTROY_LEXEMA;											\
	NEXT;													\
	EXPECTING_LEXEMA("-");									\
	DESTROY_LEXEMA;											\
	NEXT;													\
	EXPECTING_LEXEMA("?");									\
	DESTROY_LEXEMA;											\
	NEXT;													\
	EXPECTING_LEXEMA(",");									\
	DESTROY_LEXEMA;											\
	NEXT;													\
	EXPECTING_LEXEMA(":");									\
	DESTROY_LEXEMA;											\
	NEXT;													\
	EXPECTING_LEXEMA(";");									\
	DESTROY_LEXEMA;											\
	NEXT;													\
	EXPECTING_LEXEMA("~");									\
	DESTROY_LEXEMA;											\
	NEXT;													\
	EXPECTING_LEXEMA("^");									\
	DESTROY_LEXEMA;											\
	NEXT;													\
	EXPECTING_LEXEMA("!=");									\
	DESTROY_LEXEMA;											\
	NEXT;													\
	EXPECTING_LEXEMA("!");									\
	DESTROY_LEXEMA;											\
	NEXT;													\
	EXPECTING_LEXEMA("==");									\
	DESTROY_LEXEMA;											\
	NEXT;													\
	EXPECTING_LEXEMA("=");									\
	DESTROY_LEXEMA;											\
	NEXT;													\
	EXPECTING_LEXEMA("&&");									\
	DESTROY_LEXEMA;											\
	NEXT;													\
	EXPECTING_LEXEMA("&");									\
	DESTROY_LEXEMA;											\
	NEXT;													\
	EXPECTING_LEXEMA("||");									\
	DESTROY_LEXEMA;											\
	NEXT;													\
	EXPECTING_LEXEMA("<<");									\
	DESTROY_LEXEMA;											\
	NEXT;													\
	EXPECTING_LEXEMA("<=");									\
	DESTROY_LEXEMA;											\
	NEXT;													\
	EXPECTING_LEXEMA("<-");									\
	DESTROY_LEXEMA;											\
	NEXT;													\
	EXPECTING_LEXEMA("<");									\
	DESTROY_LEXEMA;											\
	NEXT;													\
	EXPECTING_LEXEMA(">>");									\
	DESTROY_LEXEMA;											\
	NEXT;													\
	EXPECTING_LEXEMA(">=");									\
	DESTROY_LEXEMA;											\
	NEXT;													\
	EXPECTING_LEXEMA(">");									\
	DESTROY_LEXEMA;											\
	NEXT;													\
	EXPECTING_TOKEN(NOT);									\
	DESTROY_LEXEMA

int main()
{
	istringstream input("\n"
						"/%*+-?,:;~^ != ! == = && & || << <= <- < >> >= > not | \n"
						"(/%*+-?,:;~^ != ! == = && & || << <= <- < >> >= > nOt | )\n"
						"{/%*+-?,:;~^ != ! == = && & || << <= <- < >> >= > NoT | }\n"
						"[/%*+-?,:;~^ != ! == = && & || << <= <- < >> >= > NOT | ]\n"
						"\n");
	CREATE_LEX_DATA(&input);

	STRING_TEST_EXPECTED;
	NEXT;
	EXPECTING_TOKEN(OR_BIT);
	EXPECTING_LEXEMA("|");
	DESTROY_LEXEMA;

	NEXT;
	EXPECTING_TOKEN(LEFTP);
	EXPECTING_LEXEMA("(");
	DESTROY_LEXEMA;

	STRING_TEST_EXPECTED;
	NEXT;
	EXPECTING_TOKEN(OR_BIT);
	EXPECTING_LEXEMA("|");
	DESTROY_LEXEMA;

	NEXT;
	EXPECTING_TOKEN(RIGHTP);
	EXPECTING_LEXEMA(")");
	DESTROY_LEXEMA;

	NEXT;
	EXPECTING_TOKEN(LEFTK);
	EXPECTING_LEXEMA("{");
	DESTROY_LEXEMA;

	STRING_TEST_EXPECTED;
	NEXT;
	EXPECTING_TOKEN(OR_BIT);
	EXPECTING_LEXEMA("|");
	DESTROY_LEXEMA;

	NEXT;
	EXPECTING_TOKEN(RIGHTK);
	EXPECTING_LEXEMA("}");
	DESTROY_LEXEMA;

	NEXT;
	EXPECTING_TOKEN(LEFTB);
	EXPECTING_LEXEMA("[");
	DESTROY_LEXEMA;

	STRING_TEST_EXPECTED;
	NEXT;
	/*	Inside a block [] the OR_BIT is called SEParator operator.
		It is used to divide the head and tail of a list. */
	EXPECTING_TOKEN(SEP);
	EXPECTING_LEXEMA("|");
	DESTROY_LEXEMA;

	NEXT;
	EXPECTING_TOKEN(RIGHTB);
	EXPECTING_LEXEMA("]");
	DESTROY_LEXEMA;

	NEXT;
	EXPECTING_TOKEN(0);

	return 0;
}
