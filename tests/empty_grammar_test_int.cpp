#include "general_test.hpp"

int main()
{
	istringstream input(" ");
	ostringstream output;
	Aslan_Context ac(&input);
	int ret = 1;

	ac.setOutputStream(&output);

	Aslan_parse(&ac);

	if (output.str().empty() == true)
		ret = 0;

	return ret;
}
