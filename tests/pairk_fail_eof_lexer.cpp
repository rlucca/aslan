#include "general_test.hpp"

int main()
{
	istringstream input("{");
	Aslan_Context ac(&input);
	MOC_LEX_DATA(loc, sem);

	EXPECT_LEX(LEFTK, sem, loc, ac, Aslan_lex);
	EXPECT_LEX(0, sem, loc, ac, Aslan_lex);
	return 0;
}
