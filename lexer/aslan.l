 /*
	vim:noexpandtab:ts=8 sw=8
 */
%top {
 /* To remove a warning of a comparison between
   signed and unsigned data */
 typedef int yy_size_t;
 #define YY_TYPEDEF_YY_SIZE_T
}

 /* Lexer options */
%option reentrant
%option extra-type="Aslan_Context *"
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
HEXES				[a-fA-F0-9]
ALNUM				[[:alnum:]_]
DIGIT				[[:digit:]]
INFIX_FLOAT			[eE][+-]?{DIGIT}+
SUFFIX_FLOAT			\.{DIGIT}+{INFIX_FLOAT}?
HEX_NUMBER			0[xX]{HEXES}+
OCT_NUMBER			0{OCTALS}+
NOT				[nN][oO][tT]
NO_NAMED_VARIABLE		_{ALNUM}*
VARIABLE			[A-Z]{ALNUM}*
IDENTIFIER			[a-z]{ALNUM}*
EXTERNAL_ACTION			{IDENTIFIER}(\.{IDENTIFIER}){1,}
FLOAT_NUMBER			{DIGIT}*{SUFFIX_FLOAT}
NUMBER				{DIGIT}+

%{
#include "Aslan_Context.hpp"
#include "aslan_parser.hpp"
#include <cstring>

void Aslan_lexerror(const char* err, yyscan_t scanner);

/* To update the line number */
#define YY_USER_ACTION yylloc->first_line = yylineno;

/* To use the input inside of extra data was
   necessary override the YY_INPUT */
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

/* To do a better error explanation.
   Well, maybe not so... */
#define YY_FATAL_ERROR(msg) Aslan_lexerror( msg , yyscanner)
/* Shortcuts */
#define PUSH_STATE(state) yy_push_state(state, yyscanner)
#define POP_STATE() yy_pop_state(yyscanner)
#define RETURN_COPYING_LEXEMA(TOKEN)		\
	yylval->lexema = strdup(yytext);	\
	return TOKEN

%}


 /* When I use %x and %s ?
      %x is used when the state not share rules with INITIAL state.
         (other way, this state is eXclusive)
      %s is used when the state share rules with INITIAL state.
         (other way, this state is incluSive)
    It is vague? See the example in the manual! */
 /* comment state */
%x IGNORE
 /* char string state */
%x CS
 /* multichar string state */
%x SS
 /* understanding and transform a escaped char */
%x ESCAPE_CHAR
 /* brackets, parentheses and keys */
%s PAIRB PAIRP PAIRK

%%

"//".*			/* IGNORE */
"/*"			PUSH_STATE(IGNORE);
"("			{
			PUSH_STATE(PAIRP);
			RETURN_COPYING_LEXEMA(LEFTP);
			}
<PAIRP>")"		{
			POP_STATE();
			RETURN_COPYING_LEXEMA(RIGHTP);
			}
")"			YY_FATAL_ERROR("Did you forget to open '('?");
"["			{
			PUSH_STATE(PAIRB);
			RETURN_COPYING_LEXEMA(LEFTB);
			}
<PAIRB>"]"		{
			POP_STATE();
			RETURN_COPYING_LEXEMA(RIGHTB);
			}
"]"			YY_FATAL_ERROR("Did you forget to open '['?");
"{"			{
			PUSH_STATE(PAIRK);
			RETURN_COPYING_LEXEMA(LEFTK);
			}
<PAIRK>"}"		{
			POP_STATE();
			RETURN_COPYING_LEXEMA(RIGHTK);
			}
