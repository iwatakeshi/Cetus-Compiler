/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
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
     T_Minus = 296,
     T_Plus = 297,
     T_Divide = 298,
     T_Times = 299,
     T_Not = 300,
     T_Address = 301,
     T_Dereference = 302
   };
#endif
/* Tokens.  */
#define T_Bool 258
#define T_Char 259
#define T_Integer 260
#define T_Str 261
#define T_String 262
#define T_Intptr 263
#define T_Charptr 264
#define T_If 265
#define T_Else 266
#define T_While 267
#define T_Var 268
#define T_Proc 269
#define T_Return 270
#define T_True 271
#define T_False 272
#define T_Null 273
#define T_Semicolon 274
#define T_Colon 275
#define T_Lcurly 276
#define T_Rcurly 277
#define T_Lparen 278
#define T_Rparen 279
#define T_Lbracket 280
#define T_Rbracket 281
#define T_Num 282
#define T_Stringtype 283
#define T_Chartype 284
#define T_Identifier 285
#define T_Comma 286
#define T_Assignment 287
#define T_Or 288
#define T_And 289
#define T_Equals 290
#define T_NE 291
#define T_GT 292
#define T_GTE 293
#define T_LT 294
#define T_LTE 295
#define T_Minus 296
#define T_Plus 297
#define T_Divide 298
#define T_Times 299
#define T_Not 300
#define T_Address 301
#define T_Dereference 302




