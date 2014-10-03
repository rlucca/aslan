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
	char *lexema;	/* To access the yytext */
}

%token ERR
%token CHAR_STRING_LITERAL STRING_LITERAL
%token FLOAT_LITERAL DOT_LITERAL
%token LEFTP RIGHTP
%token LEFTB RIGHTB
%token LEFTK RIGHTK
%token DIV
%token MOD
%token MUL
%token PLUS
%token MINUS
%token TEST
%token COMMA
%token CONTEXT
%token SEQUENCE
%token STRONG_NEGATION
%token XOR_BIT
%token DIFFERENT_CMP
%token ACHIEVE
%token EQUAL_CMP
%token ASSIGNMENT
%token AND_LOGIC
%token AND_BIT
%token OR_LOGIC
%token OR_BIT
%token SEP
%token SHIFTLEFT
%token LESSEQUAL
%token POINTER
%token LESS
%token SHIFTRIGHT
%token GREATEQUAL
%token GREAT
%token NOT
%token VARIABLE
%token <lexema> IDENTIFIER
%token EXTERNAL_ACTION
%token NUMBER_LITERAL

%destructor { free($$); } IDENTIFIER

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

start:
	aslan
	;

aslan:
	/* empty */	{ ; }
	| IDENTIFIER	{ cout << $1 << "(" << @1.first_line << ")\n"; }
	;
