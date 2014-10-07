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

 /* remember that, the higher precedence is determined by the line number. So in the same rule, - + have less precedence then / *. -+ appears before / *. */
%%

translation_unit:
	  /* EMPTY */
	| aslan translation_unit
	;

aslan:
	  belief DOT_LITERAL
	| ACHIEVE function DOT_LITERAL
	| inner_plan DOT_LITERAL
	;

belief:
	function opt_context /* opt_context was optContextPlan */
	;

opt_context:
	  /* EMPTY */
	| CONTEXT assignment_expression
	;

function:
	opt_strong_negation IDENTIFIER opt_parms opt_annots
	;

opt_strong_negation:
	  /* EMPTY */
	| STRONG_NEGATION
	;

inner_plan:
	head_plan opt_context opt_actions /* opt_actions was optActionsPlan */
	;

head_plan:
	trigger_event event_type function_or_variable
	;

trigger_event:
	  PLUS
	| MINUS
	;

event_type:
	  /* EMPTY */
	| ACHIEVE
	| TEST
	;

function_or_variable:
	  function
	| variable
	;

variable:
	  NO_NAMED_VARIABLE
	| VARIABLE opt_parms opt_annots
	;

opt_parms:
	  /* EMPTY */
	| LEFTP opt_parms_list RIGHTP
	;

opt_parms_list:
	  /* EMPTY */
	| parms_list
	;

parms_list:
	  expression
	| expression COMMA parms_list
	;

opt_annots:
	  /* EMPTY */
	| LEFTB opt_array_list RIGHTB
	;

opt_array_list:
	  /* EMPTY */
	| array_list opt_tail
	;

array_list:
	  expression
	| expression COMMA array_list
	;

opt_tail:
	  /* EMPTY */
	| SEP expression
	;

opt_actions:
	  /* EMPTY */
	| POINTER actions
	;

actions:
	  assignment_expression
	| assignment_expression SEQUENCE actions
	;

assignment_expression:
	  expression
	| expression ASSIGNMENT assignment_expression
	;

expression:
	ERR
	;
