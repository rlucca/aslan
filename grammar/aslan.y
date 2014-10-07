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
	char *lexema;	/* To access a yytext equivalent */
}

%token ERR
%token <lexema> CHAR_STRING_LITERAL STRING_LITERAL
%token <lexema> FLOAT_LITERAL NUMBER_LITERAL
%token <lexema> DOT_LITERAL NOT
%token <lexema> LEFTP RIGHTP
%token <lexema> LEFTB RIGHTB
%token <lexema> LEFTK RIGHTK
%token <lexema> DIV MOD MUL PLUS MINUS TEST COMMA
%token <lexema> CONTEXT SEQUENCE STRONG_NEGATION
%token <lexema> XOR_BIT DIFFERENT_CMP ACHIEVE
%token <lexema> EQUAL_CMP ASSIGNMENT
%token <lexema> AND_LOGIC AND_BIT
%token <lexema> OR_LOGIC OR_BIT SEP
%token <lexema> SHIFTLEFT LESSEQUAL POINTER LESS
%token <lexema> SHIFTRIGHT GREATEQUAL GREAT
%token <lexema> NO_NAMED_VARIABLE VARIABLE
%token <lexema> IDENTIFIER EXTERNAL_ACTION

%destructor { free($$); } CHAR_STRING_LITERAL STRING_LITERAL
%destructor { free($$); } FLOAT_LITERAL NUMBER_LITERAL
%destructor { free($$); } DOT_LITERAL NOT
%destructor { free($$); } LEFTP RIGHTP
%destructor { free($$); } LEFTB RIGHTB
%destructor { free($$); } LEFTK RIGHTK
%destructor { free($$); } DIV MOD MUL PLUS MINUS TEST COMMA
%destructor { free($$); } CONTEXT SEQUENCE STRONG_NEGATION
%destructor { free($$); } XOR_BIT DIFFERENT_CMP ACHIEVE
%destructor { free($$); } EQUAL_CMP ASSIGNMENT
%destructor { free($$); } AND_LOGIC AND_BIT
%destructor { free($$); } OR_LOGIC OR_BIT SEP
%destructor { free($$); } SHIFTLEFT LESSEQUAL POINTER LESS
%destructor { free($$); } SHIFTRIGHT GREATEQUAL GREAT
%destructor { free($$); } NO_NAMED_VARIABLE VARIABLE
%destructor { free($$); } IDENTIFIER EXTERNAL_ACTION

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
	#define destroy_lexema(LEXEMA)	\
		free(LEXEMA);		\
		LEXEMA = NULL
%}

%start translation_unit

%%

translation_unit:
	  /* EMPTY */
	| translation_unit aslan
	;

aslan:
	IDENTIFIER	{ cout << $1 << "(" << @1.first_line << ")\n"; destroy_lexema($1); }
	;
