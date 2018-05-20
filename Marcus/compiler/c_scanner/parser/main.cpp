#include <iostream>
#include <string>

extern int yylex();
extern char *yytext;
extern FILE *yyin;
extern void yyparse();

int main(int argc, char *argv[])
{

	yyparse();
	return 0;
}
