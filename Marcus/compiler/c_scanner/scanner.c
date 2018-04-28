#include "scanner.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR 255

//Imported from lex.yy.c
extern int yylex();
extern char* yytext;
extern int yylineno;
extern FILE* yyin;

int main(int argc, char* argv[])
{
	int tok;
	FILE* src;
	FILE* dest;
	char destPath[MAX_STR];	
	
	if(argc == 1)
	{
		fprintf(stderr, "Error: %s\n", "No input files found");
	}
	// Write lexed output to output files
	for(int i = 1; i < argc; i++)
	{
		//Set output file path
		memset(destPath, '\0', MAX_STR);
		strcpy(destPath, argv[i]);
		strcat(destPath, ".lxd");

		//Redirect input/output
		src = fopen(argv[i], "r");
		yyin = src;
		dest = fopen(destPath, "w");
		
		//Lex input and write tokens to output
		while((tok = yylex()))
		{
			fprintf(dest, "%d %s\n", tok, yytext);
		}
		
		//Reset standard i/o
		fclose(src);
		fclose(dest);
		yyin = stdin;
		
	}		
	return 0;
}
