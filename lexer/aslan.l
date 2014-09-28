/*
	vim:noexpandtab:ts=8 sw=8
*/

 /* Lexer options */
%option reentrant
%option prefix="Aslan_"
%option bison-bridge
%option bison-locations
%option noyywrap
%option yylineno
%option array
%option stack

 /* caution */
%option nounput

OCTALS				[01234567]
INFIX_FLOAT			[eE][+-]?[0-9]+
SUFFIX_FLOAT			[0-9]+{INFIX_FLOAT}?

%{
#include "Aslan_Context.hpp"
#include "aslan_parser.hpp"

void Aslan_lexerror(const char* err, yyscan_t scanner);

#define YY_EXTRA_TYPE Aslan_Context *
#define YY_USER_ACTION yylloc->first_line = yylineno;

#define YY_INPUT(buf, result, max_size)	\
{					\
	char c;				\
	(*yyextra->is) >> c;		\
	if(yyextra->is->eof())		\
		result = YY_NULL;	\
	else				\
	{				\
		buf[0] = c;		\
		result = 1;		\
	}				\
}

#define YY_FATAL_ERROR(msg) Aslan_lexerror( msg , yyscanner)
#define PUSH_STATE(state) yy_push_state(state, yyscanner)
#define POP_STATE() yy_pop_state(yyscanner)

%}

 /* comment state */
%x IGNORE
 /* char string state */
%x CS
 /* multichar string state */
%x SS
 /* understanding and transform a escaped char */
%x ESCAPE_CHAR

%%

"//".*			/* IGNORE */
"/*"			{
			PUSH_STATE(IGNORE);
			}
\'			{
			yymore();
			PUSH_STATE(CS);
			}
\"			{
			yymore();
			PUSH_STATE(SS);
			}
\.{SUFFIX_FLOAT}	return FLOAT_LITERAL;
\.			return DOT_LITERAL;
[[:blank:]]		/* IGNORE */
.           		{
			YY_FATAL_ERROR("Invalid Char");
			return ERR;
			}
\n			/* IGNORE */
<INITIAL><<EOF>>	return 0;
<<EOF>>			{
			YY_FATAL_ERROR("Unexpected end of file");
			return ERR;
			}

<IGNORE>"*/"		POP_STATE();
<IGNORE>.		/* IGNORE */
<IGNORE>\n		/* IGNORE */

<CS>\'			{
			POP_STATE();
			return CHAR_STRING_LITERAL;
			}
<SS>\"			{
			POP_STATE();
			return STRING_LITERAL;
			}
<CS,SS>\\		{
			yymore();
			PUSH_STATE(ESCAPE_CHAR);
			}
<CS,SS>.		yymore();
<CS,SS>\n		{
			YY_FATAL_ERROR("Unexpected end of line");
			return ERR;
			}

<ESCAPE_CHAR>{OCTALS}{1,3}	{
				/* Because I can reach here from
				   string, I can't garantee that
				   just  the first caracter is
				   the alien. So I can't translate
				   to a unique char right now */
				yymore();
				POP_STATE();
				}
<ESCAPE_CHAR>.		{
			yymore();
			POP_STATE();
			}

%%

void Aslan_Context::init_scanner()
{
	yylex_init(&scanner);
	yyset_extra(this, scanner);
	yy_push_state(0, scanner);
}

void Aslan_Context::destroy_scanner()
{
	yy_pop_state(scanner);
	yylex_destroy(scanner);
}

void Aslan_lexerror(const char* err, yyscan_t scanner)
{
	cerr << Aslan_get_lineno(scanner) << ": "
		<< "Error: " << err
		<< " (State: " << yy_top_state(scanner)
		<< ")\n";
	exit( YY_EXIT_FAILURE );
}
