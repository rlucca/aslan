#include "general_test.hpp"

int main()
{
	istringstream input("[.]");
	Aslan_Context ac(&input);
	MOC_LEX_DATA(loc, sem);

	EXPECT_LEX(LEFTB, sem, loc, ac, Aslan_lex);
	EXPECT_LEX(DOT_LITERAL, sem, loc, ac, Aslan_lex);
	EXPECT_LEX(RIGHTB, sem, loc, ac, Aslan_lex);
	return 0;
}
