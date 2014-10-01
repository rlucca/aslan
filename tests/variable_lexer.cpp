#include "general_test.hpp"

int main()
{
	istringstream input(" _ // It is like a no name variable\n"
						" _no_name_too // It can't be referenced\n"
						" MOUNTAIN "
						" LUCKY2GO "
						" LUCCA_CITY ");
	Aslan_Context ac(&input);
	MOC_LEX_DATA(loc, sem);

	EXPECT_LEX(VARIABLE, sem, loc, ac, Aslan_lex);
	EXPECT_LEX(VARIABLE, sem, loc, ac, Aslan_lex);
	EXPECT_LEX(VARIABLE, sem, loc, ac, Aslan_lex);
	EXPECT_LEX(VARIABLE, sem, loc, ac, Aslan_lex);
	EXPECT_LEX(VARIABLE, sem, loc, ac, Aslan_lex);
	EXPECT_LEX(0, sem, loc, ac, Aslan_lex);
	return 0;
}