/* Copy the first part of user declarations.  */
#line 1 "parser.ypp"

    #include <cstdio>
    #include <cstdlib>

    #include "ast.hpp"
    #include "primitive.hpp"
    #include "symtab.hpp"

    #define YYDEBUG 1

    extern Program_ptr ast;
    int yylex(void);
    void yyerror(const char *);


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 215 "parser.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   349

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  71
/* YYNRULES -- Number of states.  */
#define YYNSTATES  151

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   302

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    48,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,    17,    18,    24,    25,    29,    30,
      33,    35,    37,    39,    41,    43,    45,    50,    55,    59,
      67,    68,    72,    73,    75,    77,    79,    81,    83,    86,
      87,    92,    97,   105,   108,   109,   113,   114,   116,   121,
     124,   127,   130,   132,   134,   136,   138,   140,   145,   148,
     151,   154,   156,   160,   164,   168,   172,   176,   180,   184,
     188,   192,   196,   200,   204,   208,   213,   217,   219,   225,
     233,   239
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      50,     0,    -1,    51,    -1,    14,    30,    23,    52,    24,
      15,    55,    21,    56,    22,    51,    -1,    -1,    30,    53,
      20,    55,    54,    -1,    -1,    31,    30,    53,    -1,    -1,
      19,    52,    -1,    52,    -1,     5,    -1,     4,    -1,     9,
      -1,     8,    -1,     3,    -1,     6,    25,    27,    26,    -1,
      51,    58,    61,    57,    -1,    15,    68,    19,    -1,    13,
      30,    59,    20,    55,    19,    58,    -1,    -1,    31,    30,
      59,    -1,    -1,    62,    -1,    63,    -1,    70,    -1,    71,
      -1,    69,    -1,    60,    61,    -1,    -1,    66,    32,    68,
      19,    -1,    66,    32,    28,    19,    -1,    66,    32,    30,
      23,    64,    24,    19,    -1,    68,    65,    -1,    -1,    31,
      68,    65,    -1,    -1,    30,    -1,    30,    25,    68,    26,
      -1,    47,    30,    -1,    41,    68,    -1,    42,    68,    -1,
      27,    -1,    16,    -1,    17,    -1,    29,    -1,    30,    -1,
      30,    25,    68,    26,    -1,    45,    67,    -1,    47,    68,
      -1,    46,    66,    -1,    18,    -1,    68,    42,    68,    -1,
      68,    41,    68,    -1,    68,    44,    68,    -1,    68,    43,
      68,    -1,    68,    35,    68,    -1,    68,    39,    68,    -1,
      68,    40,    68,    -1,    68,    37,    68,    -1,    68,    38,
      68,    -1,    68,    36,    68,    -1,    68,    33,    68,    -1,
      68,    34,    68,    -1,    23,    68,    24,    -1,    45,    23,
      68,    24,    -1,    48,    68,    48,    -1,    67,    -1,    10,
      23,    68,    24,    71,    -1,    10,    23,    68,    24,    71,
      11,    71,    -1,    12,    23,    68,    24,    71,    -1,    21,
      58,    61,    22,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   102,   102,   107,   110,   114,   118,   121,   123,   126,
     128,   132,   134,   136,   138,   140,   142,   147,   152,   158,
     162,   166,   169,   173,   175,   177,   179,   181,   185,   188,
     191,   193,   197,   201,   204,   207,   210,   214,   215,   217,
     222,   224,   226,   228,   230,   232,   234,   236,   238,   240,
     242,   243,   248,   250,   252,   254,   256,   258,   260,   262,
     264,   266,   268,   270,   272,   274,   276,   278,   284,   286,
     291,   296
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_Bool", "T_Char", "T_Integer", "T_Str",
  "T_String", "T_Intptr", "T_Charptr", "T_If", "T_Else", "T_While",
  "T_Var", "T_Proc", "T_Return", "T_True", "T_False", "T_Null",
  "T_Semicolon", "T_Colon", "T_Lcurly", "T_Rcurly", "T_Lparen", "T_Rparen",
  "T_Lbracket", "T_Rbracket", "T_Num", "T_Stringtype", "T_Chartype",
  "T_Identifier", "T_Comma", "T_Assignment", "T_Or", "T_And", "T_Equals",
  "T_NE", "T_GT", "T_GTE", "T_LT", "T_LTE", "T_Minus", "T_Plus",
  "T_Divide", "T_Times", "T_Not", "T_Address", "T_Dereference", "'|'",
  "$accept", "Start", "Method", "ParamList", "MoreParams", "ParamsAddl",
  "Type", "BodyReturn", "Return", "Vars", "MoreVars", "StatementP",
  "Statement", "Assignment", "MethodCall", "FuncExpr", "MoreExpr", "LHS",
  "UnaryExpr", "Expr", "IfWithElse", "While", "CodeBlock", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   124
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    51,    51,    52,    52,    53,    53,    54,
      54,    55,    55,    55,    55,    55,    55,    56,    57,    58,
      58,    59,    59,    60,    60,    60,    60,    60,    61,    61,
      62,    62,    63,    64,    64,    65,    65,    66,    66,    66,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    69,    69,
      70,    71
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,    11,     0,     5,     0,     3,     0,     2,
       1,     1,     1,     1,     1,     1,     4,     4,     3,     7,
       0,     3,     0,     1,     1,     1,     1,     1,     2,     0,
       4,     4,     7,     2,     0,     3,     0,     1,     4,     2,
       2,     2,     1,     1,     1,     1,     1,     4,     2,     2,
       2,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     4,     3,     1,     5,     7,
       5,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     0,     2,     0,     1,     6,     8,     0,     0,
       0,     0,     8,     0,     0,     7,    15,    12,    11,     0,
      14,    13,     6,     0,     0,     6,    10,     5,     4,     0,
       9,    20,     0,    16,     0,    29,     4,    22,     0,     0,
      20,    37,     0,    29,     0,    23,    24,     0,    27,    25,
      26,     3,     0,     0,     0,     0,    29,     0,    39,    28,
       0,    17,     0,    22,     0,    43,    44,    51,     0,    42,
      45,    46,     0,     0,     0,     0,     0,     0,    67,     0,
       0,     0,     0,     0,     0,    46,     0,    21,     0,     0,
       0,    40,    41,     0,     0,    48,    50,    49,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    71,    38,    18,    31,    34,    30,    20,
      64,     0,     0,    66,    68,    62,    63,    56,    61,    59,
      60,    57,    58,    53,    52,    55,    54,    70,     0,    36,
      19,    47,    65,     0,     0,     0,    33,    69,    32,    36,
      35
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     8,    10,    27,    22,    32,    61,    35,
      53,    43,    44,    45,    46,   138,   146,    47,    78,    79,
      48,    49,    50
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -85
static const yytype_int16 yypact[] =
{
       0,    -4,    36,   -85,    17,   -85,    12,    26,    20,    31,
      46,    52,    26,   210,   210,   -85,   -85,   -85,   -85,    43,
     -85,   -85,    -3,    48,    54,    12,   -85,   -85,     0,    53,
     -85,    70,    64,   -85,    57,    13,     0,    60,    75,    76,
      70,    82,    78,    13,    94,   -85,   -85,    84,   -85,   -85,
     -85,   -85,    80,    99,    55,    55,    13,    55,   -85,   -85,
      55,   -85,    47,    60,   210,   -85,   -85,   -85,    55,   -85,
     -85,    95,    55,    55,    88,   -27,    55,    55,   -85,   146,
     167,   100,   228,   112,   102,    16,   125,   -85,   105,   188,
      55,   -12,   -12,    55,    96,   -85,   -85,   -85,   259,   106,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,   106,   -85,   -85,   -85,   -85,    55,   -85,    70,
     -85,   247,   209,   -85,   117,   286,   296,   305,   134,   154,
     195,   215,   -32,   -12,   -12,   -85,   -85,   -85,   108,   275,
     -85,   -85,   -85,   106,   120,    55,   -85,   -85,   -85,   275,
     -85
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -85,   -85,     1,     8,   124,   -85,    -6,   -85,   -85,   -39,
      77,   -85,   -37,   -85,   -85,   -85,    50,   142,   -70,   -55,
     -85,   -85,   -84
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      80,    56,    82,    41,    95,    83,    59,    86,    23,   108,
     109,   110,   111,    89,     1,   124,    25,    91,    92,    81,
      42,    97,    98,    38,    95,    39,     4,     7,   137,    31,
      26,   110,   111,    30,    40,   121,     5,    51,   122,   117,
       6,    90,     7,    41,    11,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,     9,    88,   147,
      42,    12,   139,    65,    66,    67,    13,    14,    24,    28,
      68,    65,    66,    67,    69,    84,    70,    85,    68,    33,
     140,    29,    69,    34,    70,    71,    36,    37,    72,    73,
     149,    52,    74,    75,    76,    77,    72,    73,    54,    55,
      74,    75,    76,    77,    65,    66,    67,    57,    58,    60,
      63,    93,    65,    66,    67,    69,    62,    70,    71,    64,
      90,   116,   113,    69,   119,    70,    71,    40,   143,    72,
      73,   115,   144,    94,    75,    76,    15,    72,    73,   148,
      87,    94,    75,    76,   118,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,     0,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
      99,   104,   105,   106,   107,   108,   109,   110,   111,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   105,   106,   107,   108,   109,   110,   111,   150,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   120,    16,    17,    18,    19,    96,    20,    21,
       0,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   142,   106,   107,   108,   109,   110,   111,
       0,     0,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   114,   107,   108,   109,   110,   111,
       0,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   141,     0,     0,     0,     0,     0,     0,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,     0,     0,   145,   123,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   103,   104,   105,   106,   107,   108,   109,   110,   111
};

