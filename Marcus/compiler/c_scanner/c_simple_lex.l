%{
#include "scanner.h"

%}

%%
","						return COMMA;
"("						return PAREN_L;
")"						return PAREN_R;
"{"						return BRAC_L;
"}"						return BRAC_R;
"["						return SBRAC_L;
"]"						return SBRAC_R;
";"						return SEMICOLON;
"+" 					return O_ADD;
"-" 					return O_SUBTRACT;
"/" 					return O_DIVIDE;
"%" 					return O_REMAIN;
"*" 					return O_MULT;
"==" 					return O_EQUAL;
">" 					return O_GT;
"<" 					return O_LT;
">=" 					return O_GTE;
"<=" 					return O_LTE;
"="						return O_ASSIGN;
"int"					return K_INT;
"float"					return K_FLOAT;
"char"					return K_CHAR;
"if"					return K_IF;
"else"					return K_ELSE;
"for"					return K_WHILE;
"return"				return K_RETURN;
"break"					return K_BREAK;
"struct"				return K_STRUCT;
"class"					return K_CLASS;
[0-9]*\.?[0-9]*			return NUMBER;
[_a-zA-Z][_a-zA-Z0-9]* 	return IDEN;
\"[a-zA-Z0-9 ]*\"		return STRING_LIT;
'[a-zA-Z0-9 ]'			return CHAR_LIT;
[ \t\n]					;
.						return NONE;

%%



