#include "general_test.hpp"

int main()
{
	istringstream input("	'	\n");
	Aslan_Context ac(&input);
	MOC_LEX_DATA(loc, sem);

	/* program will be ended by the fatal message.
	 * Although the test wont be performed here,
	 * it'll be tested by the error by ctest. */
	EXPECT_LEX(0, sem, loc, ac, Aslan_lex);
	return 0;
}
