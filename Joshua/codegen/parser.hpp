/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_Bool = 258,
    T_Char = 259,
    T_Integer = 260,
    T_Str = 261,
    T_String = 262,
    T_Intptr = 263,
    T_Charptr = 264,
    T_If = 265,
    T_Else = 266,
    T_While = 267,
    T_Var = 268,
    T_Proc = 269,
    T_Return = 270,
    T_True = 271,
    T_False = 272,
    T_Null = 273,
    T_Semicolon = 274,
    T_Colon = 275,
    T_Lcurly = 276,
    T_Rcurly = 277,
    T_Lparen = 278,
    T_Rparen = 279,
    T_Lbracket = 280,
    T_Rbracket = 281,
    T_Num = 282,
    T_Stringtype = 283,
    T_Chartype = 284,
    T_Identifier = 285,
    T_Comma = 286,
    T_Assignment = 287,
    T_Or = 288,
    T_And = 289,
    T_Equals = 290,
    T_NE = 291,
    T_GT = 292,
    T_GTE = 293,
    T_LT = 294,
    T_LTE = 295,
    T_Plus = 296,
    T_Minus = 297,
    T_Times = 298,
    T_Divide = 299,
    T_Not = 300,
    T_Address = 301,
    T_Dereference = 302
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
