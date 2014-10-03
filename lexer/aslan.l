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
VARIABLE			[_A-Z]{ALNUM}*
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
			return LEFTP;
			}
<PAIRP>")"		{
			POP_STATE();
			return RIGHTP;
			}
")"			{
			YY_FATAL_ERROR("Did you forget to open '('?");
			POP_STATE();
			}
"["			{
			PUSH_STATE(PAIRB);
			return LEFTB;
			}
<PAIRB>"]"		{
			POP_STATE();
			return RIGHTB;
			}
"]"			{
			YY_FATAL_ERROR("Did you forget to open '['?");
			POP_STATE();
			}
"{"			{
			PUSH_STATE(PAIRK);
			return LEFTK;
			}
<PAIRK>"}"		{
			POP_STATE();
			return RIGHTK;
			}
"}"			{
			YY_FATAL_ERROR("Did you forget to open '{'?");
			POP_STATE();
			}
"/"			return DIV;
"%"			return MOD;
"*"			return MUL;
"+"			return PLUS;
"-"			return MINUS;
"?"			return TEST;
","			return COMMA;
":"			return CONTEXT;
";"			return SEQUENCE;
"~"			return STRONG_NEGATION;
"^"			return XOR_BIT;
"!="			return DIFFERENT_CMP;
"!"			return ACHIEVE;
"=="			return EQUAL_CMP;
"="			return ASSIGNMENT;
"&&"			return AND_LOGIC;
"&"			return AND_BIT;
"||"			return OR_LOGIC;
<PAIRB>"|"		return SEP;
"|"			return OR_BIT;
"<<"			return SHIFTLEFT;
"<="			return LESSEQUAL;
"<-"			return POINTER;
"<"			return LESS;
">>"			return SHIFTRIGHT;
">="			return GREATEQUAL;
">"			return GREAT;
{NOT}			return NOT;
{VARIABLE}		return VARIABLE;
{IDENTIFIER}		{
			yylval->lexema = strdup(yytext);
			return IDENTIFIER;
			}
{EXTERNAL_ACTION}	return EXTERNAL_ACTION;
{HEX_NUMBER}		return NUMBER_LITERAL;
{OCT_NUMBER}		return NUMBER_LITERAL;
{FLOAT_NUMBER}		return FLOAT_LITERAL;
{NUMBER}		return NUMBER_LITERAL;
\'			{
			yymore();
			PUSH_STATE(CS);
			}
\"			{
			yymore();
			PUSH_STATE(SS);
			}
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
