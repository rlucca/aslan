#include "general_test.hpp"

int main()
{
	istringstream input("");
	CREATE_LEX_DATA(&input);

	NEXT;
	EXPECTING_TOKEN(0);
	return 0;
}
