#include "general_test.hpp"

int main()
{
	istringstream input("mar.headUp.\n"
						"m1.move\n"
						"car_2.do_nothing\n");
	CREATE_LEX_DATA(&input);

	NEXT;
	EXPECTING_TOKEN(EXTERNAL_ACTION);
	EXPECTING_LEXEMA("mar.headUp");
	DESTROY_LEXEMA;
	NEXT;
	EXPECTING_TOKEN(DOT_LITERAL);
	EXPECTING_LEXEMA(".");
	DESTROY_LEXEMA;

	NEXT;
	EXPECTING_TOKEN(EXTERNAL_ACTION);
	EXPECTING_LEXEMA("m1.move");
	DESTROY_LEXEMA;

	NEXT;
	EXPECTING_TOKEN(EXTERNAL_ACTION);
	EXPECTING_LEXEMA("car_2.do_nothing");
	DESTROY_LEXEMA;

	NEXT;
	EXPECTING_TOKEN(0);

	return 0;
}
