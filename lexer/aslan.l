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
[[:blank:]]		/* IGNORE */
.           		{
			YY_FATAL_ERROR("Invalid Char");
			return ERR;
			}
\n			/* IGNORE */

<IGNORE>"*/"		POP_STATE();
<IGNORE>.		/* IGNORE */
<IGNORE>\n		/* IGNORE */
<IGNORE><<EOF>>		{
			YY_FATAL_ERROR("Unexpected end of file");
			return ERR;
			}

<CS>\'			{
			cout << yytext << "\n";
			POP_STATE();
			}
<CS>\\			{
			yymore();
			PUSH_STATE(ESCAPE_CHAR);
			}
<CS>.			yymore();
<CS>\n			{
			YY_FATAL_ERROR("Unexpected end of line");
			return ERR;
			}
<CS><<EOF>>		{
			YY_FATAL_ERROR("Unexpected end of file");
			return ERR;
			}

<ESCAPE_CHAR>\\		POP_STATE();
<ESCAPE_CHAR>n		POP_STATE();
<ESCAPE_CHAR>t		POP_STATE();
<ESCAPE_CHAR>r		POP_STATE();
<ESCAPE_CHAR>b		POP_STATE();
<ESCAPE_CHAR>f		POP_STATE();

<ESCAPE_CHAR>{OCTALS}{1,3}	{
				/* 0 to 377 */
				POP_STATE();
				}
<ESCAPE_CHAR>.		POP_STATE();

%%

void Aslan_Context::init_scanner()
{
	yylex_init(&scanner);
	yyset_extra(this, scanner);
}

void Aslan_Context::destroy_scanner()
{
	yylex_destroy(scanner);
}

void Aslan_lexerror(const char* err, yyscan_t scanner)
{
	cerr << Aslan_get_lineno(scanner) << ": "
		<< "Error: " << err
		<< "(State: " << yy_top_state(scanner)
		<< ")\n";
	exit( YY_EXIT_FAILURE );
}