"}"			YY_FATAL_ERROR("Did you forget to open '{'?");
"/"			{ RETURN_COPYING_LEXEMA(DIV); }
"%"			{ RETURN_COPYING_LEXEMA(MOD); }
"*"			{ RETURN_COPYING_LEXEMA(MUL); }
"+"			{ RETURN_COPYING_LEXEMA(PLUS); }
"-"			{ RETURN_COPYING_LEXEMA(MINUS); }
"?"			{ RETURN_COPYING_LEXEMA(TEST); }
","			{ RETURN_COPYING_LEXEMA(COMMA); }
":"			{ RETURN_COPYING_LEXEMA(CONTEXT); }
";"			{ RETURN_COPYING_LEXEMA(SEQUENCE); }
"~"			{ RETURN_COPYING_LEXEMA(STRONG_NEGATION); }
"^"			{ RETURN_COPYING_LEXEMA(XOR_BIT); }
"!="			{ RETURN_COPYING_LEXEMA(DIFFERENT_CMP); }
"!"			{ RETURN_COPYING_LEXEMA(ACHIEVE); }
"=="			{ RETURN_COPYING_LEXEMA(EQUAL_CMP); }
"="			{ RETURN_COPYING_LEXEMA(ASSIGNMENT); }
"&&"			{ RETURN_COPYING_LEXEMA(AND_LOGIC); }
"&"			{ RETURN_COPYING_LEXEMA(AND_BIT); }
"||"			{ RETURN_COPYING_LEXEMA(OR_LOGIC); }
<PAIRB>"|"		{ RETURN_COPYING_LEXEMA(SEP); }
"|"			{ RETURN_COPYING_LEXEMA(OR_BIT); }
"<<"			{ RETURN_COPYING_LEXEMA(SHIFTLEFT); }
"<="			{ RETURN_COPYING_LEXEMA(LESSEQUAL); }
"<-"			{ RETURN_COPYING_LEXEMA(POINTER); }
"<"			{ RETURN_COPYING_LEXEMA(LESS); }
">>"			{ RETURN_COPYING_LEXEMA(SHIFTRIGHT); }
">="			{ RETURN_COPYING_LEXEMA(GREATEQUAL); }
">"			{ RETURN_COPYING_LEXEMA(GREAT); }
{NOT}			{ RETURN_COPYING_LEXEMA(NOT); }
{NO_NAMED_VARIABLE}	{
			yylval->lexema = strdup("_");
			return NO_NAMED_VARIABLE;
			}
{VARIABLE}		{ RETURN_COPYING_LEXEMA(VARIABLE); }
{IDENTIFIER}		{ RETURN_COPYING_LEXEMA(IDENTIFIER); }
{EXTERNAL_ACTION}	{ RETURN_COPYING_LEXEMA(EXTERNAL_ACTION); }
{HEX_NUMBER}		{ RETURN_COPYING_LEXEMA(NUMBER_LITERAL); }
{OCT_NUMBER}		{ RETURN_COPYING_LEXEMA(NUMBER_LITERAL); }
{FLOAT_NUMBER}		{ RETURN_COPYING_LEXEMA(FLOAT_LITERAL); }
{NUMBER}		{ RETURN_COPYING_LEXEMA(NUMBER_LITERAL); }
\'			{
			yymore();
			PUSH_STATE(CS);
			}
\"			{
			yymore();
			PUSH_STATE(SS);
			}
\.			{ RETURN_COPYING_LEXEMA(DOT_LITERAL); }
[[:blank:]]		/* IGNORE */
.           		YY_FATAL_ERROR("Invalid Char");
\n			/* IGNORE */
<INITIAL><<EOF>>	{ RETURN_COPYING_LEXEMA(0); }
<<EOF>>			YY_FATAL_ERROR("Unexpected end of file");
<IGNORE>"*/"		POP_STATE();
<IGNORE>.		/* IGNORE */
<IGNORE>\n		/* IGNORE */

<CS>\'			{
			POP_STATE();
			RETURN_COPYING_LEXEMA(CHAR_STRING_LITERAL);
			}
<SS>\"			{
			POP_STATE();
			RETURN_COPYING_LEXEMA(STRING_LITERAL);
			}
<CS,SS>\\		{
			yymore();
			PUSH_STATE(ESCAPE_CHAR);
			}
<CS,SS>.		yymore();
<CS,SS>\n		YY_FATAL_ERROR("Unexpected end of line");

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
	// It will destroy the states too
	yylex_destroy(scanner);
}

void Aslan_lexerror(const char* err, yyscan_t scanner)
{
	cerr << Aslan_get_lineno(scanner) << ": "
		<< "Error: " << err
		<< " (State: " << yy_top_state(scanner)
		<< ")\n";

	// Destroy everything
	Aslan_get_extra(scanner)->is->~istream();
	Aslan_get_extra(scanner)->~Aslan_Context();

	exit( YY_EXIT_FAILURE );
}
