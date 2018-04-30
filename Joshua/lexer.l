%option noyywrap yylineno
%x COMMENT
%x STRING

%{

#include <stdlib.h>
#include <errno.h>
#include <string.h>

#ifndef MAX_STRING
	#define MAX_STRING 512
#endif

void yyerror(const char *);

int makeInt(char *, int);

char buf[MAX_STRING];
char *charPtr;

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
"procedure"	{ return PROC; }
"return"    { return RETURN; }
"null"		{ return NIL; }

"="			{ return ASN; }
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

"&"			{ return ADR; }
"^"			{ return DER; }
";"			{ return SMC; }
","			{ return CMA; }
"|"			{ return BAR; } 

"{"			{ return BRC_O; }
"}"			{ return BRC_C; }
"("			{ return PRN_O; }
")"			{ return PRN_C; }
"["			{ return SQR_O; }
"]"			{ return SQR_C; }


"/%"					{ BEGIN(COMMENT); }

<COMMENT>{
		[^%\n]*			{ /* Remove anything != '%' */ }
		"%"+[^*/\n]*	{ /* Remove any '*' if not immediately followed by '/' */ }
		\n				{ }
		"%"+"/"			{ BEGIN(INITIAL); }
		<<EOF>>			{ yyerror("unexpected end of file") /* Detect unclosed comment block */  }
}

\"						{ charPtr = buf; BEGIN(STRING); }
	
<STRING>\"				{ BEGIN(INITIAL);
							*charPtr = '\0';
							strcpy(yylval.str_buf, buf); 
							return STR_LIT; }

<STRING>{
		<<EOF>>			{ yyerror("unterminated string") /* Detect unclosed string */ }
		\n				{ *charPtr++ = '\\'; *charPtr++ = 'n'; } 
		[[:print:]]		{ *charPtr++ = yytext[0]; }
		[^[:print:]]	{ yyerror("invalid character in string") }						
}			

"true"					{ yylval.int_val = 1; return BOOL_LIT; }
"false"					{ yylval.int_val = 0; return BOOL_LIT; }
\'[:print:]\'			{ yylval.char_val = yytext[1] ; return CHAR_LIT; }
[0-1]+b					{ yylval.int_val = makeInt(yytext, 2); return INT_LIT; }
0|[-+]?[1-9][0-9]*		{ yylval.int_val = makeInt(yytext, 10); return INT_LIT; }
0[1-7][0-7]*			{ yylval.int_val = makeInt(yytext, 8); return INT_LIT; }
0[x|X][0-9A-F]+			{ yylval.int_val = makeInt(yytext, 0); return INT_LIT; }

{ID}					{ strcpy(yylval.str_buf, yytext); return ID; }

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
