#include "general_test.hpp"

int main()
{
	istringstream input(")");
	CREATE_LEX_DATA(&input);

	/* program will be ended by the fatal message.
	 * Although the test wont be performed here,
	 * it'll be tested by the error by ctest. */
	NEXT;
	return 0;
}
