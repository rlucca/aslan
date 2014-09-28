#include "general_test.hpp"

int main()
{
	istringstream input("	.	\n"
						".07\n"
						".007\n"
						".1\n"
						".1e-1\n"
						".1e+1\n"
						".1e1\n"
						".123.\n");
	Aslan_Context ac(&input);
	MOC_LEX_DATA(loc, sem);

	EXPECT_LEX(DOT_LITERAL, sem, loc, ac, Aslan_lex);
	EXPECT_TOKEN_LEX(".", ac);
	EXPECT_LEX(FLOAT_LITERAL, sem, loc, ac, Aslan_lex);
	EXPECT_TOKEN_LEX(".07", ac);
	EXPECT_LEX(FLOAT_LITERAL, sem, loc, ac, Aslan_lex);
	EXPECT_TOKEN_LEX(".007", ac);
	EXPECT_LEX(FLOAT_LITERAL, sem, loc, ac, Aslan_lex);
	EXPECT_TOKEN_LEX(".1", ac);
	EXPECT_LEX(FLOAT_LITERAL, sem, loc, ac, Aslan_lex);
	EXPECT_TOKEN_LEX(".1e-1", ac);
	EXPECT_LEX(FLOAT_LITERAL, sem, loc, ac, Aslan_lex);
	EXPECT_TOKEN_LEX(".1e+1", ac);
	EXPECT_LEX(FLOAT_LITERAL, sem, loc, ac, Aslan_lex);
	EXPECT_TOKEN_LEX(".1e1", ac);
	EXPECT_LEX(FLOAT_LITERAL, sem, loc, ac, Aslan_lex);
	NOT_EXPECT_TOKEN_LEX(".123.", ac);
	EXPECT_TOKEN_LEX(".123", ac);
	EXPECT_LEX(DOT_LITERAL, sem, loc, ac, Aslan_lex);
	EXPECT_TOKEN_LEX(".", ac);

	return 0;
}
