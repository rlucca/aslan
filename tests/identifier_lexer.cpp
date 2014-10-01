#include "general_test.hpp"

int main()
{
	istringstream input("id\n"
						"m4\n"
						"set_up\n");
	Aslan_Context ac(&input);
	MOC_LEX_DATA(loc, sem);

	EXPECT_LEX(IDENTIFIER, sem, loc, ac, Aslan_lex);
	EXPECT_LEX(IDENTIFIER, sem, loc, ac, Aslan_lex);
	EXPECT_LEX(IDENTIFIER, sem, loc, ac, Aslan_lex);
	EXPECT_LEX(0, sem, loc, ac, Aslan_lex);
	return 0;
}