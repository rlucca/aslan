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

%{
	#include <iostream>
	#include "Aslan_Context.hpp"
	#include "Utils.hpp" /* I hate this name, but */

enum
{
	NO_OPERATION = 0,
	UNARY_TEST = 1,
	UNARY_ACHIEVE = 2,
	UNARY_MINUS = 3,
	UNARY_PLUS = 4,
	UNARY_NOT = 5,
};

class Expression // TODO move this to other file
{ public:
	Expression(void *, void*, int) {}
	Expression(void *, int = 0) {}
};
class Array {
 public:
	Array(void *, void*, int) {}
	Array(void *, int = 0) {}
};
class Functor {
 public:
	Functor(const char *, void*, void*) {}
};

%}


%union
{
	char *lexema;	/* To access a yytext equivalent */
	void *symbol;	/* To hold a pointer of Symbol */
	int type;	/* To hold an indentifier */
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

%type <lexema> char_string_literal string_literal
%type <lexema> opt_strong_negation
%type <type> unary_op
%type <symbol> literal

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
%destructor { free($$); } char_string_literal string_literal
%destructor { free($$); } opt_strong_negation
%destructor { delete($$); } literal

%{
	using namespace std;

	int Aslan_lex(YYSTYPE* lvalp, YYLTYPE* llocp, void *scanner);
	void Aslan_error(YYLTYPE* locp, Aslan_Context* context, const char* err);

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
		{ $$ = strdup(""); }
	| STRONG_NEGATION
		{ $$ = $1; }
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
	| opt_strong_negation VARIABLE opt_parms opt_annots
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
	  math_expression
	| math_expression COMMA parms_list
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
	  conditional_expression
	| conditional_expression COMMA array_list
	;

opt_tail:
	  /* EMPTY */
	| SEP conditional_expression
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
	  conditional_expression
	| conditional_expression ASSIGNMENT assignment_expression
	;

conditional_expression:
	  math_expression
	| simple_expression AND_BIT conditional_expression
	| simple_expression OR_BIT conditional_expression
	| simple_expression XOR_BIT conditional_expression
	| simple_expression AND_LOGIC conditional_expression
	| simple_expression OR_LOGIC conditional_expression
	| simple_expression EQUAL_CMP conditional_expression
	| simple_expression DIFFERENT_CMP conditional_expression
	| simple_expression LESSEQUAL conditional_expression
	| simple_expression LESS conditional_expression
	| simple_expression GREATEQUAL conditional_expression
	| simple_expression GREAT conditional_expression
	;

math_expression:
	  simple_expression
	| unary_op simple_expression
	| simple_expression SHIFTLEFT math_expression
	| simple_expression SHIFTRIGHT math_expression
	| simple_expression PLUS math_expression
	| simple_expression MINUS math_expression
	| simple_expression MUL math_expression
	| simple_expression DIV math_expression
	| simple_expression MOD math_expression
	;

unary_op:
	  NOT
		{
			free($1);
			$$ = UNARY_NOT;
		}
	| PLUS
		{
			free($1);
			$$ = UNARY_PLUS;
		}
	| MINUS
		{
			free($1);
			$$ = UNARY_MINUS;
		}
	| ACHIEVE
		{
			free($1);
			$$ = UNARY_ACHIEVE;
		}
	| TEST
		{
			free($1);
			$$ = UNARY_TEST;
		}
	;

simple_expression:
	  literal
	| function_or_variable
	| opt_strong_negation EXTERNAL_ACTION opt_parms opt_annots
	| LEFTB opt_array_list RIGHTB
	| LEFTP assignment_expression RIGHTP
	;

literal:
	  NUMBER_LITERAL
		{ $$ = $1; }
	| FLOAT_LITERAL
		{ $$ = $1; }
	| char_string_literal
		{ $$ = $1; }
	| string_literal
		{ $$ = $1; }
	;

char_string_literal:
	  CHAR_STRING_LITERAL
		{ $$ = $1; }
	| CHAR_STRING_LITERAL char_string_literal
		{ $$ = lexema_append($1, $2, '"'); }
	;

string_literal:
	  STRING_LITERAL
		{ $$ = $1; }
	| STRING_LITERAL string_literal
		{ $$ = lexema_append($1, $2, '"'); }
	;

%%

	void Aslan_error(YYLTYPE* locp, Aslan_Context* context, const char* err)
	{
		(void) context;
		cout << locp->first_line << ":" << err << endl;
	}
