#include "general_test.hpp"

int main()
{
	istringstream input("	.	\n.07\n"
						".007\n.1\n"
						".1e-1\n.1e+1\n"
						".1e1\n.123.\n"
						"0 012 0xFF 0Xff\n"
						"0.1.\n0.\n");
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
	EXPECT_LEX(NUMBER_LITERAL, sem, loc, ac, Aslan_lex);
	EXPECT_TOKEN_LEX("0", ac);
	EXPECT_LEX(NUMBER_LITERAL, sem, loc, ac, Aslan_lex);
	EXPECT_TOKEN_LEX("012", ac);
	EXPECT_LEX(NUMBER_LITERAL, sem, loc, ac, Aslan_lex);
	EXPECT_TOKEN_LEX("0xFF", ac);
	EXPECT_LEX(NUMBER_LITERAL, sem, loc, ac, Aslan_lex);
	EXPECT_TOKEN_LEX("0Xff", ac);
	EXPECT_LEX(FLOAT_LITERAL, sem, loc, ac, Aslan_lex);
	EXPECT_TOKEN_LEX("0.1", ac);
	EXPECT_LEX(DOT_LITERAL, sem, loc, ac, Aslan_lex);
	EXPECT_LEX(NUMBER_LITERAL, sem, loc, ac, Aslan_lex);
	EXPECT_TOKEN_LEX("0", ac);
	EXPECT_LEX(DOT_LITERAL, sem, loc, ac, Aslan_lex);
	EXPECT_LEX(0, sem, loc, ac, Aslan_lex);

	return 0;
}
