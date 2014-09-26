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
%}

 /* comment state */
%x IGNORE
 /* char string state */
%x CS
 /* multichar string state */
%x SS

%%

"//".*			/* IGNORE */
"/*"			BEGIN(IGNORE);
\'			BEGIN(CS);
[[:blank:]]		/* IGNORE */
.           		{
			YY_FATAL_ERROR("Invalid Char");
			return ERR;
			}
\n			/* IGNORE */

<IGNORE>"*/"		BEGIN(INITIAL);
<IGNORE>.		/* IGNORE */
<IGNORE>\n		/* IGNORE */
<IGNORE><<EOF>>		{
			YY_FATAL_ERROR("Unexpected end of file");
			return ERR;
			}

<CS>\'			BEGIN(INITIAL);
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
		<< "Error: " << err << "\n";
	exit( YY_EXIT_FAILURE );
}
