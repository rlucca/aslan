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

#define TOKEN_ERR 3
#define LEXEMA_ERR 4

#define CREATE_LEX_DATA(PTR_INPUT)						\
	Aslan_Context _ac(PTR_INPUT);						\
	YYSTYPE _buf1;										\
	YYLTYPE _buf2;										\
	YYSTYPE *_semantic = &_buf1;						\
	YYLTYPE *_location = &_buf2;						\
	int _token_code = 0

#define NEXT											\
	_token_code = Aslan_lex(_semantic, _location, _ac.scanner)

#define DUMP_POSITION									\
		cerr << "Token: " << _token_code << "\n"		\
		     << "Lexema: '"								\
				<< Aslan_get_text(_ac.scanner) << "'\n"	\
			<< "Line: " << Aslan_get_lineno(_ac.scanner)\
			<< "\n"


#define EXPECTING_TOKEN(TOKEN)							\
		if (_token_code != TOKEN)						\
		{												\
			cerr << "Expected Token: " << TOKEN << "\n";\
			DUMP_POSITION;								\
			free(_semantic->lexema);					\
			exit(TOKEN_ERR);							\
		}

#define NOT_EXPECTING_TOKEN(TOKEN)						\
		if (_token_code == TOKEN)						\
		{												\
			cerr << "Not Expecting Token: " << TOKEN	\
				<< "\n";								\
			DUMP_POSITION;								\
			free(_semantic->lexema);					\
			exit(TOKEN_ERR);							\
		}

#define DESTROY_LEXEMA									\
	free(_semantic->lexema);							\
	_semantic->lexema = NULL

#define EXPECTING_LEXEMA(TEXT)							\
	if (strcmp(TEXT, _semantic->lexema))				\
	{													\
		cerr << "Expected Lexema: " << TEXT << "\n";	\
		DUMP_POSITION;									\
		DESTROY_LEXEMA;									\
		exit(LEXEMA_ERR);								\
	}													\

#define NOT_EXPECTING_LEXEMA(TEXT)						\
	if (!strcmp(TEXT, _semantic->lexema))				\
	{													\
		cerr << "Not Expecting Lexema: " << TEXT		\
				<< "\n";								\
		DUMP_POSITION;									\
		DESTROY_LEXEMA;									\
		exit(LEXEMA_ERR);								\
	}													\

