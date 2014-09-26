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
%option stack

 /* caution */
%option nounput

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

<CS>\'			POP_STATE();
<CS><<EOF>>		{
			YY_FATAL_ERROR("Unexpected end of file");
			return ERR;
			}

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
