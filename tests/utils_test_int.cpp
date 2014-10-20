#include "Utils.hpp"
#include <cassert>
#include <cstdlib>
#include <cstring>

static void firstStringNull()
{
	char *ret = lexema_append(NULL, NULL);
	assert(ret == NULL && "first param is NULL, must return NULL too");
	free(ret);
}

static void firstStringEmptySecondStringNull()
{
	char *ret = lexema_append(strdup(""), NULL);
	assert(!strcmp(ret, "") && "must return a empty string too");
	free(ret);
}

static void firstStringEmptySecondStringNullChangingDelimiter()
{
	char *ret = lexema_append(strdup("''"), NULL, '"');
	assert(!strcmp(ret, "\"\"")
			&& "must return a empty string with the correct delimiter");
	free(ret);
}

static void firstStringWithMicroSecondStringNull()
{
	char *ret = lexema_append(strdup("Micro"), NULL);
	assert(!strcmp(ret, "Micro") && "must return the same string");
	free(ret);
}

static void firstStringWithMicroSecondStringNullChangingDelimiter()
{
	char *ret = lexema_append(strdup("\"Micro\""), NULL, '\'');
	assert(!strcmp(ret, "\'Micro\'") && "must return \'Micro\'");
	free(ret);
}

static void firstStringWithMicroSecondStringEmpty()
{
	char *ret = lexema_append(strdup("Micro"), strdup(""));
	assert(!strcmp(ret, "Micro") && "must return Micro");
	free(ret);
}

static void firstStringWithMicroSecondStringEmptyChangingDelimiter()
{
	char *ret = lexema_append(strdup("\"Micro\""), strdup("''"), '*');
	assert(!strcmp(ret, "*Micro*") && "must return *Micro*");
	free(ret);
}

static void firstStringWithMicroSecondStringCircuit()
{
	char *ret = lexema_append(strdup("Micro"), strdup("Circuit"));
	assert(!strcmp(ret, "MicroCircuit") && "must return MicroCircuit");
	free(ret);
}

static void firstStringWithMicroSecondStringCircuitChangingDelimiter()
{
	char *ret = lexema_append(strdup("\"Micro\""), strdup("'Circuit'"), '*');
	assert(!strcmp(ret, "*MicroCircuit*") && "must return *MicroCircuit*");
	free(ret);
}

static void sequence()
{
	char *rets[6];
	rets[0] = lexema_append(strdup("\"abacate\""), strdup("\", \""));
	rets[1] = lexema_append(rets[0], strdup("\"maca\""));
	rets[2] = lexema_append(rets[1], strdup("\", \""));
	rets[3] = lexema_append(rets[2], strdup("\"pera,\""));
	rets[4] = lexema_append(rets[3], strdup("\" e \""));
	rets[5] = lexema_append(rets[4], strdup("\"uva\""));

	assert(!strcmp("\"abacate\"\", \"\"maca\"\", \"\"pera,\"\" e \"\"uva\"", rets[5])
		&& "string is not correct");

	free(rets[5]);

	rets[0] = lexema_append(strdup("\"abacate\""), strdup("\", \""), '"');
	rets[1] = lexema_append(rets[0], strdup("\"maca\""), '"');
	rets[2] = lexema_append(rets[1], strdup("\", \""), '"');
	rets[3] = lexema_append(rets[2], strdup("\"pera,\""), '"');
	rets[4] = lexema_append(rets[3], strdup("\" e \""), '"');
	rets[5] = lexema_append(rets[4], strdup("\"uva\""), '"');

	assert(!strcmp("\"abacate, maca, pera, e uva\"", rets[5])
		&& "string is not correct");

	free(rets[5]);
}

void firstStringWithMaySecondWithGoReturnMayGo()
{
	char *par1 = strdup("May");
	char *par2 = strdup("Go");
	char *ret = lexema_cat(par1, par2);
	assert(!strcmp("MayGo", ret) && "must return MayGo");
	free(ret);
	ret = lexema_cat(par2, par1);
	assert(!strcmp("GoMay", ret) && "must return GoMay");
	free(ret);
	ret = lexema_cat(par2, par2);
	assert(!strcmp("GoGo", ret) && "must return GoGo");
	free(ret);
	free(par1);
	free(par2);
}

int main()
{
	firstStringNull();
	firstStringEmptySecondStringNull();
	firstStringEmptySecondStringNullChangingDelimiter();
	firstStringWithMicroSecondStringNull();
	firstStringWithMicroSecondStringNullChangingDelimiter();
	firstStringWithMicroSecondStringEmpty();
	firstStringWithMicroSecondStringEmptyChangingDelimiter();
	firstStringWithMicroSecondStringCircuit();
	firstStringWithMicroSecondStringCircuitChangingDelimiter();
	firstStringWithMaySecondWithGoReturnMayGo();
	sequence();
	return 0;
}
