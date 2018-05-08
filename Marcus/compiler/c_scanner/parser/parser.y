%{
	#include <stdio.h>
	#include <stdlib.h>

	extern int yylex();
%}

%token T_BOOL T_CHAR T_INT T_STR T_INTP T_CHARP
%token K_IF K_ELSE K_WHILE K_VAR K_PROC K_RETURN K_NULL
%token O_AND O_DIVIDE O_ASSIGN O_EQUALS O_GT O_GTE O_LT O_LTE O_SUBTRACT O_NOT O_NEQUAL O_OR O_ADD O_MULTIPLY O_ADDRESS O_DEREF

%token L_BOOL L_CHAR L_INT L_STRING
%token ID SEMICOLON COLON COMMA PIPE CURLY_L CURLY_R PAREN_L PAREN_R SQR_L SQR_R


%%
program: block Main	block	{printf("PARSE SUCCESSFUL\n");}
;

Main: K_PROC "Main" PAREN_L arglist PAREN_R K_RETURN type CURLY_L block CURLY_R

block: statement fstatement
| fstatement
| /*epsilon*/
;

type: T_INT
|T_BOOL
|T_CHAR
|T_STR
|T_INTP
|T_CHARP
;

statement: statement fstatement
| fstatement
| /*epsilon*/
;

fstatement: declproc 
| declvar SEMICOLON
| declif 
| declwhile
;

declproc: K_PROC ID PAREN_L arglist PAREN_R CURLY_L block CURLY_R
;

arglist: arglist farglist
| farglist
| /*epsilon*/
;

farglist:  arg ID COLON type
;

arg: arg ID COMMA
| /*epsilon*/
;




%%

