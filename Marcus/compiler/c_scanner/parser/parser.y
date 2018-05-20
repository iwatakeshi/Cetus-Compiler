%{
	#include <cstdio.h>
	#include <cstdlib.h>
	#include "public/ast.hpp"
	extern int yylex();
%}

%token T_BOOL T_CHAR T_INT T_STR T_INTP T_CHARP
%token K_IF K_ELSE K_WHILE K_VAR K_PROC K_RETURN K_NULL
%token O_AND O_DIVIDE O_ASSIGN O_EQUAL O_GT O_GTE O_LT O_LTE O_SUBTRACT O_NOT O_NEQUAL O_OR O_ADD O_MULTIPLY O_ADDRESS O_DEREF

%token L_BOOL L_CHAR L_INT L_STRING
%token ID SEMICOLON COLON COMMA PIPE CURLY_L CURLY_R PAREN_L PAREN_R SQR_L SQR_R

// Operator Precedence

%right O_ASSIGN
%left O_OR
%left O_AND
%left O_EQUAL
%left O_NEQUAL
%left O_GT
%left O_GTE
%left O_LT
%left O_LTE
%left O_SUBTRACT O_ADD
%left O_MULTIPLY O_DIVIDE
%right O_NOT
%right O_ADDRESS
%right O_DEREF


%%

program: proc
;

proc: K_PROC ID PAREN_L params PAREN_R K_RETURN type proc_block proc
   	| /* E */
;

type: T_BOOL
	| T_INT
	| T_CHAR
	| T_STR
	| T_CHARP
	| T_INTP
;

params: ID more_params COLON type SEMICOLON params
	 | /* E */
;

more_params:  COMMA ID more_params
		   | /* E */
;

proc_block: CURLY_L proc decls stats return_stat CURLY_R
;

decls: decl SEMICOLON decls
	 | /* E */
;

stats: stat SEMICOLON stats
	 | /* E */
;

return_stat: K_RETURN expr SEMICOLON
;

decl: K_VAR vars ID COLON type
	| K_VAR vars ID COLON T_STR SQR_L expr SQR_R
;

vars: vars COMMA ID
	| /* E */
;

stat: lhs O_ASSIGN expr
	| lhs O_ASSIGN ID PAREN_L args PAREN_R
	| K_IF PAREN_L expr PAREN_R nest_block
	| K_IF PAREN_L expr PAREN_R nest_block K_ELSE nest_block
	| K_WHILE PAREN_L expr PAREN_R nest_block
	| nest_block
;
/*
assign: lhs O_ASSIGN expr
	  | lhs O_ASSIGN L_STRING
;
*/
lhs: ID
   | ID SQR_L expr SQR_R
   | O_DEREF ID
;
/*
call: lhs O_ASSIGN ID PAREN_L args PAREN_R
*/
args: expr more_args
	| /* E */
;

more_args: COMMA expr more_args
		 | /* E */
;
/*
if: K_IF PAREN_L expr PAREN_R nest_block
;

ifelse: K_IF PAREN_L expr PAREN_R nest_block K_ELSE nest_block
;

while: K_WHILE PAREN_L expr PAREN_R nest_block
;
*/
nest_block: CURLY_L decls stats CURLY_R
;

expr: PAREN_L expr PAREN_R
   	| expr O_OR expr
	| expr O_AND expr
	| expr O_EQUAL expr
	| expr O_NEQUAL expr
	| expr O_SUBTRACT expr
	| expr O_ADD expr
	| expr O_MULTIPLY expr
	| expr O_DIVIDE expr
	| expr O_GT expr
	| expr O_GTE expr
	| expr O_LT expr
	| expr O_LTE expr
	| O_NOT expr
	| O_ADDRESS lhs
	| O_DEREF PAREN_L expr PAREN_R
	| K_NULL
	| ID
	| abs
	| L_INT
	| L_CHAR
	| L_BOOL
	| L_STRING
;
/*
o_bin: O_OR
	 | O_AND
	 | O_EQUAL
	 | O_NEQUAL
	 | O_SUBTRACT
	 | O_ADD
	 | O_MULTIPLY
	 | O_DIVIDE
	 | O_GT
	 | O_GTE
	 | O_LT
	 | O_LTE
;

o_un: O_NOT
	| O_DEREF
	| O_ADDRESS
;
*/
abs: PIPE expr PIPE
;


%%


