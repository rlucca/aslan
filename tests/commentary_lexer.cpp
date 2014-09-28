#include "general_test.hpp"

int main()
{
	istringstream input("/************** \n"
						" +x. \n"
						" a(3).\n "
						" **\n****\n**********/"
						""
						" ");
	Aslan_Context ac(&input);
	MOC_LEX_DATA(loc, sem);

	EXPECT_LEX(0, sem, loc, ac, Aslan_lex);
	return 0;
}
