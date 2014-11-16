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
%expect 0

%{
	#include <iostream>
	#include <cstring>
	#include "Aslan_Context.hpp"
	#include "AllSymbol.hpp"
	#include "Utils.hpp" /* I hate this name, but */
%}


%union
{
	char *lexema;	/* To access a yytext equivalent */
	Symbol *symbol;	/* To hold a pointer of Symbol */
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
%type <lexema> opt_strong_negation literal
%type <symbol> trigger_event event_type
%type <symbol> unary_op math_op relational_op
%type <symbol> assignment_expression
%type <symbol> conditional_expression math_expression
%type <symbol> simple_expression function_or_variable
%type <symbol> opt_array_list opt_parms opt_annots
%type <symbol> function opt_parms_list parms_list
%type <symbol> array_list opt_tail variable
%type <symbol> opt_actions actions opt_context
%type <symbol> head_plan inner_plan aslan belief

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
%destructor { free($$); } opt_strong_negation literal
%destructor { delete($$); } assignment_expression
%destructor { delete($$); } conditional_expression math_expression
%destructor { delete($$); } simple_expression function_or_variable
%destructor { delete($$); } opt_array_list opt_parms opt_annots
%destructor { delete($$); } function opt_parms_list parms_list
%destructor { delete($$); } array_list opt_tail variable
%destructor { delete($$); } opt_actions actions opt_context
%destructor { delete($$); } head_plan inner_plan aslan belief
%destructor { delete($$); } trigger_event event_type
%destructor { delete($$); } unary_op math_op relational_op

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
		{ context->output()[0] << $1; }
	;

aslan:
	  belief DOT_LITERAL
		{
			free($2);
			$$ = $1;
		}
	| ACHIEVE function DOT_LITERAL
		{
			free($1);
			free($3);
			$$ = $2;
		}
	| inner_plan DOT_LITERAL
		{
			free($2);
			$$ = $1;
		}
	;

belief:
	function opt_context
		{ $$ = new Belief($1, $2); }
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
				@2.first_line,
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
	head_plan opt_context opt_actions
		{ $$ = ((Plan*) $1)->addContext($2)->addAction($3); }
	;

head_plan:
	trigger_event event_type function_or_variable
		{ $$ = new Plan((Trigger*) $1, (EventType*) $2, $3); }
	;

trigger_event:
	  PLUS
		{ $$ = new AdditionTrigger(@1.first_line, $1); }
	| MINUS
		{ $$ = new DeletionTrigger(@1.first_line, $1); }
	;

event_type:
	  /* EMPTY */
		{ $$ = new BeliefEvent(); }
	| ACHIEVE
		{ $$ = new GoalEvent(@1.first_line, $1); }
	| TEST
		{ $$ = new TestEvent(@1.first_line, $1); }
	;

function_or_variable:
	  function
		{ $$ = $1; }
	| variable
		{ $$ = $1; }
	;

variable:
	  NO_NAMED_VARIABLE
		{ $$ = new Functor(@1.first_line, $1); }
	| opt_strong_negation VARIABLE opt_parms opt_annots
		{
			$$ = new Functor(
				@2.first_line,
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
		{
			Parameter *par = new Parameter(@1.first_line, $1);
			$$ = par;
		}
	| math_expression COMMA parms_list
		{
			free($2);
			((Parameter *) $3)->push($1);
			$$ = $3;
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
		{
			ConstantExpression *ce = new ConstantExpression(0, strdup("_"));
			// It's need to pass a valid symbol here... :'(
			Array *aux = new Array(0, ce);
			aux->pop();
			$$ = aux;
		}
	| array_list opt_tail
		{
			((Array*)$1)->setTail($2);
			$$ = $1;
		}
	;

array_list:
	  conditional_expression
		{ $$ = new Array(@1.first_line, $1); }
	| conditional_expression COMMA array_list
		{
			free($2);
			((Array*)$3)->push($1);
			$$ = $3;
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
		{ $$ = new Action(@1.first_line, $1); }
	| assignment_expression SEQUENCE actions
		{
			free($2);
			((Action *)$3)->push($1);
			$$ = $3;
		}
	;

assignment_expression:
	  math_expression
		{ $$ = $1; }
	| math_expression ASSIGNMENT assignment_expression
		{
			free($2);
			Expression *aux = new Expression($1);
			aux->add($3);
			aux->setOp(ASSIGNMENT);
			$$ = aux;
		}
	;

math_expression:
	  conditional_expression
		{ $$ = $1; }
	| conditional_expression math_op math_expression
		{
			Expression *aux = new Expression($1);
			aux->add($3);
			aux->setOp(((Expression *) $2)->op());
			delete $2;
			$$ = aux;
		}
	;

conditional_expression:
	  simple_expression
		{ $$ = $1; }
	| unary_op simple_expression
		{
			Expression *aux = new Expression($2);
			aux->setOp(((Expression *) $1)->op());
			delete $1;
			$$ = aux;
		}
	| simple_expression relational_op conditional_expression
		{
			Expression *aux = new Expression($1);
			aux->add($3);
			aux->setOp(((Expression *) $2)->op());
			delete $2;
			$$ = aux;
		}
	;

relational_op:
	  AND_BIT
		{
			$$ = new ConstantExpression(@1.first_line, $1);
		}
	| OR_BIT
		{
			$$ = new ConstantExpression(@1.first_line, $1);
		}
	| XOR_BIT
		{
			$$ = new ConstantExpression(@1.first_line, $1);
		}
	| AND_LOGIC
		{
			$$ = new ConstantExpression(@1.first_line, $1);
		}
	| OR_LOGIC
		{
			$$ = new ConstantExpression(@1.first_line, $1);
		}
	| EQUAL_CMP
		{
			$$ = new ConstantExpression(@1.first_line, $1);
		}
	| DIFFERENT_CMP
		{
			$$ = new ConstantExpression(@1.first_line, $1);
		}
	| LESSEQUAL
		{
			$$ = new ConstantExpression(@1.first_line, $1);
		}
	| LESS
		{
			$$ = new ConstantExpression(@1.first_line, $1);
		}
	| GREATEQUAL
		{
			$$ = new ConstantExpression(@1.first_line, $1);
		}
	| GREAT
		{
			$$ = new ConstantExpression(@1.first_line, $1);
		}
	;

math_op:
	  SHIFTLEFT
		{
			$$ = new ConstantExpression(@1.first_line, $1);
		}
	| SHIFTRIGHT
		{
			$$ = new ConstantExpression(@1.first_line, $1);
		}
	| PLUS
		{
			$$ = new ConstantExpression(@1.first_line, $1);
		}
	| MINUS
		{
			$$ = new ConstantExpression(@1.first_line, $1);
		}
	| MUL
		{
			$$ = new ConstantExpression(@1.first_line, $1);
		}
	| DIV
		{
			$$ = new ConstantExpression(@1.first_line, $1);
		}
	| MOD
		{
			$$ = new ConstantExpression(@1.first_line, $1);
		}
	;


unary_op:
	  NOT
		{
			$$ = new ConstantExpression(@1.first_line, $1);
		}
	| PLUS
		{
			$$ = new ConstantExpression(@1.first_line, $1);
		}
	| MINUS
		{
			$$ = new ConstantExpression(@1.first_line, $1);
		}
	| ACHIEVE
		{
			$$ = new ConstantExpression(@1.first_line, $1);
		}
	| TEST
		{
			$$ = new ConstantExpression(@1.first_line, $1);
		}
	;

simple_expression:
	  literal
		{ $$ = new ConstantExpression(@1.first_line, $1); }
	| function_or_variable
		{ $$ = $1; }
	| opt_strong_negation EXTERNAL_ACTION opt_parms opt_annots
		{
			$$ = new Functor(
				@2.first_line,
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
