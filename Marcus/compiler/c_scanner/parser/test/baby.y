%{
	#include <stdio.h>
	#include <stdlib.h>

	extern int yylex();


%}

%token INT CHAR ID ASSIGN VALUE SEMICOLON

%%
prog: block			{printf("parse complete!\n"); }
;

block: statement	{printf("block complete!\n"); }
| /*epsilon*/	{printf("block complete!\n"); }
;

statement: statement final	{printf("multiple statements!\n"); }
| final						{printf("statement complete!\n");}
;

final: decl					{printf("final found\n"); }
| assign
;

decl: type ID SEMICOLON		{printf("decl found\n"); }
;

assign: ID ASSIGN value SEMICOLON 	{printf("found assign\n"); }
| type ID ASSIGN value SEMICOLON	{printf("found assign\n"); }
;

value: VALUE				{printf("found value\n"); }
| ID
; 

type: INT					{printf("found type\n"); }
| CHAR						{printf("found type\n"); }
;

%%

int main()
{
	yyparse();
}

int yyerror() 
{
	fprintf(stderr, "there was an error I guess\n");
	return 1;
}
