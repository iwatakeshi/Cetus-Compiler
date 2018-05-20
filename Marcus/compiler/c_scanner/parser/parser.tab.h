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
     T_BOOL = 258,
     T_CHAR = 259,
     T_INT = 260,
     T_STR = 261,
     T_INTP = 262,
     T_CHARP = 263,
     K_IF = 264,
     K_ELSE = 265,
     K_WHILE = 266,
     K_VAR = 267,
     K_PROC = 268,
     K_RETURN = 269,
     K_NULL = 270,
     O_AND = 271,
     O_DIVIDE = 272,
     O_ASSIGN = 273,
     O_EQUAL = 274,
     O_GT = 275,
     O_GTE = 276,
     O_LT = 277,
     O_LTE = 278,
     O_SUBTRACT = 279,
     O_NOT = 280,
     O_NEQUAL = 281,
     O_OR = 282,
     O_ADD = 283,
     O_MULTIPLY = 284,
     O_ADDRESS = 285,
     O_DEREF = 286,
     L_BOOL = 287,
     L_CHAR = 288,
     L_INT = 289,
     L_STRING = 290,
     ID = 291,
     SEMICOLON = 292,
     COLON = 293,
     COMMA = 294,
     PIPE = 295,
     CURLY_L = 296,
     CURLY_R = 297,
     PAREN_L = 298,
     PAREN_R = 299,
     SQR_L = 300,
     SQR_R = 301
   };
#endif
/* Tokens.  */
#define T_BOOL 258
#define T_CHAR 259
#define T_INT 260
#define T_STR 261
#define T_INTP 262
#define T_CHARP 263
#define K_IF 264
#define K_ELSE 265
#define K_WHILE 266
#define K_VAR 267
#define K_PROC 268
#define K_RETURN 269
#define K_NULL 270
#define O_AND 271
#define O_DIVIDE 272
#define O_ASSIGN 273
#define O_EQUAL 274
#define O_GT 275
#define O_GTE 276
#define O_LT 277
#define O_LTE 278
#define O_SUBTRACT 279
#define O_NOT 280
#define O_NEQUAL 281
#define O_OR 282
#define O_ADD 283
#define O_MULTIPLY 284
#define O_ADDRESS 285
#define O_DEREF 286
#define L_BOOL 287
#define L_CHAR 288
#define L_INT 289
#define L_STRING 290
#define ID 291
#define SEMICOLON 292
#define COLON 293
#define COMMA 294
#define PIPE 295
#define CURLY_L 296
#define CURLY_R 297
#define PAREN_L 298
#define PAREN_R 299
#define SQR_L 300
#define SQR_R 301




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

