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
%token <lexema> FLOAT_LITERAL NUMBER_LITERAL
%token <lexema> LEFTP RIGHTP DOT_LITERAL
%token <lexema> LEFTB RIGHTB NOT
%token <lexema> LEFTK RIGHTK STRONG_NEGATION
%token <lexema> CONTEXT SEQUENCE TEST COMMA
%token <lexema> ACHIEVE ASSIGNMENT POINTER
%token <lexema> NO_NAMED_VARIABLE VARIABLE
%token <lexema> IDENTIFIER EXTERNAL_ACTION
%right <lexema> CHAR_STRING_LITERAL STRING_LITERAL
%right <lexema> DIV MOD MUL PLUS MINUS
%right <lexema> XOR_BIT DIFFERENT_CMP EQUAL_CMP
%right <lexema> AND_LOGIC AND_BIT
%right <lexema> OR_LOGIC OR_BIT SEP
%right <lexema> SHIFTLEFT LESSEQUAL LESS
%right <lexema> SHIFTRIGHT GREATEQUAL GREAT

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
	  simple_expression
	| unary_op simple_expression
	| simple_expression AND_BIT expression
	| simple_expression OR_BIT expression
	| simple_expression XOR_BIT expression
	| simple_expression AND_LOGIC expression
	| simple_expression OR_LOGIC expression
	| simple_expression EQUAL_CMP expression
	| simple_expression DIFFERENT_CMP expression
	| simple_expression LESSEQUAL expression
	| simple_expression LESS expression
	| simple_expression GREATEQUAL expression
	| simple_expression GREAT expression
	| simple_expression SHIFTLEFT expression
	| simple_expression SHIFTRIGHT expression
	| simple_expression PLUS expression
	| simple_expression MINUS expression
	| simple_expression MUL expression
	| simple_expression DIV expression
	| simple_expression MOD expression
	;

unary_op:
	  NOT
	| PLUS
	| MINUS
	| ACHIEVE
	| TEST
	;

simple_expression:
	  function_or_variable
	| EXTERNAL_ACTION opt_parms opt_annots
	| literals
	| LEFTP assignment_expression RIGHTP
	| LEFTB opt_array_list RIGHTB
	;

literals:
	  NUMBER_LITERAL
	| FLOAT_LITERAL
	| char_string_literal
	| string_literal
	;

char_string_literal:
	  CHAR_STRING_LITERAL
	| CHAR_STRING_LITERAL char_string_literal
	;

string_literal:
	  STRING_LITERAL
	| STRING_LITERAL string_literal
	;
