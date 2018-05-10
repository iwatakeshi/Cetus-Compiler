%option yylineno
%pointer
%x COMMENT

%{
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "y.tab.h"

//extern int yylval;
//extern void yyerror(const char *);

int makeInt(char *, int);
%}

ID        [a-zA-Z][a-zA-Z0-9]*

%%

"boolean"	{ return BOOLEAN; }
"char"		{ return CHAR; }
"integer"	{ return INTEGER; }
"string"	{ return STRING; }
"intptr"	{ return INTPTR; }
"charptr"	{ return CHARPTR; }

"if"		{ return IF; }
"else"		{ return ELSE; }
"while"		{ return WHILE; }
"var"		{ return VAR; }
"procedure"	{ return PROCEDURE; }
"return"    { return RETURN; }
"null"		{ return NIL; }

"="			{ return ASSIGN; }
"+"			{ return ADD; }
"-"			{ return SUB; }
"*"			{ return MUL; }
"/"			{ return DIV; }

">"			{ return GT; }
">="		{ return GE; }
"<"			{ return LT; }
"<="		{ return LE; }
"=="		{ return EQ; }
"!="		{ return NE; }

"!"			{ return NOT; }
"&&"		{ return AND; }
"||"		{ return OR; }

"&"			{ return ADDRESS; }
"^"			{ return DEREF; }
":"			{ return COLON; }
";"			{ return SEMICOLON; }
","			{ return COMMA; }
"|"			{ return BAR; } 

"{"			{ return BRACE_O; }
"}"			{ return BRACE_C; }
"("			{ return PAREN_O; }
")"			{ return PAREN_C; }
"["			{ return SQUARE_O; }
"]"			{ return SQUARE_C; }


"/%"					{ BEGIN(COMMENT); }

<COMMENT>{
		[^%\n]*			{ /* Remove anything != '%' */ }
		"%"+[^*/\n]*	{ /* Remove any '*' if not immediately followed by '/' */ }
		\n				{ }
		"%"+"/"			{ BEGIN(INITIAL); }
		<<EOF>>			{ yyerror("unexpected end of file"); /* Detect unclosed comment block */  }
}

"true"					{ yylval.int_val = 1; return BOOL_LIT; }
"false"					{ yylval.int_val = 0; return BOOL_LIT; }

[0-1]+b					{ yylval.int_val = makeInt(yytext, 2); return INT_LIT; }
0|[-+]?[1-9][0-9]*		{ yylval.int_val = makeInt(yytext, 10); return INT_LIT; }
0[1-7][0-7]*			{ yylval.int_val = makeInt(yytext, 8); return INT_LIT; }
0[x|X][0-9A-F]+			{ yylval.int_val = makeInt(yytext, 0); return INT_LIT; }

\'[:print:]\'			{ yylval.int_val = (int)(*(yytext+1)); return CHAR_LIT; }

\"[^\"]*\"				{	yylval.char_ptr = strdup(yytext + 1); // Remove leading "
							yylval.char_ptr[strlen(yylval.char_ptr) - 1] = '\0'; // Remove trailing " 
							return STR_LIT; }

{ID}					{ yylval.char_ptr = strdup(yytext); return ID; }

[ \n\t]					{ /* Whitespace Be Gone! */ }

.						{ return UNKNOWN; }

%%

int makeInt(char* text, int base) {

	char *p = NULL;

	errno = 0;

	int value = (int) strtol(text, &p, base);

	if (errno != 0){
		yyerror("conversion to integer failed");
	}

	return value;
}

int yywrap(void) { return 1; }
