#include "general_test.hpp"

int main()
{
	istringstream input("/************** \n"
						" +x. \n"
						" a(3).\n "
						" **\n****\n**********/"
						"\n\n"
						"// .3\n"
						"// a.\n"
						"// +x <- foo;"
						"         bar.\n"
						" ");
	CREATE_LEX_DATA(&input);

	NEXT;
	EXPECTING_TOKEN(0);

	return 0;
}
