/*
vim:noexpandtab:ts=8 sw=8
*/
%pure-parser
%name-prefix="Aslan_"
%locations
%defines
%error-verbose
%parse-param {Aslan_Context* context }
%lex-param { void* scanner  }

%union
{
	long long numerical;
	double fractional;
	char* cptr;
}

/*%token <numerical> A
%token <fractional> B
%token <cptr> ESCAPE */
%token ERR
%token CHAR_STRING_LITERAL STRING_LITERAL
%token FLOAT_LITERAL DOT_LITERAL

%type <numerical> aslan

%{
	#include <iostream>
	#include "Aslan_Context.hpp"

	using namespace std;

	int Aslan_lex(YYSTYPE* lvalp, YYLTYPE* llocp, void *scanner);

	void Aslan_error(YYLTYPE* locp, Aslan_Context* context, const char* err)
	{
		(void) context;
		cout << locp->first_line << ":" << err << endl;
	}

	#define scanner context->scanner
%}

%%

/*start:
	  aslan
	;

aslan :
	  A aslan
	  	{ $$ = $1 + $2; }
	| B aslan
		{ $$ = $1 + $2; }
	| ESCAPE aslan
		{
			{
				//istringstream* is = new istringstream($1);
				//LanCD_Context context(is);
				//LanCD_parse(&context);
				//$$ = context.result + $2;
				$$ = $2;
			}
		}
	| // * empty * /
		{ $$ = 0; }
	;
*/

start:
	aslan
	;

aslan:
	/* empty */	{ $$ = 0; }
	;
