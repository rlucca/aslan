#include "general_test.hpp"

int main()
{
	istringstream input(" ");
	ostringstream output;
	Aslan_Context ac(&input);

	ac.setOutputStream(&output);

	Aslan_parse(&ac);

	if (output.str().empty() == true)
		return 0; // OK, it must be empty

	return __LINE__;
}