static const yytype_int16 yycheck[] =
{
      55,    40,    57,    30,    74,    60,    43,    62,    14,    41,
      42,    43,    44,    68,    14,    99,    19,    72,    73,    56,
      47,    76,    77,    10,    94,    12,    30,    30,   112,    28,
      22,    43,    44,    25,    21,    90,     0,    36,    93,    23,
      23,    25,    30,    30,    24,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,    31,    64,   143,
      47,    30,   117,    16,    17,    18,    20,    15,    25,    21,
      23,    16,    17,    18,    27,    28,    29,    30,    23,    26,
     119,    27,    27,    13,    29,    30,    22,    30,    41,    42,
     145,    31,    45,    46,    47,    48,    41,    42,    23,    23,
      45,    46,    47,    48,    16,    17,    18,    25,    30,    15,
      30,    23,    16,    17,    18,    27,    32,    29,    30,    20,
      25,    19,    22,    27,    19,    29,    30,    21,    11,    41,
      42,    19,    24,    45,    46,    47,    12,    41,    42,    19,
      63,    45,    46,    47,    19,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    -1,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      24,    37,    38,    39,    40,    41,    42,    43,    44,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    24,    38,    39,    40,    41,    42,    43,    44,   149,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    24,     3,     4,     5,     6,    75,     8,     9,
      -1,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    24,    39,    40,    41,    42,    43,    44,
      -1,    -1,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    26,    40,    41,    42,    43,    44,
      -1,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    -1,    -1,    31,    48,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    36,    37,    38,    39,    40,    41,    42,    43,    44
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    14,    50,    51,    30,     0,    23,    30,    52,    31,
      53,    24,    30,    20,    15,    53,     3,     4,     5,     6,
       8,     9,    55,    55,    25,    19,    52,    54,    21,    27,
      52,    51,    56,    26,    13,    58,    22,    30,    10,    12,
      21,    30,    47,    60,    61,    62,    63,    66,    69,    70,
      71,    51,    31,    59,    23,    23,    58,    25,    30,    61,
      15,    57,    32,    30,    20,    16,    17,    18,    23,    27,
      29,    30,    41,    42,    45,    46,    47,    48,    67,    68,
      68,    61,    68,    68,    28,    30,    68,    59,    55,    68,
      25,    68,    68,    23,    45,    67,    66,    68,    68,    24,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    24,    22,    26,    19,    19,    23,    19,    19,
      24,    68,    68,    48,    71,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    71,    64,    68,
      58,    26,    24,    11,    24,    31,    65,    71,    19,    68,
      65
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 103 "parser.ypp"
    { ast = new ProgramImpl((yyvsp[(1) - (1)]).u_proc_list);;}
    break;

  case 3:
#line 108 "parser.ypp"
    {(yyvsp[(11) - (11)]).u_proc_list->push_front(new ProcImpl(new SymName((yyvsp[(2) - (11)]).u_base_charptr), (yyvsp[(4) - (11)]).u_decl_list, (yyvsp[(7) - (11)]).u_type, (yyvsp[(9) - (11)]).u_procedure_block)); (yyval) = (yyvsp[(11) - (11)]);;}
    break;

  case 4:
#line 110 "parser.ypp"
    {(yyval).u_proc_list = new std::list<Proc_ptr>();;}
    break;

  case 5:
#line 115 "parser.ypp"
    {(yyvsp[(2) - (5)]).u_symname_list->push_front(new SymName((yyvsp[(1) - (5)]).u_base_charptr));
	         (yyvsp[(5) - (5)]).u_decl_list->push_front(new DeclImpl((yyvsp[(2) - (5)]).u_symname_list, (yyvsp[(4) - (5)]).u_type)); (yyval) = (yyvsp[(5) - (5)]);;}
    break;

  case 6:
#line 118 "parser.ypp"
    {(yyval).u_decl_list = new std::list<Decl_ptr> ();;}
    break;

  case 7:
#line 121 "parser.ypp"
    {(yyvsp[(3) - (3)]).u_symname_list->push_front(new SymName((yyvsp[(2) - (3)]).u_base_charptr)); (yyval)=(yyvsp[(3) - (3)]);;}
    break;

  case 8:
#line 123 "parser.ypp"
    {(yyval).u_symname_list = new std::list<SymName_ptr> ();;}
    break;

  case 9:
#line 127 "parser.ypp"
    {(yyval) = (yyvsp[(2) - (2)]);;}
    break;

  case 10:
#line 129 "parser.ypp"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 11:
#line 133 "parser.ypp"
    {(yyval).u_type = new TInteger();;}
    break;

  case 12:
#line 135 "parser.ypp"
    {(yyval).u_type = new TCharacter();;}
    break;

  case 13:
#line 137 "parser.ypp"
    {(yyval).u_type = new TCharPtr();;}
    break;

  case 14:
#line 139 "parser.ypp"
    {(yyval).u_type = new TIntPtr();;}
    break;

  case 15:
#line 141 "parser.ypp"
    {(yyval).u_type = new TBoolean();;}
    break;

  case 16:
#line 143 "parser.ypp"
    {(yyval).u_type = new TString(new Primitive((yyvsp[(3) - (4)]).u_base_int));;}
    break;

  case 17:
#line 148 "parser.ypp"
    {(yyval).u_procedure_block = new Procedure_blockImpl((yyvsp[(1) - (4)]).u_proc_list, (yyvsp[(2) - (4)]).u_decl_list, (yyvsp[(3) - (4)]).u_stat_list, (yyvsp[(4) - (4)]).u_return_stat);;}
    break;

  case 18:
#line 153 "parser.ypp"
    {(yyval).u_return_stat = new Return((yyvsp[(2) - (3)]).u_expr);;}
    break;

  case 19:
#line 159 "parser.ypp"
    {(yyvsp[(3) - (7)]).u_symname_list->push_front(new SymName((yyvsp[(2) - (7)]).u_base_charptr));
 	         (yyvsp[(7) - (7)]).u_decl_list->push_front(new DeclImpl((yyvsp[(3) - (7)]).u_symname_list, (yyvsp[(5) - (7)]).u_type)); (yyval) = (yyvsp[(7) - (7)]);;}
    break;

  case 20:
#line 162 "parser.ypp"
    {(yyval).u_decl_list = new std::list<Decl_ptr> ();;}
    break;

  case 21:
#line 167 "parser.ypp"
    {(yyvsp[(3) - (3)]).u_symname_list->push_front(new SymName((yyvsp[(2) - (3)]).u_base_charptr)); (yyval)=(yyvsp[(3) - (3)]); ;}
    break;

  case 22:
#line 169 "parser.ypp"
    {(yyval).u_symname_list = new std::list<SymName_ptr> ();;}
    break;

  case 23:
#line 174 "parser.ypp"
    {(yyval).u_stat = (yyvsp[(1) - (1)]).u_stat;;}
    break;

  case 24:
#line 176 "parser.ypp"
    {(yyval).u_stat = (yyvsp[(1) - (1)]).u_stat;;}
    break;

  case 25:
#line 178 "parser.ypp"
    {(yyval).u_stat = (yyvsp[(1) - (1)]).u_stat;;}
    break;

  case 26:
#line 180 "parser.ypp"
    {(yyval).u_stat = (yyvsp[(1) - (1)]).u_stat;;}
    break;

  case 27:
#line 182 "parser.ypp"
    {(yyval).u_stat = (yyvsp[(1) - (1)]).u_stat;;}
    break;

  case 28:
#line 186 "parser.ypp"
    {(yyvsp[(2) - (2)]).u_stat_list->push_front((yyvsp[(1) - (2)]).u_stat); (yyval).u_stat_list = (yyvsp[(2) - (2)]).u_stat_list;;}
    break;

  case 29:
#line 188 "parser.ypp"
    {(yyval).u_stat_list = new std::list<Stat_ptr> ();;}
    break;

  case 30:
#line 192 "parser.ypp"
    {(yyval).u_stat = new Assignment((yyvsp[(1) - (4)]).u_lhs, (yyvsp[(3) - (4)]).u_expr);;}
    break;

  case 31:
#line 194 "parser.ypp"
    {(yyval).u_stat = new StringAssignment((yyvsp[(1) - (4)]).u_lhs, new StringPrimitive((yyvsp[(3) - (4)]).u_base_charptr));;}
    break;

  case 32:
#line 198 "parser.ypp"
    {(yyval).u_stat = new Call((yyvsp[(1) - (7)]).u_lhs, new SymName((yyvsp[(3) - (7)]).u_base_charptr), (yyvsp[(5) - (7)]).u_expr_list);;}
    break;

  case 33:
#line 202 "parser.ypp"
    {(yyvsp[(2) - (2)]).u_expr_list->push_front((yyvsp[(1) - (2)]).u_expr); (yyval).u_expr_list = (yyvsp[(2) - (2)]).u_expr_list;;}
    break;

  case 34:
#line 204 "parser.ypp"
    {(yyval).u_expr_list = new std::list<Expr_ptr>();;}
    break;

  case 35:
#line 208 "parser.ypp"
    {(yyvsp[(3) - (3)]).u_expr_list->push_front((yyvsp[(2) - (3)]).u_expr); (yyval).u_expr_list = (yyvsp[(3) - (3)]).u_expr_list;;}
    break;

  case 36:
#line 210 "parser.ypp"
    {(yyval).u_expr_list = new std::list<Expr_ptr>();;}
    break;

  case 37:
#line 214 "parser.ypp"
    {(yyval).u_lhs = new Variable(new SymName((yyvsp[(1) - (1)]).u_base_charptr));;}
    break;

  case 38:
#line 216 "parser.ypp"
    {(yyval).u_lhs = new ArrayElement(new SymName((yyvsp[(1) - (4)]).u_base_charptr), (yyvsp[(3) - (4)]).u_expr);;}
    break;

  case 39:
#line 218 "parser.ypp"
    {(yyval).u_lhs = new DerefVariable(new SymName((yyvsp[(2) - (2)]).u_base_charptr));;}
    break;

  case 40:
#line 223 "parser.ypp"
    {(yyval).u_expr = new Uminus((yyvsp[(2) - (2)]).u_expr);;}
    break;

  case 41:
#line 225 "parser.ypp"
    {(yyval).u_expr = (yyvsp[(2) - (2)]).u_expr;;}
    break;

  case 42:
#line 227 "parser.ypp"
    {(yyval).u_expr = new IntLit(new Primitive((yyvsp[(1) - (1)]).u_base_int));;}
    break;

  case 43:
#line 229 "parser.ypp"
    {(yyval).u_expr = new BoolLit(new Primitive((yyvsp[(1) - (1)]).u_base_int));;}
    break;

  case 44:
#line 231 "parser.ypp"
    {(yyval).u_expr = new BoolLit(new Primitive((yyvsp[(1) - (1)]).u_base_int));;}
    break;

  case 45:
#line 233 "parser.ypp"
    {(yyval).u_expr = new CharLit(new Primitive((yyvsp[(1) - (1)]).u_base_int));;}
    break;

  case 46:
#line 235 "parser.ypp"
    {(yyval).u_expr = new Ident(new SymName((yyvsp[(1) - (1)]).u_base_charptr));;}
    break;

  case 47:
#line 237 "parser.ypp"
    {(yyval).u_expr = new ArrayAccess(new SymName((yyvsp[(1) - (4)]).u_base_charptr), (yyvsp[(3) - (4)]).u_expr);;}
    break;

  case 48:
#line 239 "parser.ypp"
    {(yyval).u_expr = new Not((yyvsp[(2) - (2)]).u_expr);;}
    break;

  case 49:
#line 241 "parser.ypp"
    {(yyval).u_expr = new Deref((yyvsp[(2) - (2)]).u_expr);;}
    break;

  case 50:
#line 242 "parser.ypp"
    {(yyval).u_expr = new AddressOf((yyvsp[(2) - (2)]).u_lhs);;}
    break;

  case 51:
#line 244 "parser.ypp"
    {(yyval).u_expr = new IntLit(new Primitive((yyvsp[(1) - (1)]).u_base_int));;}
    break;

  case 52:
#line 249 "parser.ypp"
    {(yyval).u_expr = new Plus((yyvsp[(1) - (3)]).u_expr, (yyvsp[(3) - (3)]).u_expr);;}
    break;

  case 53:
#line 251 "parser.ypp"
    {(yyval).u_expr = new Minus((yyvsp[(1) - (3)]).u_expr, (yyvsp[(3) - (3)]).u_expr);;}
    break;

  case 54:
#line 253 "parser.ypp"
    {(yyval).u_expr = new Times((yyvsp[(1) - (3)]).u_expr, (yyvsp[(3) - (3)]).u_expr);;}
    break;

  case 55:
#line 255 "parser.ypp"
    {(yyval).u_expr = new Div((yyvsp[(1) - (3)]).u_expr,(yyvsp[(3) - (3)]).u_expr);;}
    break;

  case 56:
#line 257 "parser.ypp"
    {(yyval).u_expr = new Compare((yyvsp[(1) - (3)]).u_expr, (yyvsp[(3) - (3)]).u_expr);;}
    break;

  case 57:
#line 259 "parser.ypp"
    {(yyval).u_expr = new Lt((yyvsp[(1) - (3)]).u_expr, (yyvsp[(3) - (3)]).u_expr);;}
    break;

  case 58:
#line 261 "parser.ypp"
    {(yyval).u_expr = new Lteq((yyvsp[(1) - (3)]).u_expr, (yyvsp[(3) - (3)]).u_expr);;}
    break;

  case 59:
#line 263 "parser.ypp"
    {(yyval).u_expr = new Gt((yyvsp[(1) - (3)]).u_expr, (yyvsp[(3) - (3)]).u_expr);;}
    break;

  case 60:
#line 265 "parser.ypp"
    {(yyval).u_expr = new Gteq((yyvsp[(1) - (3)]).u_expr, (yyvsp[(3) - (3)]).u_expr);;}
    break;

  case 61:
#line 267 "parser.ypp"
    {(yyval).u_expr = new Noteq((yyvsp[(1) - (3)]).u_expr, (yyvsp[(3) - (3)]).u_expr);;}
    break;

  case 62:
#line 269 "parser.ypp"
    {(yyval).u_expr = new Or((yyvsp[(1) - (3)]).u_expr, (yyvsp[(3) - (3)]).u_expr);;}
    break;

  case 63:
#line 271 "parser.ypp"
    {(yyval).u_expr = new And((yyvsp[(1) - (3)]).u_expr, (yyvsp[(3) - (3)]).u_expr);;}
    break;

  case 64:
#line 273 "parser.ypp"
    {(yyval).u_expr = (yyvsp[(2) - (3)]).u_expr;;}
    break;

  case 65:
#line 275 "parser.ypp"
    {(yyval).u_expr = new Not((yyvsp[(3) - (4)]).u_expr);;}
    break;

  case 66:
#line 277 "parser.ypp"
    {(yyval).u_expr = new AbsoluteValue((yyvsp[(2) - (3)]).u_expr);;}
    break;

  case 67:
#line 279 "parser.ypp"
    {(yyval).u_expr = (yyvsp[(1) - (1)]).u_expr;;}
    break;

  case 68:
#line 285 "parser.ypp"
    {(yyval).u_stat = new IfNoElse((yyvsp[(3) - (5)]).u_expr, (yyvsp[(5) - (5)]).u_nested_block);;}
    break;

  case 69:
#line 287 "parser.ypp"
    {(yyval).u_stat = new IfWithElse((yyvsp[(3) - (7)]).u_expr, (yyvsp[(5) - (7)]).u_nested_block, (yyvsp[(7) - (7)]).u_nested_block);;}
    break;

  case 70:
#line 292 "parser.ypp"
    {(yyval).u_stat = new WhileLoop((yyvsp[(3) - (5)]).u_expr, (yyvsp[(5) - (5)]).u_nested_block);;}
    break;

  case 71:
#line 297 "parser.ypp"
    {(yyval).u_stat = new CodeBlock(new Nested_blockImpl((yyvsp[(2) - (4)]).u_decl_list, (yyvsp[(3) - (4)]).u_stat_list));;}
    break;


/* Line 1267 of yacc.c.  */
#line 1934 "parser.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 300 "parser.ypp"


/** You shall not pass!
 *  You should not  have to do or edit anything past this.
 */

extern int yylineno;

void yyerror(const char *s)
{
    fprintf(stderr, "%s at line %d\n", s, yylineno);
    return;
}

