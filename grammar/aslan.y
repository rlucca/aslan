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
	#include <cstring>
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
	BINARY_MOD = 6,
	BINARY_DIVIDE = 7,
	BINARY_MULTIPLY = 8,
	BINARY_MINUS = 9,
	BINARY_PLUS = 10,
	BINARY_SHIFTRIGHT = 11,
	BINARY_SHIFTLEFT = 12,
	BINARY_GREAT = 13,
	BINARY_GREATEQUAL = 14,
	BINARY_LESS = 15,
	BINARY_LESSEQUAL = 16,
	BINARY_DIFFERENT_CMP = 17,
	BINARY_EQUAL_CMP = 18,
	BINARY_OR_LOGIC = 19,
	BINARY_AND_LOGIC = 20,
	BINARY_XOR_BIT = 21,
	BINARY_OR_BIT = 22,
	BINARY_AND_BIT = 23,
	BINARY_ASSIGNMENT = 24,
	EVENT_ABOUT_TEST = 25,
	EVENT_ABOUT_GOAL = 26,
	EVENT_ABOUT_BELIEF = 27,
	REMOVE_TRIGGER = 28,
	INSERT_TRIGGER = 29
};

class Expression // TODO move this to other file
{ public:
	Expression(void *, void*, int) {}
	Expression(void *, int = 0) {}
};
class Stack {
 public:
	void *push(void *) { return 0; }
	void pop() {}
	void *top() { return 0; }
};
class Array : public Stack {
 public:
	Array(void *) : Stack() {}
	void *setTail(void *) { return 0; }
};
class Actions : public Stack {
 public:
	Actions(void *) : Stack() {}
};
class Parameters {
 public:
	Parameters(void *, void* = 0) {}
};
class Functor {
 public:
	Functor(const char *, void* = NULL, void* = NULL) {}
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
%type <type> unary_op math_op relational_op
%type <type> trigger_event event_type
%type <symbol> literal assignment_expression
%type <symbol> conditional_expression math_expression
%type <symbol> simple_expression function_or_variable
%type <symbol> opt_array_list opt_parms opt_annots
%type <symbol> function opt_parms_list parms_list
%type <symbol> array_list opt_tail variable
%type <symbol> opt_actions actions opt_context

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
%destructor { delete($$); } literal assignment_expression
%destructor { delete($$); } conditional_expression math_expression
%destructor { delete($$); } simple_expression function_or_variable
%destructor { delete($$); } opt_array_list opt_parms opt_annots
%destructor { delete($$); } function opt_parms_list parms_list
%destructor { delete($$); } array_list opt_tail variable
%destructor { delete($$); } opt_actions actions opt_context

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
		{ $$ = NULL; }
	| CONTEXT assignment_expression
		{
			free($1);
			$$ = $2;
		}
	;

function:
	opt_strong_negation IDENTIFIER opt_parms opt_annots
		{
			$$ = new Functor(
				lexema_append($1, $2),
				$3,
				$4);
		}
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
		{
			free($1);
			$$ = INSERT_TRIGGER;
		}
	| MINUS
		{
			free($1);
			$$ = REMOVE_TRIGGER;
		}
	;

event_type:
	  /* EMPTY */
		{
			$$ = EVENT_ABOUT_BELIEF;
		}
	| ACHIEVE
		{
			free($1);
			$$ = EVENT_ABOUT_GOAL;
		}
	| TEST
		{
			free($1);
			$$ = EVENT_ABOUT_TEST;
		}
	;

function_or_variable:
	  function
		{ $$ = $1; }
	| variable
		{ $$ = $1; }
	;

variable:
	  NO_NAMED_VARIABLE
		{ $$ = new Functor($1); }
	| opt_strong_negation VARIABLE opt_parms opt_annots
		{
			$$ = new Functor(
				lexema_append($1, $2),
				$3,
				$4);
		}
	;

opt_parms:
	  /* EMPTY */
		{ $$ = NULL; }
	| LEFTP opt_parms_list RIGHTP
		{
			free($1);
			free($3);
			$$ = $2;
		}
	;

opt_parms_list:
	  /* EMPTY */
		{ $$ = NULL; }
	| parms_list
		{ $$ = $1; }
	;

parms_list:
	  math_expression
		{ $$ = new Parameters($1); }
	| math_expression COMMA parms_list
		{
			free($2);
			$$ = new Parameters($1, $3);
		}
	;

opt_annots:
	  /* EMPTY */
		{ $$ = NULL; }
	| LEFTB opt_array_list RIGHTB
		{
			free($1);
			free($3);
			$$ = $2;
		}
	;

opt_array_list:
	  /* EMPTY */
		{ $$ = NULL; }
	| array_list opt_tail
		{ $$ = ((Array*)$1)->setTail($2); }
	;

array_list:
	  conditional_expression
		{ $$ = new Array($1); }
	| conditional_expression COMMA array_list
		{
			free($2);
			$$ = ((Array*)$3)->push($1); // Array is a stack of elements
		}
	;

opt_tail:
	  /* EMPTY */
		{ $$ = NULL; }
	| SEP conditional_expression
		{
			free($1);
			$$ = $2;
		}
	;

opt_actions:
	  /* EMPTY */
		{ $$ = NULL; }
	| POINTER actions
		{
			free($1);
			$$ = $2;
		}
	;

actions:
	  assignment_expression
		{ $$ = new Actions($1); }
	| assignment_expression SEQUENCE actions
		{
			free($2);
			$$ = ((Actions *)$3)->push($1);
		}
	;

assignment_expression:
	  conditional_expression
		{ $$ = $1; }
	| conditional_expression ASSIGNMENT assignment_expression
		{ $$ = new Expression($1, $3, BINARY_ASSIGNMENT); }
	;

conditional_expression:
	  math_expression
		{ $$ = $1; }
	| simple_expression relational_op conditional_expression
		{ $$ = new Expression($1, $3, $2); }
	;

relational_op:
	  AND_BIT
		{
			free($1);
			$$ = BINARY_AND_BIT;
		}
	| OR_BIT
		{
			free($1);
			$$ = BINARY_OR_BIT;
		}
	| XOR_BIT
		{
			free($1);
			$$ = BINARY_XOR_BIT;
		}
	| AND_LOGIC
		{
			free($1);
			$$ = BINARY_AND_LOGIC;
		}
	| OR_LOGIC
		{
			free($1);
			$$ = BINARY_OR_LOGIC;
		}
	| EQUAL_CMP
		{
			free($1);
			$$ = BINARY_EQUAL_CMP;
		}
	| DIFFERENT_CMP
		{
			free($1);
			$$ = BINARY_DIFFERENT_CMP;
		}
	| LESSEQUAL
		{
			free($1);
			$$ = BINARY_LESSEQUAL;
		}
	| LESS
		{
			free($1);
			$$ = BINARY_LESS;
		}
	| GREATEQUAL
		{
			free($1);
			$$ = BINARY_GREATEQUAL;
		}
	| GREAT
		{
			free($1);
			$$ = BINARY_GREAT;
		}
	;

math_expression:
	  simple_expression
		{ $$ = $1; }
	| unary_op simple_expression
		{ $$ = new Expression($2, $1); }
	| simple_expression math_op math_expression
		{ $$ = new Expression($1, $3, $2); }
	;

math_op:
	  SHIFTLEFT
		{
			free($1);
			$$ = BINARY_SHIFTLEFT;
		}
	| SHIFTRIGHT
		{
			free($1);
			$$ = BINARY_SHIFTRIGHT;
		}
	| PLUS
		{
			free($1);
			$$ = BINARY_PLUS;
		}
	| MINUS
		{
			free($1);
			$$ = BINARY_MINUS;
		}
	| MUL
		{
			free($1);
			$$ = BINARY_MULTIPLY;
		}
	| DIV
		{
			free($1);
			$$ = BINARY_DIVIDE;
		}
	| MOD
		{
			free($1);
			$$ = BINARY_MOD;
		}
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
		{ $$ = new Expression($1); }
	| function_or_variable
		{ $$ = $1; }
	| opt_strong_negation EXTERNAL_ACTION opt_parms opt_annots
		{
			$$ = new Functor(
				lexema_append($1, $2),
				$3,
				$4);
		}
	| LEFTB opt_array_list RIGHTB
		{
			free($1);
			free($3);
			$$ = $2;
		}
	| LEFTP assignment_expression RIGHTP
		{
			free($1);
			free($3);
			$$ = $2;
		}
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
