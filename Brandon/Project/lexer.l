%option yylineno
%pointer

%{
    #include <stdlib.h>
    #include <string.h>
    #include "parser.hpp"

    void yyerror(const char *);
%}
/** WRITE ME:
 *  Put any definitions you need here. Add your own regular expressions
 *  below for ALL tokens defined in the manual. You can choose not to use
 *  definitions here.
 */

/** The example below is very simple, but it shows almost everything you will
 *  need to do for this first part. The syntax is as follows:
 *
 *  regular_expression      {  c code  }
 *
 * The lexer will try to match each regular expression. When it does it will
 * execute the corresponding C code.
*/

/**
\"[ -~]*\"         {printf("T_Stringtype "); return T_Stringtype;}

\"[^\r\n]*\"      {printf("T_Stringtype "); return T_Stringtype;}

\/% {
int i;
while(true){
while((i = yyinput() != '%' && i != EOF));
if(i == '%'){
while((i = yyinput() == '%'));
if(i == '/'){
break;
}
}
if(i == EOF){
exit(1);
}
}
}

*/

%%

boolean     {printf("T_Bool "); return T_Bool;}
char        {printf("T_Char "); return T_Char;}
integer     {printf("T_Integer "); return T_Integer;}
string\[[1-9][0-9]*\] {printf("T_String "); return T_String;}
intptr      {printf("T_Intptr "); return T_Intptr;}
charptr     {printf("T_Charptr "); return T_Charptr;}
if          {printf("T_If "); return T_If;}
else        {printf("T_Else "); return T_Else;}
while       {printf("T_While "); return T_While;}
var         {printf("T_Var "); return T_Var;}
procedure   {printf("T_Proc "); return T_Proc;}
return      {printf("T_Return "); return T_Return;}
true        {printf("T_True "); return T_True;}
false       {printf("T_False "); return T_False;}
null        {printf("T_Null "); return T_Null;}

\&\&        {printf("T_And "); return T_And;}
\/          {printf("T_Divide "); return T_Divide;}
=           {printf("T_Assignment "); return T_Assignment;}
==          {printf("T_Equals "); return T_Equals;}
>           {printf("T_GT "); return T_GT;}
>=          {printf("T_GTE "); return T_GTE;}
\<          {printf("T_LT "); return T_LT;}
\<=         {printf("T_LTE "); return T_LTE;}
-           {printf("T_Minus "); return T_Minus;}
!           {printf("T_Not "); return T_Not;}
!=          {printf("T_NE "); return T_NE;}
\|\|        {printf("T_Or "); return T_Or;}
\+          {printf("T_Plus "); return T_Plus;}
\*          {printf("T_Times "); return T_Times;}
\&          {printf("T_Address "); return T_Address;}
\^          {printf("T_Dereference "); return T_Dereference;}

;           {prtinf("T_Semicolon "); return T_Semicolon;}
:           {printf("T_Colon "); return T_Colon;}
"{"         {printf("T_Lcurly "); return T_Lcurly;}
"}"         {printf("T_Rcurly "); return T_Rcurly;}
\(          {printf("T_Lparen "); return T_Lparen;}
\)          {printf("T_Rparen "); return T_Rparen;}
\[          {printf("T_Lbracket "); return T_Lbracket;}
]           {printf("T_Rbracket "); return T_Rbracket;}
,           {printf("T_Comma"); return T_Comma;}

0|[1-9][0-9]*      {printf("T_Num "); return T_Num;}
0[xX][0-9A-F]+     {printf("T_Num "); return T_Num;}
0[0-7][0-7]*       {printf("T_Num "); return T_Num;}
[01][01]*b         {printf("T_Num "); return T_Num;}

'[ -~]'            {printf("T_Chartype "); return T_Chartype;}
\"[^\"\r\n]*\"      {printf("T_Stringtype "); return T_Stringtype;}

[a-zA-Z][0-9_a-zA-Z]* {printf("T_Identifier "); return T_Identifier;}

[\*\(\)\.\+\-\%]  { return *yytext; }
[0-9][0-9]*         { return 'n'; }
[ \t\n]             ; /* skip whitespace */

.                   yyerror((char *) "invalid character");

%%

/** You shall not pass!
 *  You should not  have to do or edit anything past this.
 */

int yywrap(void) {
    return 1;
}
