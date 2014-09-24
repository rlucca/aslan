
/* Lexer options */
%option reentrant
%option prefix="Aslan_"
%option bison-bridge
%option bison-locations
%option noyywrap
%option yylineno

%{
#include "Aslan_Context.h"
#include "aslan.tab.h"

#define YY_EXTRA_TYPE Aslan_Context *
#define YY_USER_ACTION yylloc->first_line = yylineno;

#define YY_INPUT(buf, result, max_size)			\
{												\
	char c;										\
	(*yyextra->is) >> c;						\
	if(yyextra->is->eof())						\
		result = YY_NULL;						\
	else										\
	{											\
		buf[0] = c;								\
		result = 1;								\
	}											\
}
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
\'				BEGIN(CS);
.           	return ERR;
\n				{ }

<IGNORE>"*/"	BEGIN(INITIAL);
<IGNORE>.		{ }
<IGNORE>\n		{ }

<CS>\'			BEGIN(INITIAL);

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
