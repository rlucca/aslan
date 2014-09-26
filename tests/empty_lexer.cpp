#include "general_test.hpp"

int main()
{
	istringstream input("");
	Aslan_Context ac(&input);
	MOC_DATA(loc, sem);

	EXPECT(0, sem, loc, ac, Aslan_lex);
	return 0;
}
