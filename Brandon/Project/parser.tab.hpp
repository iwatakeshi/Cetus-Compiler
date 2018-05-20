/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_Bool = 258,
     T_Char = 259,
     T_Integer = 260,
     T_String = 261,
     T_Intptr = 262,
     T_Charptr = 263,
     T_If = 264,
     T_Else = 265,
     T_While = 266,
     T_Var = 267,
     T_Proc = 268,
     T_Return = 269,
     T_True = 270,
     T_False = 271,
     T_Null = 272,
     T_Semicolon = 273,
     T_Colon = 274,
     T_Lcurly = 275,
     T_Rcurly = 276,
     T_Lparen = 277,
     T_Rparen = 278,
     T_Lbracket = 279,
     T_Rbracket = 280,
     T_Num = 281,
     T_Stringtype = 282,
     T_Chartype = 283,
     T_Identifier = 284,
     T_Comma = 285,
     T_Assignment = 286,
     T_Or = 287,
     T_And = 288,
     T_Equals = 289,
     T_NE = 290,
     T_GT = 291,
     T_GTE = 292,
     T_LT = 293,
     T_LTE = 294,
     T_Minus = 295,
     T_Plus = 296,
     T_Divide = 297,
     T_Times = 298,
     T_Not = 299,
     T_Address = 300,
     T_Dereference = 301
   };
#endif
/* Tokens.  */
#define T_Bool 258
#define T_Char 259
#define T_Integer 260
#define T_String 261
#define T_Intptr 262
#define T_Charptr 263
#define T_If 264
#define T_Else 265
#define T_While 266
#define T_Var 267
#define T_Proc 268
#define T_Return 269
#define T_True 270
#define T_False 271
#define T_Null 272
#define T_Semicolon 273
#define T_Colon 274
#define T_Lcurly 275
#define T_Rcurly 276
#define T_Lparen 277
#define T_Rparen 278
#define T_Lbracket 279
#define T_Rbracket 280
#define T_Num 281
#define T_Stringtype 282
#define T_Chartype 283
#define T_Identifier 284
#define T_Comma 285
#define T_Assignment 286
#define T_Or 287
#define T_And 288
#define T_Equals 289
#define T_NE 290
#define T_GT 291
#define T_GTE 292
#define T_LT 293
#define T_LTE 294
#define T_Minus 295
#define T_Plus 296
#define T_Divide 297
#define T_Times 298
#define T_Not 299
#define T_Address 300
#define T_Dereference 301




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 13 "parser.ypp"
{ int int_val; char *char_ptr; }
/* Line 1529 of yacc.c.  */
#line 143 "parser.tab.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

