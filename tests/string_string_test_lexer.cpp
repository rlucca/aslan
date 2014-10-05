#include "general_test.hpp"

int main()
{
	istringstream input("	\"\"	\n"
						"\"a\"	\n"
						"\"\\\\\"	\n"
						"\"\\\\n\"\n"
						"\"\\n\"	\n"
						"\"\\141\"\n"
						"\"\\\"\"\n"
						"\"abacate \\141 noite\\n\"\n"
						"\n");
	CREATE_LEX_DATA(&input);

	NEXT;
	EXPECTING_TOKEN(STRING_LITERAL);
	EXPECTING_LEXEMA("\"\"");
	DESTROY_LEXEMA;

	NEXT;
	EXPECTING_TOKEN(STRING_LITERAL);
	EXPECTING_LEXEMA("\"a\"");
	DESTROY_LEXEMA;

	NEXT;
	EXPECTING_TOKEN(STRING_LITERAL);
	EXPECTING_LEXEMA("\"\\\\\"");
	DESTROY_LEXEMA;

	NEXT;
	EXPECTING_TOKEN(STRING_LITERAL);
	EXPECTING_LEXEMA("\"\\\\n\"");
	DESTROY_LEXEMA;

	NEXT;
	EXPECTING_TOKEN(STRING_LITERAL);
	EXPECTING_LEXEMA("\"\\n\"");
	DESTROY_LEXEMA;

	NEXT;
	EXPECTING_TOKEN(STRING_LITERAL);
	EXPECTING_LEXEMA("\"\\141\"");
	/* We are not interpreting the data! So, it must fail! */
	NOT_EXPECTING_LEXEMA("\"\141\"");
	DESTROY_LEXEMA;

	NEXT;
	EXPECTING_TOKEN(STRING_LITERAL);
	EXPECTING_LEXEMA("\"\\\"\"");
	DESTROY_LEXEMA;

	NEXT;
	EXPECTING_TOKEN(STRING_LITERAL);
	EXPECTING_LEXEMA("\"abacate \\141 noite\\n\"");
	DESTROY_LEXEMA;

	return 0;
}
