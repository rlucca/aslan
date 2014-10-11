#include "Utils.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>

char *lexema_append(char *first,
					char *second,
					char changeDelimiter)
{
	char *ret = NULL;
	int ret_size = 0;

	if (first == NULL)
		return ret;

	ret_size += strlen(first) + 1; // plus final zero
	ret = (char *) malloc(sizeof(char) * ret_size);

	strcpy(ret, first);

	if (second != NULL)
	{
		ret_size += strlen(second);
		ret = (char *) realloc(ret, sizeof(char) * ret_size);

		if (changeDelimiter)
		{
			ret[strlen(ret) - 1] = 0;
			strcat(ret, second + 1);
		} else {
			strcat(ret, second);
		}

		free(second);
	}

	if (changeDelimiter)
	{
		ret[0] = changeDelimiter;
		ret[strlen(ret) - 1] = changeDelimiter;
	}

	free(first);
	return ret;
}
