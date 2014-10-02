#include "general_test.hpp"

int main()
{
	istringstream input("	''	\n"
						"'a'	\n"
						"'\\\\'	\n"
						"'\\\\n'\n"
						"'\\n'	\n"
						"'\\141'\n"
						"'\\\''\n"
						"\n");
	Aslan_Context ac(&input);
	MOC_LEX_DATA(loc, sem);

	EXPECT_LEX(CHAR_STRING_LITERAL, sem, loc, ac, Aslan_lex);
	EXPECT_TOKEN_LEX("''", ac);
	EXPECT_LEX(CHAR_STRING_LITERAL, sem, loc, ac, Aslan_lex);
	EXPECT_TOKEN_LEX("'a'", ac);
	EXPECT_LEX(CHAR_STRING_LITERAL, sem, loc, ac, Aslan_lex);
	EXPECT_TOKEN_LEX("'\\\\'", ac);
	EXPECT_LEX(CHAR_STRING_LITERAL, sem, loc, ac, Aslan_lex);
	EXPECT_TOKEN_LEX("'\\\\n'", ac);
	EXPECT_LEX(CHAR_STRING_LITERAL, sem, loc, ac, Aslan_lex);
	EXPECT_TOKEN_LEX("'\\n'", ac);

	EXPECT_LEX(CHAR_STRING_LITERAL, sem, loc, ac, Aslan_lex);
	EXPECT_TOKEN_LEX("'\\141'", ac);
	/* We are not interpreting the data! So, it must fail! */
	NOT_EXPECT_TOKEN_LEX("'\141'", ac);

	EXPECT_LEX(CHAR_STRING_LITERAL, sem, loc, ac, Aslan_lex);
	EXPECT_TOKEN_LEX("'\\\''", ac);
	return 0;
}
