#pragma once

#include <cstdlib>
#include <sstream>
#include <cstring>
#include "Aslan_Context.hpp"
#include "aslan_parser.hpp"

using namespace std;

typedef union YYSTYPE YYSTYPE;
typedef struct YYLTYPE YYLTYPE;

extern int Aslan_lex \
		   (YYSTYPE * yylval_param, YYLTYPE * yylloc_param ,void * yyscanner);
extern const char *Aslan_get_text \
		   (void * yyscanner);
extern int Aslan_get_lineno (void * yyscanner);

#define EXPECT_LEX(code, sem, loc, ac, yylex)			\
{														\
	int ret = yylex(sem, loc, ac.scanner);				\
	if (ret != code)									\
	{													\
		cerr << "Expected: " << code << "\n"			\
			 << "Returned: " << ret << "\n"				\
			 << "Token: '"								\
				<< Aslan_get_text(ac.scanner) << "'\n"	\
			 << "Line: "								\
				<< Aslan_get_lineno(ac.scanner) << "\n";\
		exit(1);										\
	}													\
}

#define EXPECT_TOKEN_LEX(token, ac)						\
{														\
	if (strcmp(token, Aslan_get_text(ac.scanner)))		\
	{													\
		cerr << "Expected: " << token << "\n"			\
			 << "Returned: "							\
				<< Aslan_get_text(ac.scanner) << "\n"	\
			 << "Line: "								\
				<< Aslan_get_lineno(ac.scanner) << "\n";\
		exit(2);										\
	}													\
}

#define NOT_EXPECT_TOKEN_LEX(token, ac)					\
{														\
	if (!strcmp(token, Aslan_get_text(ac.scanner)))		\
	{													\
		cerr << "Not Expected: " << token << "\n"		\
			 << "Returned: "							\
				<< Aslan_get_text(ac.scanner) << "\n"	\
			 << "Line: "								\
				<< Aslan_get_lineno(ac.scanner) << "\n";\
		exit(2);										\
	}													\
}

#define MOC_LEX_DATA(LOCATION, SEMANTIC)				\
	char buf1[10];										\
	char buf2[16];										\
	YYLTYPE *LOCATION = (YYLTYPE *) buf1;				\
	YYSTYPE *SEMANTIC = (YYSTYPE *) buf2
