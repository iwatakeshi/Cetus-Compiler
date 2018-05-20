%{

#include <cstdio>
#include <cstdlib>
#include "parser.tab.hpp"
%}

%%

"boolean"					{ return T_BOOL; }
"char"						{ return T_CHAR; }
"integer"					{ return T_INT; }
"string"					{ return T_STR; }
"intptr"					{ return T_INTP; }
"charptr"					{ return T_CHARP; }
"if" 						{ return K_IF; }
"else"						{ return K_ELSE; }
"while"						{ return K_WHILE; }
"var"						{ return K_VAR; }
"procedure"					{ return K_PROC; }
"return"					{ return K_RETURN; }
"null"						{ return K_NULL; }
"&&"						{ return O_AND; }
"/"							{ return O_DIVIDE; }
"="							{ return O_ASSIGN; }
"=="						{ return O_EQUAL; }
">"							{ return O_GT; }
">="						{ return O_GTE; }
"<"							{ return O_LT; }
"<="						{ return O_LTE; }
"-"							{ return O_SUBTRACT; }
"!"							{ return O_NOT; }
"!="						{ return O_NEQUAL; }
"||"						{ return O_OR; }
"+"							{ return O_ADD; }
"*"							{ return O_MULTIPLY; }
"&"							{ return O_ADDRESS; }
"^"							{ return O_DEREF; }
";"							{ return SEMICOLON; }
":"							{ return COLON; }
","							{ return COMMA; }
"|"							{ return PIPE; }
"{"							{ return CURLY_L; }
"}"							{ return CURLY_R; }
"("							{ return PAREN_L; }
")"							{ return PAREN_R; }
"["							{ return SQR_L; }
"]"							{ return SQR_R; }
[0-9]* |
0(x|X)[0-9ABCDEF]+ |
"0"[0-7]* |
(0|1)+b						{ return L_INT; }
(true|false)				{ return L_BOOL; }
'.'							{ return L_CHAR; }
\"(\\.|[^\\"])*\"			{ return L_STRING; }
_?[a-zA-Z0-9]+				{ return ID; }
\/%.*%\/						{ ;}
[ \t\n]						{ ;}
.							{ printf("Invalid token '%s'\n", yytext) ;}

%%


