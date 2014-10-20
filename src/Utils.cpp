#include "Utils.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>

char *lexema_cat(char *first,
				 char *second)
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
		strcat(ret, second);
	}

	return ret;
}

char *lexema_append(char *first,
					char *second,
					char changeDelimiter)
{
	char *ret = lexema_cat(first, second);

	if (ret && changeDelimiter)
	{
		ret[0] = changeDelimiter;
		ret[strlen(ret) - 1] = changeDelimiter;
		if (second)
		{
			char *to = ret + strlen(first) - 1;
			char *from = ret + strlen(first) + 1;
			memmove(to, from, strlen(ret) - strlen(first));
		}
	}

	free(first);
	free(second);
	return ret;
}
