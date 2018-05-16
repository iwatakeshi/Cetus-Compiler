%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "baby.tab.hpp"

	int yylval;
%}

%%

[ \t\n]							;
"char"							return CHAR;
"int"							return INT;
"="								return ASSIGN;
";"								return SEMICOLON;
[_a-zA-Z][_a-zA-Z0-9]*			return ID;
[0-9]+							return VALUE;
.								printf("token not found\n");

%%
