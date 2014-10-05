#include "general_test.hpp"

int main()
{
	istringstream input("id\n"
						"m4\n"
						"set_up\n");
	CREATE_LEX_DATA(&input);

	NEXT;
	EXPECTING_TOKEN(IDENTIFIER);
	EXPECTING_LEXEMA("id");
	DESTROY_LEXEMA;

	NEXT;
	EXPECTING_TOKEN(IDENTIFIER);
	EXPECTING_LEXEMA("m4");
	DESTROY_LEXEMA;

	NEXT;
	EXPECTING_TOKEN(IDENTIFIER);
	EXPECTING_LEXEMA("set_up");
	DESTROY_LEXEMA;

	NEXT;
	EXPECTING_TOKEN(0);
	return 0;
}
