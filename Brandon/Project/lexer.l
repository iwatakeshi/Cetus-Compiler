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

boolean                 {return T_Bool;}
char                    {return T_Char;}
integer                 {return T_Integer;}
string\[[1-9][0-9]*\]   {return T_String;}
intptr                  {return T_Intptr;}
charptr                 {return T_Charptr;}
if                      {return T_If;}
else                    {return T_Else;}
while                   {return T_While;}
var                     {return T_Var;}
procedure               {return T_Proc;}
return                  {return T_Return;}
true                    {return T_True;}
false                   {return T_False;}
null                    {return T_Null;}

\&\&                    {return T_And;}
\/                      {return T_Divide;}
=                       {return T_Assignment;}
==                      {return T_Equals;}
>                       {return T_GT;}
>=                      {return T_GTE;}
\<                      {return T_LT;}
\<=                     {return T_LTE;}
-                       {return T_Minus;}
!                       {return T_Not;}
!=                      {return T_NE;}
\|\|                    {return T_Or;}
\+                      {return T_Plus;}
\*                      {return T_Times;}
\&                      {return T_Address;}
\^                      {return T_Dereference;}

;                       {return T_Semicolon;}
:                       {return T_Colon;}
"{"                     {return T_Lcurly;}
"}"                     {return T_Rcurly;}
\(                      {return T_Lparen;}
\)                      {return T_Rparen;}
\[                      {return T_Lbracket;}
]                       {return T_Rbracket;}
,                       {return T_Comma;}

0|[1-9][0-9]*           {return T_Num;}
0[xX][0-9A-F]+          {return T_Num;}
0[0-7][0-7]*            {return T_Num;}
[01][01]*b              {return T_Num;}

'[ -~]'                 {return T_Chartype;}
\"[^\"\r\n]*\"          {return T_Stringtype;}

[a-zA-Z][0-9_a-zA-Z]*   {return T_Identifier;}

[\*\(\)\.\+\-\%]        {return *yytext;}
[0-9][0-9]*             {return 'n'; }
[ \t\n]             ; /* skip whitespace */

.                   yyerror((char *) "invalid character");

%%

/** You shall not pass!
 *  You should not  have to do or edit anything past this.
 */

int yywrap(void) {
    return 1;
}
