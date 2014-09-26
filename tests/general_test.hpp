#pragma once

#include <cstdlib>
#include <sstream>
#include "Aslan_Context.hpp"

using namespace std;

typedef union YYSTYPE YYSTYPE;
typedef struct YYLTYPE YYLTYPE;

extern int Aslan_lex \
		   (YYSTYPE * yylval_param, YYLTYPE * yylloc_param ,void * yyscanner);
extern const char *Aslan_get_text \
		   (void * yyscanner);
extern int Aslan_get_lineno (void * yyscanner);

#define EXPECT(code, sem, loc, ac, yylex)				\
{														\
	int ret = yylex(sem, loc, ac.scanner);				\
	if (ret != code)									\
	{													\
		fprintf(stderr, "Expected: %d\n"				\
						"Returned: %d\n"				\
						"Token: '%s'\n"					\
						"Line: %d\n",					\
						code, ret,						\
						Aslan_get_text(ac.scanner),		\
						Aslan_get_lineno(ac.scanner));	\
		exit(1);										\
	}													\
}

#define MOC_DATA(LOCATION, SEMANTIC)					\
	char buf1[10];										\
	char buf2[16];										\
	YYLTYPE *LOCATION = (YYLTYPE *) buf1;				\
	YYSTYPE *SEMANTIC = (YYSTYPE *) buf2
