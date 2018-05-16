%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "Node.h"

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

Main: K_PROC "Main" PAREN_L paramlist PAREN_R K_RETURN type CURLY_L block CURLY_R

block: dblock sblock
| /* epsilon */
;

dblock: dblock fdecl
| /* epsilon */
;

sblock: sblock fstatement
| /* epsilon */
;

type: T_INT
| T_BOOL
| T_CHAR
| T_STR
| T_INTP
| T_CHARP
| T_BOOL SQR_L expr SQR_R
| T_CHAR SQR_L expr SQR_R
| T_INT SQR_L expr SQR_R
| T_STR SQR_L expr SQR_R
| T_INTP SQR_L expr SQR_R
| T_CHARP SQR_L expr SQR_R
;

fdecl: declproc
| declvar SEMICOLON

declproc: K_PROC ID PAREN_L paramlist PAREN_R K_RETURN type CURLY_L block K_RETURN expr CURLY_R
;

paramlist: paramlist fparamlist
| fparamlist
| /* epsilon */
;

fparamlist: param ID COLON type
;

param: param ID COMMA
| /* epsilon */
;

declvar: K_VAR addID ID COLON type
;

addID: addID ID COMMA
| /* epsilon */
;

fstatement: sif 
| swhile
| sassign SEMICOLON
| scall SEMICOLON
;

sif: K_IF PAREN_L expr PAREN_R CURLY_L block CURLY_R selse
;

selse: K_ELSE CURLY_L block CURLY_R
| /* epsilon */
;

swhile: K_WHILE PAREN_L expr PAREN_R CURLY_L block CURLY_R
;

sassign: lhs O_ASSIGN expr
;

scall: lhs O_ASSIGN ID PAREN_L arglist PAREN_R
;

arglist: arglist farg
| farg
| /* epsilon */
;

farg: ID
| farg COMMA
| /* epsilon */
;

lhs: ID
;

len: PIPE ID PIPE
;

expr: PAREN_L expr PAREN_R
| expr O_ADD factor
| expr O_SUBTRACT factor
| expr cmpr factor
| factor
| len
;

factor: PAREN_L factor PAREN_R
| factor O_MULTIPLY term
| factor O_DIVIDE term
| term
;

term: PAREN_L term PAREN_R
| unar term
| len
| L_BOOL
| L_INT
| L_STRING
| L_CHAR
| ID
;

unar: O_NOT
| O_ADDRESS
| O_DEREF

cmpr: O_NEQUAL
| O_LT
| O_LTE
| O_GT
| O_GTE
| O_EQUAL
;


%%



int main(int argc, char * argv[])
{

	yyparse();

}

