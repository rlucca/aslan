#include "general_test.hpp"

int main()
{
	istringstream input("mar.headUp.\n"
						"m1.move\n"
						"car_2.do_nothing\n");
	Aslan_Context ac(&input);
	MOC_LEX_DATA(loc, sem);

	EXPECT_LEX(EXTERNAL_ACTION, sem, loc, ac, Aslan_lex);
	EXPECT_LEX(DOT_LITERAL, sem, loc, ac, Aslan_lex);
	EXPECT_LEX(EXTERNAL_ACTION, sem, loc, ac, Aslan_lex);
	EXPECT_LEX(EXTERNAL_ACTION, sem, loc, ac, Aslan_lex);
	EXPECT_LEX(0, sem, loc, ac, Aslan_lex);
	return 0;
}
