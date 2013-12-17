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
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ATTRIBUTE = 258,
     CONST_QUAL = 259,
     STATIC_QUAL = 260,
     BOOL_TYPE = 261,
     FLOAT_TYPE = 262,
     INT_TYPE = 263,
     STRING_TYPE = 264,
     FIXED_TYPE = 265,
     HALF_TYPE = 266,
     BREAK = 267,
     CONTINUE = 268,
     DO = 269,
     ELSE = 270,
     FOR = 271,
     IF = 272,
     DISCARD = 273,
     RETURN = 274,
     BVEC2 = 275,
     BVEC3 = 276,
     BVEC4 = 277,
     IVEC2 = 278,
     IVEC3 = 279,
     IVEC4 = 280,
     VEC2 = 281,
     VEC3 = 282,
     VEC4 = 283,
     HVEC2 = 284,
     HVEC3 = 285,
     HVEC4 = 286,
     FVEC2 = 287,
     FVEC3 = 288,
     FVEC4 = 289,
     MATRIX2 = 290,
     MATRIX3 = 291,
     MATRIX4 = 292,
     HMATRIX2 = 293,
     HMATRIX3 = 294,
     HMATRIX4 = 295,
     FMATRIX2 = 296,
     FMATRIX3 = 297,
     FMATRIX4 = 298,
     IN_QUAL = 299,
     OUT_QUAL = 300,
     INOUT_QUAL = 301,
     UNIFORM = 302,
     VARYING = 303,
     STRUCT = 304,
     VOID_TYPE = 305,
     WHILE = 306,
     SAMPLER1D = 307,
     SAMPLER2D = 308,
     SAMPLER3D = 309,
     SAMPLERCUBE = 310,
     SAMPLER1DSHADOW = 311,
     SAMPLER2DSHADOW = 312,
     SAMPLERRECT = 313,
     SAMPLERGENERIC = 314,
     VECTOR = 315,
     MATRIX = 316,
     REGISTER = 317,
     TEXTURE = 318,
     SAMPLERSTATE = 319,
     IDENTIFIER = 320,
     TYPE_NAME = 321,
     FLOATCONSTANT = 322,
     INTCONSTANT = 323,
     BOOLCONSTANT = 324,
     STRINGCONSTANT = 325,
     FIELD_SELECTION = 326,
     LEFT_OP = 327,
     RIGHT_OP = 328,
     INC_OP = 329,
     DEC_OP = 330,
     LE_OP = 331,
     GE_OP = 332,
     EQ_OP = 333,
     NE_OP = 334,
     AND_OP = 335,
     OR_OP = 336,
     XOR_OP = 337,
     MUL_ASSIGN = 338,
     DIV_ASSIGN = 339,
     ADD_ASSIGN = 340,
     MOD_ASSIGN = 341,
     LEFT_ASSIGN = 342,
     RIGHT_ASSIGN = 343,
     AND_ASSIGN = 344,
     XOR_ASSIGN = 345,
     OR_ASSIGN = 346,
     SUB_ASSIGN = 347,
     LEFT_PAREN = 348,
     RIGHT_PAREN = 349,
     LEFT_BRACKET = 350,
     RIGHT_BRACKET = 351,
     LEFT_BRACE = 352,
     RIGHT_BRACE = 353,
     DOT = 354,
     COMMA = 355,
     COLON = 356,
     EQUAL = 357,
     SEMICOLON = 358,
     BANG = 359,
     DASH = 360,
     TILDE = 361,
     PLUS = 362,
     STAR = 363,
     SLASH = 364,
     PERCENT = 365,
     LEFT_ANGLE = 366,
     RIGHT_ANGLE = 367,
     VERTICAL_BAR = 368,
     CARET = 369,
     AMPERSAND = 370,
     QUESTION = 371
   };
#endif
/* Tokens.  */
#define ATTRIBUTE 258
#define CONST_QUAL 259
#define STATIC_QUAL 260
#define BOOL_TYPE 261
#define FLOAT_TYPE 262
#define INT_TYPE 263
#define STRING_TYPE 264
#define FIXED_TYPE 265
#define HALF_TYPE 266
#define BREAK 267
#define CONTINUE 268
#define DO 269
#define ELSE 270
#define FOR 271
#define IF 272
#define DISCARD 273
#define RETURN 274
#define BVEC2 275
#define BVEC3 276
#define BVEC4 277
#define IVEC2 278
#define IVEC3 279
#define IVEC4 280
#define VEC2 281
#define VEC3 282
#define VEC4 283
#define HVEC2 284
#define HVEC3 285
#define HVEC4 286
#define FVEC2 287
#define FVEC3 288
#define FVEC4 289
#define MATRIX2 290
#define MATRIX3 291
#define MATRIX4 292
#define HMATRIX2 293
#define HMATRIX3 294
#define HMATRIX4 295
#define FMATRIX2 296
#define FMATRIX3 297
#define FMATRIX4 298
#define IN_QUAL 299
#define OUT_QUAL 300
#define INOUT_QUAL 301
#define UNIFORM 302
#define VARYING 303
#define STRUCT 304
#define VOID_TYPE 305
#define WHILE 306
#define SAMPLER1D 307
#define SAMPLER2D 308
#define SAMPLER3D 309
#define SAMPLERCUBE 310
#define SAMPLER1DSHADOW 311
#define SAMPLER2DSHADOW 312
#define SAMPLERRECT 313
#define SAMPLERGENERIC 314
#define VECTOR 315
#define MATRIX 316
#define REGISTER 317
#define TEXTURE 318
#define SAMPLERSTATE 319
#define IDENTIFIER 320
#define TYPE_NAME 321
#define FLOATCONSTANT 322
#define INTCONSTANT 323
#define BOOLCONSTANT 324
#define STRINGCONSTANT 325
#define FIELD_SELECTION 326
#define LEFT_OP 327
#define RIGHT_OP 328
#define INC_OP 329
#define DEC_OP 330
#define LE_OP 331
#define GE_OP 332
#define EQ_OP 333
#define NE_OP 334
#define AND_OP 335
#define OR_OP 336
#define XOR_OP 337
#define MUL_ASSIGN 338
#define DIV_ASSIGN 339
#define ADD_ASSIGN 340
#define MOD_ASSIGN 341
#define LEFT_ASSIGN 342
#define RIGHT_ASSIGN 343
#define AND_ASSIGN 344
#define XOR_ASSIGN 345
#define OR_ASSIGN 346
#define SUB_ASSIGN 347
#define LEFT_PAREN 348
#define RIGHT_PAREN 349
#define LEFT_BRACKET 350
#define RIGHT_BRACKET 351
#define LEFT_BRACE 352
#define RIGHT_BRACE 353
#define DOT 354
#define COMMA 355
#define COLON 356
#define EQUAL 357
#define SEMICOLON 358
#define BANG 359
#define DASH 360
#define TILDE 361
#define PLUS 362
#define STAR 363
#define SLASH 364
#define PERCENT 365
#define LEFT_ANGLE 366
#define RIGHT_ANGLE 367
#define VERTICAL_BAR 368
#define CARET 369
#define AMPERSAND 370
#define QUESTION 371




/* Copy the first part of user declarations.  */
#line 9 "hlslang.y"


/* Based on:
ANSI C Yacc grammar

In 1985, Jeff Lee published his Yacc grammar (which is accompanied by a 
matching Lex specification) for the April 30, 1985 draft version of the 
ANSI C standard.  Tom Stockfisch reposted it to net.sources in 1987; that
original, as mentioned in the answer to question 17.25 of the comp.lang.c
FAQ, can be ftp'ed from ftp.uu.net, file usenet/net.sources/ansi.c.grammar.Z.
 
I intend to keep this version as close to the current C Standard grammar as 
possible; please let me know if you discover discrepancies. 

Jutta Degener, 1995 
*/

#include "SymbolTable.h"
#include "ParseHelper.h"
#include "../../include/hlsl2glsl.h"

#ifdef _WIN32
#undef _WIN32
#endif

#ifdef _WIN32
    #define YYPARSE_PARAM parseContext
    #define YYPARSE_PARAM_DECL TParseContext&
    #define YY_DECL int yylex(YYSTYPE* pyylval, TParseContext& parseContext)
    #define YYLEX_PARAM parseContext
#else
    #define YYPARSE_PARAM parseContextLocal
	#define YYPARSE_PARAM_DECL void *
    #define parseContext (*((TParseContext*)(parseContextLocal)))
    #define YY_DECL int yylex(YYSTYPE* pyylval, void* parseContextLocal)
    #define YYLEX_PARAM (void*)(parseContextLocal)
    extern void yyerror(char*);    
#endif

#define FRAG_VERT_ONLY(S, L) {                                                  \
    if (parseContext.language != EShLangFragment &&                             \
        parseContext.language != EShLangVertex) {                               \
        parseContext.error(L, " supported in vertex/fragment shaders only ", S, "", "");   \
        parseContext.recover();                                                            \
    }                                                                           \
}

#define VERTEX_ONLY(S, L) {                                                     \
    if (parseContext.language != EShLangVertex) {                               \
        parseContext.error(L, " supported in vertex shaders only ", S, "", "");            \
        parseContext.recover();                                                            \
    }                                                                           \
}

#define FRAG_ONLY(S, L) {                                                       \
    if (parseContext.language != EShLangFragment) {                             \
        parseContext.error(L, " supported in fragment shaders only ", S, "", "");          \
        parseContext.recover();                                                            \
    }                                                                           \
}

#define UNSUPPORTED_FEATURE(S, L) {                                                       \
    parseContext.error(L, " not supported ", S, "", "");              \
    parseContext.recover();                                                            \
}

#define SET_BASIC_TYPE(RES,PAR,T,PREC) \
	TQualifier qual = parseContext.getDefaultQualifier(); \
	(RES).setBasic(T, qual, (PAR).line); \
	(RES).precision = PREC




/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 82 "hlslang.y"
{
    struct {
        TSourceLoc line;
        union {
            TString *string;
            float f;
            int i;
            bool b;
        };
        TSymbol* symbol;
    } lex;
    struct {
        TSourceLoc line;
        TOperator op;
        union {
            TIntermNode* intermNode;
            TIntermNodePair nodePair;
            TIntermTyped* intermTypedNode;
            TIntermAggregate* intermAggregate;
        };
        union {
            TPublicType type;
            TQualifier qualifier;
            TFunction* function;
            TParameter param;
            TTypeLine typeLine;
            TTypeList* typeList;
	    TAnnotation* ann;
	    TTypeInfo* typeInfo;
        };
    } interm;
}
/* Line 193 of yacc.c.  */
#line 435 "hlslang_tab.cpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */
#line 115 "hlslang.y"

#ifndef _WIN32
    extern int yylex(YYSTYPE*, void*);
#endif


/* Line 216 of yacc.c.  */
#line 453 "hlslang_tab.cpp"

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
#define YYFINAL  83
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2251

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  117
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  93
/* YYNRULES -- Number of rules.  */
#define YYNRULES  302
/* YYNRULES -- Number of states.  */
#define YYNSTATES  474

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   371

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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    11,    13,    17,    19,
      24,    26,    30,    33,    36,    38,    40,    42,    46,    49,
      52,    55,    57,    60,    64,    67,    69,    71,    73,    75,
      78,    81,    84,    89,    91,    93,    95,    97,    99,   103,
     107,   111,   113,   117,   121,   123,   127,   131,   133,   137,
     141,   145,   149,   151,   155,   159,   161,   165,   167,   171,
     173,   177,   179,   183,   185,   189,   191,   195,   197,   203,
     205,   209,   211,   213,   215,   217,   219,   221,   223,   225,
     227,   229,   231,   233,   237,   239,   242,   245,   248,   253,
     255,   257,   260,   264,   268,   271,   276,   280,   285,   291,
     299,   303,   306,   310,   313,   314,   316,   318,   320,   322,
     324,   329,   336,   344,   353,   363,   370,   372,   376,   382,
     389,   397,   406,   412,   414,   417,   419,   421,   424,   426,
     428,   430,   432,   437,   439,   441,   443,   445,   447,   449,
     456,   463,   470,   472,   474,   476,   478,   480,   482,   484,
     486,   488,   490,   492,   494,   496,   498,   500,   502,   504,
     506,   508,   510,   512,   514,   516,   518,   520,   522,   524,
     526,   528,   530,   532,   534,   536,   538,   540,   546,   551,
     553,   556,   560,   562,   566,   568,   572,   577,   584,   586,
     588,   590,   592,   594,   596,   598,   600,   602,   604,   606,
     609,   610,   611,   617,   619,   621,   624,   628,   630,   633,
     635,   638,   644,   648,   650,   652,   657,   658,   665,   666,
     675,   676,   684,   686,   688,   690,   691,   694,   698,   701,
     704,   707,   711,   714,   716,   719,   721,   723,   725,   726,
     730,   734,   739,   741,   743,   747,   751,   754,   758,   760,
     763,   769,   771,   773,   775,   777,   779,   781,   783,   785,
     787,   789,   791,   793,   795,   797,   799,   801,   803,   805,
     807,   809,   811,   813,   815,   817,   819,   821,   823,   825,
     830,   832,   836,   840,   846,   849,   850,   852,   854,   856,
     859,   862,   865,   869,   874,   878,   880,   883,   888,   895,
     902,   907,   914
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     189,     0,    -1,    65,    -1,   118,    -1,    68,    -1,    67,
      -1,    69,    -1,    93,   145,    94,    -1,   119,    -1,   120,
      95,   121,    96,    -1,   122,    -1,   120,    99,    71,    -1,
     120,    74,    -1,   120,    75,    -1,   145,    -1,   123,    -1,
     124,    -1,   120,    99,   124,    -1,   126,    94,    -1,   125,
      94,    -1,   127,    50,    -1,   127,    -1,   127,   143,    -1,
     126,   100,   143,    -1,   128,    93,    -1,   160,    -1,    65,
      -1,    71,    -1,   120,    -1,    74,   129,    -1,    75,   129,
      -1,   130,   129,    -1,    93,   161,    94,   129,    -1,   107,
      -1,   105,    -1,   104,    -1,   106,    -1,   129,    -1,   131,
     108,   129,    -1,   131,   109,   129,    -1,   131,   110,   129,
      -1,   131,    -1,   132,   107,   131,    -1,   132,   105,   131,
      -1,   132,    -1,   133,    72,   132,    -1,   133,    73,   132,
      -1,   133,    -1,   134,   111,   133,    -1,   134,   112,   133,
      -1,   134,    76,   133,    -1,   134,    77,   133,    -1,   134,
      -1,   135,    78,   134,    -1,   135,    79,   134,    -1,   135,
      -1,   136,   115,   135,    -1,   136,    -1,   137,   114,   136,
      -1,   137,    -1,   138,   113,   137,    -1,   138,    -1,   139,
      80,   138,    -1,   139,    -1,   140,    82,   139,    -1,   140,
      -1,   141,    81,   140,    -1,   141,    -1,   141,   116,   145,
     101,   143,    -1,   142,    -1,   129,   144,   143,    -1,   102,
      -1,    83,    -1,    84,    -1,    86,    -1,    85,    -1,    92,
      -1,    87,    -1,    88,    -1,    89,    -1,    90,    -1,    91,
      -1,   143,    -1,   145,   100,   143,    -1,   142,    -1,   148,
     103,    -1,   156,   103,    -1,   149,    94,    -1,   149,    94,
     101,    65,    -1,   151,    -1,   150,    -1,   151,   153,    -1,
     150,   100,   153,    -1,   158,    65,    93,    -1,   160,    65,
      -1,   160,    65,   102,   167,    -1,   160,    65,   204,    -1,
     160,    65,   101,    65,    -1,   160,    65,    95,   146,    96,
      -1,   160,    65,    95,   146,    96,   101,    65,    -1,   159,
     154,   152,    -1,   154,   152,    -1,   159,   154,   155,    -1,
     154,   155,    -1,    -1,    44,    -1,    45,    -1,    46,    -1,
     160,    -1,   157,    -1,   156,   100,    65,   206,    -1,   156,
     100,    65,    95,    96,   206,    -1,   156,   100,    65,    95,
     146,    96,   206,    -1,   156,   100,    65,    95,    96,   206,
     102,   167,    -1,   156,   100,    65,    95,   146,    96,   206,
     102,   167,    -1,   156,   100,    65,   206,   102,   167,    -1,
     158,    -1,   158,    65,   206,    -1,   158,    65,    95,    96,
     206,    -1,   158,    65,    95,   146,    96,   206,    -1,   158,
      65,    95,    96,   206,   102,   167,    -1,   158,    65,    95,
     146,    96,   206,   102,   167,    -1,   158,    65,   206,   102,
     167,    -1,   160,    -1,   159,   160,    -1,     4,    -1,     5,
      -1,     5,     4,    -1,     3,    -1,    48,    -1,    47,    -1,
     161,    -1,   161,    95,   146,    96,    -1,    50,    -1,     7,
      -1,    11,    -1,    10,    -1,     8,    -1,     6,    -1,    60,
     111,     7,   100,    68,   112,    -1,    60,   111,     8,   100,
      68,   112,    -1,    60,   111,     6,   100,    68,   112,    -1,
      26,    -1,    27,    -1,    28,    -1,    29,    -1,    30,    -1,
      31,    -1,    32,    -1,    33,    -1,    34,    -1,    20,    -1,
      21,    -1,    22,    -1,    23,    -1,    24,    -1,    25,    -1,
      35,    -1,    36,    -1,    37,    -1,    38,    -1,    39,    -1,
      40,    -1,    41,    -1,    42,    -1,    43,    -1,    63,    -1,
      59,    -1,    52,    -1,    53,    -1,    54,    -1,    55,    -1,
      58,    -1,    56,    -1,    57,    -1,   162,    -1,    66,    -1,
      49,    65,    97,   163,    98,    -1,    49,    97,   163,    98,
      -1,   164,    -1,   163,   164,    -1,   160,   165,   103,    -1,
     166,    -1,   165,   100,   166,    -1,    65,    -1,    65,   101,
      65,    -1,    65,    95,   146,    96,    -1,    65,    95,   146,
      96,   101,    65,    -1,   143,    -1,   193,    -1,   207,    -1,
     147,    -1,   171,    -1,   170,    -1,   168,    -1,   177,    -1,
     178,    -1,   181,    -1,   188,    -1,    97,    98,    -1,    -1,
      -1,    97,   172,   176,   173,    98,    -1,   175,    -1,   170,
      -1,    97,    98,    -1,    97,   176,    98,    -1,   169,    -1,
     176,   169,    -1,   103,    -1,   145,   103,    -1,    17,    93,
     145,    94,   179,    -1,   169,    15,   169,    -1,   169,    -1,
     145,    -1,   158,    65,   102,   167,    -1,    -1,    51,    93,
     182,   180,    94,   174,    -1,    -1,    14,   183,   169,    51,
      93,   145,    94,   103,    -1,    -1,    16,    93,   184,   185,
     187,    94,   174,    -1,   177,    -1,   168,    -1,   180,    -1,
      -1,   186,   103,    -1,   186,   103,   145,    -1,    13,   103,
      -1,    12,   103,    -1,    19,   103,    -1,    19,   145,   103,
      -1,    18,   103,    -1,   190,    -1,   189,   190,    -1,   191,
      -1,   147,    -1,   103,    -1,    -1,   148,   192,   175,    -1,
      97,   194,    98,    -1,    97,   194,   100,    98,    -1,   143,
      -1,   193,    -1,   194,   100,   143,    -1,   194,   100,   193,
      -1,   111,   112,    -1,   111,   196,   112,    -1,   197,    -1,
     196,   197,    -1,   198,    65,   102,   199,   103,    -1,     7,
      -1,    11,    -1,    10,    -1,     8,    -1,     6,    -1,     9,
      -1,    20,    -1,    21,    -1,    22,    -1,    23,    -1,    24,
      -1,    25,    -1,    26,    -1,    27,    -1,    28,    -1,    29,
      -1,    30,    -1,    31,    -1,    32,    -1,    33,    -1,    34,
      -1,   200,    -1,    70,    -1,   201,    -1,   203,    -1,    68,
      -1,    69,    -1,    67,    -1,   198,    93,   202,    94,    -1,
     200,    -1,   202,   100,   200,    -1,    97,   202,    98,    -1,
     101,    62,    93,    65,    94,    -1,   101,    65,    -1,    -1,
     205,    -1,   204,    -1,   195,    -1,   205,   195,    -1,   205,
     204,    -1,   204,   195,    -1,   205,   204,   195,    -1,    64,
      97,   208,    98,    -1,    64,    97,    98,    -1,   209,    -1,
     208,   209,    -1,    65,   102,    65,   103,    -1,    65,   102,
     111,    65,   112,   103,    -1,    65,   102,    93,    65,    94,
     103,    -1,    63,   102,    65,   103,    -1,    63,   102,   111,
      65,   112,   103,    -1,    63,   102,    93,    65,    94,   103,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   190,   190,   226,   229,   234,   239,   244,   250,   253,
     330,   333,   452,   462,   475,   483,   597,   600,   618,   622,
     629,   633,   640,   649,   661,   669,   730,   742,   752,   755,
     765,   775,   793,   864,   865,   866,   867,   873,   874,   883,
     892,   903,   904,   912,   923,   924,   933,   945,   946,   956,
     966,   976,   989,   990,  1001,  1015,  1016,  1028,  1029,  1041,
    1042,  1054,  1055,  1068,  1069,  1082,  1083,  1096,  1097,  1112,
    1113,  1127,  1128,  1129,  1130,  1131,  1132,  1133,  1134,  1135,
    1136,  1137,  1141,  1144,  1155,  1163,  1164,  1172,  1205,  1242,
    1245,  1252,  1260,  1281,  1306,  1317,  1330,  1342,  1354,  1372,
    1401,  1406,  1416,  1421,  1431,  1434,  1437,  1440,  1446,  1453,
    1456,  1467,  1485,  1506,  1537,  1571,  1608,  1612,  1625,  1644,
    1667,  1701,  1738,  1789,  1792,  1814,  1817,  1822,  1827,  1833,
    1841,  1849,  1852,  1867,  1870,  1873,  1876,  1879,  1882,  1885,
    1896,  1907,  1918,  1922,  1926,  1930,  1934,  1938,  1942,  1946,
    1950,  1954,  1958,  1962,  1966,  1970,  1974,  1978,  1983,  1988,
    1993,  1998,  2003,  2008,  2013,  2018,  2023,  2027,  2031,  2035,
    2039,  2043,  2047,  2051,  2055,  2059,  2064,  2076,  2086,  2094,
    2097,  2112,  2144,  2148,  2154,  2159,  2165,  2175,  2191,  2192,
    2193,  2197,  2201,  2202,  2208,  2209,  2210,  2211,  2212,  2216,
    2217,  2217,  2217,  2225,  2226,  2231,  2234,  2242,  2245,  2251,
    2252,  2256,  2264,  2268,  2278,  2283,  2300,  2300,  2305,  2305,
    2312,  2312,  2325,  2328,  2334,  2337,  2343,  2347,  2354,  2361,
    2368,  2375,  2395,  2404,  2408,  2415,  2418,  2421,  2425,  2425,
    2533,  2536,  2543,  2547,  2551,  2555,  2562,  2566,  2572,  2576,
    2583,  2589,  2590,  2591,  2592,  2593,  2594,  2595,  2596,  2597,
    2598,  2599,  2600,  2601,  2602,  2603,  2604,  2605,  2606,  2607,
    2608,  2609,  2613,  2614,  2615,  2616,  2620,  2623,  2626,  2632,
    2636,  2637,  2641,  2645,  2651,  2655,  2656,  2657,  2658,  2659,
    2660,  2661,  2662,  2666,  2671,  2676,  2678,  2683,  2684,  2685,
    2686,  2687,  2688
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ATTRIBUTE", "CONST_QUAL", "STATIC_QUAL",
  "BOOL_TYPE", "FLOAT_TYPE", "INT_TYPE", "STRING_TYPE", "FIXED_TYPE",
  "HALF_TYPE", "BREAK", "CONTINUE", "DO", "ELSE", "FOR", "IF", "DISCARD",
  "RETURN", "BVEC2", "BVEC3", "BVEC4", "IVEC2", "IVEC3", "IVEC4", "VEC2",
  "VEC3", "VEC4", "HVEC2", "HVEC3", "HVEC4", "FVEC2", "FVEC3", "FVEC4",
  "MATRIX2", "MATRIX3", "MATRIX4", "HMATRIX2", "HMATRIX3", "HMATRIX4",
  "FMATRIX2", "FMATRIX3", "FMATRIX4", "IN_QUAL", "OUT_QUAL", "INOUT_QUAL",
  "UNIFORM", "VARYING", "STRUCT", "VOID_TYPE", "WHILE", "SAMPLER1D",
  "SAMPLER2D", "SAMPLER3D", "SAMPLERCUBE", "SAMPLER1DSHADOW",
  "SAMPLER2DSHADOW", "SAMPLERRECT", "SAMPLERGENERIC", "VECTOR", "MATRIX",
  "REGISTER", "TEXTURE", "SAMPLERSTATE", "IDENTIFIER", "TYPE_NAME",
  "FLOATCONSTANT", "INTCONSTANT", "BOOLCONSTANT", "STRINGCONSTANT",
  "FIELD_SELECTION", "LEFT_OP", "RIGHT_OP", "INC_OP", "DEC_OP", "LE_OP",
  "GE_OP", "EQ_OP", "NE_OP", "AND_OP", "OR_OP", "XOR_OP", "MUL_ASSIGN",
  "DIV_ASSIGN", "ADD_ASSIGN", "MOD_ASSIGN", "LEFT_ASSIGN", "RIGHT_ASSIGN",
  "AND_ASSIGN", "XOR_ASSIGN", "OR_ASSIGN", "SUB_ASSIGN", "LEFT_PAREN",
  "RIGHT_PAREN", "LEFT_BRACKET", "RIGHT_BRACKET", "LEFT_BRACE",
  "RIGHT_BRACE", "DOT", "COMMA", "COLON", "EQUAL", "SEMICOLON", "BANG",
  "DASH", "TILDE", "PLUS", "STAR", "SLASH", "PERCENT", "LEFT_ANGLE",
  "RIGHT_ANGLE", "VERTICAL_BAR", "CARET", "AMPERSAND", "QUESTION",
  "$accept", "variable_identifier", "primary_expression",
  "postfix_expression", "integer_expression", "function_call",
  "function_call_or_method", "function_call_generic",
  "function_call_header_no_parameters",
  "function_call_header_with_parameters", "function_call_header",
  "function_identifier", "unary_expression", "unary_operator",
  "multiplicative_expression", "additive_expression", "shift_expression",
  "relational_expression", "equality_expression", "and_expression",
  "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_xor_expression",
  "logical_or_expression", "conditional_expression",
  "assignment_expression", "assignment_operator", "expression",
  "constant_expression", "declaration", "function_prototype",
  "function_declarator", "function_header_with_parameters",
  "function_header", "parameter_declarator", "parameter_declaration",
  "parameter_qualifier", "parameter_type_specifier",
  "init_declarator_list", "single_declaration", "fully_specified_type",
  "type_qualifier", "type_specifier", "type_specifier_nonarray",
  "struct_specifier", "struct_declaration_list", "struct_declaration",
  "struct_declarator_list", "struct_declarator", "initializer",
  "declaration_statement", "statement", "simple_statement",
  "compound_statement", "@1", "@2", "statement_no_new_scope",
  "compound_statement_no_new_scope", "statement_list",
  "expression_statement", "selection_statement",
  "selection_rest_statement", "condition", "iteration_statement", "@3",
  "@4", "@5", "for_init_statement", "conditionopt", "for_rest_statement",
  "jump_statement", "translation_unit", "external_declaration",
  "function_definition", "@6", "initialization_list", "initializer_list",
  "annotation", "annotation_list", "annotation_item", "ann_type",
  "ann_literal", "ann_numerical_constant", "ann_literal_constructor",
  "ann_value_list", "ann_literal_init_list", "register_specifier",
  "semantic", "type_info", "sampler_initializer", "sampler_init_list",
  "sampler_init_item", 0
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   117,   118,   119,   119,   119,   119,   119,   120,   120,
     120,   120,   120,   120,   121,   122,   123,   123,   124,   124,
     125,   125,   126,   126,   127,   128,   128,   128,   129,   129,
     129,   129,   129,   130,   130,   130,   130,   131,   131,   131,
     131,   132,   132,   132,   133,   133,   133,   134,   134,   134,
     134,   134,   135,   135,   135,   136,   136,   137,   137,   138,
     138,   139,   139,   140,   140,   141,   141,   142,   142,   143,
     143,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   145,   145,   146,   147,   147,   148,   148,   149,
     149,   150,   150,   151,   152,   152,   152,   152,   152,   152,
     153,   153,   153,   153,   154,   154,   154,   154,   155,   156,
     156,   156,   156,   156,   156,   156,   157,   157,   157,   157,
     157,   157,   157,   158,   158,   159,   159,   159,   159,   159,
     159,   160,   160,   161,   161,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   162,   162,   163,
     163,   164,   165,   165,   166,   166,   166,   166,   167,   167,
     167,   168,   169,   169,   170,   170,   170,   170,   170,   171,
     172,   173,   171,   174,   174,   175,   175,   176,   176,   177,
     177,   178,   179,   179,   180,   180,   182,   181,   183,   181,
     184,   181,   185,   185,   186,   186,   187,   187,   188,   188,
     188,   188,   188,   189,   189,   190,   190,   190,   192,   191,
     193,   193,   194,   194,   194,   194,   195,   195,   196,   196,
     197,   198,   198,   198,   198,   198,   198,   198,   198,   198,
     198,   198,   198,   198,   198,   198,   198,   198,   198,   198,
     198,   198,   199,   199,   199,   199,   200,   200,   200,   201,
     202,   202,   203,   204,   205,   206,   206,   206,   206,   206,
     206,   206,   206,   207,   207,   208,   208,   209,   209,   209,
     209,   209,   209
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     3,     1,     4,
       1,     3,     2,     2,     1,     1,     1,     3,     2,     2,
       2,     1,     2,     3,     2,     1,     1,     1,     1,     2,
       2,     2,     4,     1,     1,     1,     1,     1,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     5,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     2,     2,     2,     4,     1,
       1,     2,     3,     3,     2,     4,     3,     4,     5,     7,
       3,     2,     3,     2,     0,     1,     1,     1,     1,     1,
       4,     6,     7,     8,     9,     6,     1,     3,     5,     6,
       7,     8,     5,     1,     2,     1,     1,     2,     1,     1,
       1,     1,     4,     1,     1,     1,     1,     1,     1,     6,
       6,     6,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     5,     4,     1,
       2,     3,     1,     3,     1,     3,     4,     6,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       0,     0,     5,     1,     1,     2,     3,     1,     2,     1,
       2,     5,     3,     1,     1,     4,     0,     6,     0,     8,
       0,     7,     1,     1,     1,     0,     2,     3,     2,     2,
       2,     3,     2,     1,     2,     1,     1,     1,     0,     3,
       3,     4,     1,     1,     3,     3,     2,     3,     1,     2,
       5,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     4,
       1,     3,     3,     5,     2,     0,     1,     1,     1,     2,
       2,     2,     3,     4,     3,     1,     2,     4,     6,     6,
       4,     6,     6
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,   128,   125,   126,   138,   134,   137,   136,   135,   151,
     152,   153,   154,   155,   156,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   130,   129,     0,   133,   168,   169,   170,
     171,   173,   174,   172,   167,     0,   166,   176,   237,   236,
     238,     0,    90,   104,     0,   109,   116,     0,   123,   131,
     175,     0,   233,   235,   127,     0,     0,     0,    85,     0,
      87,   104,   105,   106,   107,    91,     0,   104,     0,    86,
     285,   124,     0,     1,   234,     0,     0,     0,   179,     0,
       0,     0,     0,   239,     0,    92,   101,   103,   108,     0,
     285,    93,     0,     0,     0,   288,   287,   286,   117,     2,
       5,     4,     6,    27,     0,     0,     0,    35,    34,    36,
      33,     3,     8,    28,    10,    15,    16,     0,     0,    21,
       0,    37,     0,    41,    44,    47,    52,    55,    57,    59,
      61,    63,    65,    67,    84,     0,    25,     0,   184,     0,
     182,   178,   180,     0,     0,     0,     0,     0,   218,     0,
       0,     0,     0,     0,   200,   205,   209,    37,    69,    82,
       0,   191,     0,   123,   194,   207,   193,   192,     0,   195,
     196,   197,   198,    88,    94,   100,   102,     0,   110,   285,
       0,     0,   284,   255,   251,   254,   256,   253,   252,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   246,     0,   248,     0,   291,     0,
     289,   290,     0,    29,    30,     0,   131,    12,    13,     0,
       0,    19,    18,     0,   133,    22,    24,    31,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   132,   177,
       0,     0,     0,   181,     0,     0,     0,   229,   228,     0,
     220,     0,   232,   230,     0,   216,   199,     0,    72,    73,
      75,    74,    77,    78,    79,    80,    81,    76,    71,     0,
       0,   210,   206,   208,     0,     0,     0,    96,   285,     0,
       0,   118,   285,     0,   247,   249,     0,   292,     0,     0,
     188,   122,   189,   190,     7,     0,     0,    14,    26,    11,
      17,    23,    38,    39,    40,    43,    42,    45,    46,    50,
      51,    48,    49,    53,    54,    56,    58,    60,    62,    64,
      66,     0,     0,   185,   183,   141,   139,   140,     0,     0,
       0,   231,     0,   201,    70,    83,     0,    97,    95,   111,
     285,   115,     0,   119,     0,     0,     0,   242,   243,     0,
      32,     9,     0,   186,     0,   223,   222,   225,     0,   214,
       0,     0,     0,    98,     0,   112,   120,     0,   283,   278,
     276,   277,   273,     0,     0,     0,   272,   274,   275,     0,
       0,   294,     0,   295,   240,     0,    68,     0,     0,   224,
       0,     0,   213,   211,     0,     0,   202,     0,   113,     0,
     121,   280,     0,     0,   250,     0,     0,   293,   296,   241,
     244,   245,   187,     0,   226,     0,     0,     0,   204,   217,
     203,    99,   114,   282,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   227,   221,   212,   215,   281,   279,   300,
       0,     0,   297,     0,     0,   219,     0,     0,     0,     0,
     302,   301,   299,   298
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   121,   122,   123,   316,   124,   125,   126,   127,   128,
     129,   130,   167,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   168,   169,   289,   170,   145,
     171,   172,    51,    52,    53,    96,    75,    76,    97,    54,
      55,    56,    57,   146,    59,    60,    87,    88,   149,   150,
     311,   174,   175,   176,   177,   277,   382,   439,   440,   178,
     179,   180,   413,   381,   181,   352,   269,   349,   377,   410,
     411,   182,    61,    62,    63,    69,   312,   369,   105,   215,
     216,   217,   395,   421,   397,   422,   398,   106,   107,   108,
     313,   402,   403
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -394
static const yytype_int16 yypact[] =
{
    1848,  -394,  -394,    25,  -394,  -394,  -394,  -394,  -394,  -394,
    -394,  -394,  -394,  -394,  -394,  -394,  -394,  -394,  -394,  -394,
    -394,  -394,  -394,  -394,  -394,  -394,  -394,  -394,  -394,  -394,
    -394,  -394,  -394,  -394,  -394,   -46,  -394,  -394,  -394,  -394,
    -394,  -394,  -394,  -394,  -394,   -78,  -394,  -394,  -394,  -394,
     -29,    -8,    39,    23,    10,  -394,    46,  2185,  -394,    -5,
    -394,  1037,  -394,  -394,  -394,   101,  2185,   143,  -394,   104,
      51,    36,  -394,  -394,  -394,  -394,  2185,   113,   103,  -394,
      14,  -394,  1669,  -394,  -394,  2185,   138,  1932,  -394,   110,
     111,   112,   435,  -394,   148,  -394,  -394,  -394,   149,  2185,
     -51,  -394,  1311,    73,   274,  -394,   108,   -76,   114,   125,
    -394,  -394,  -394,  -394,  1669,  1669,  1669,  -394,  -394,  -394,
    -394,  -394,  -394,    28,  -394,  -394,  -394,   126,   -63,  1757,
     128,  -394,  1669,    56,    -7,   -10,   -56,    50,   109,   115,
     117,   142,   141,   -43,  -394,   129,  -394,  2011,   -42,    37,
    -394,  -394,  -394,   158,   159,   160,   130,   131,  -394,   139,
     145,   133,  1402,   146,   144,  -394,  -394,   105,  -394,  -394,
      41,  -394,   -29,   147,  -394,  -394,  -394,  -394,   540,  -394,
    -394,  -394,  -394,  -394,    17,  -394,  -394,  1490,   150,   -53,
     135,   151,  -394,  -394,  -394,  -394,  -394,  -394,  -394,  -394,
    -394,  -394,  -394,  -394,  -394,  -394,  -394,  -394,  -394,  -394,
    -394,  -394,  -394,  -394,  -394,   396,  -394,   176,  -394,   181,
    -394,   108,  1121,  -394,  -394,    -6,    66,  -394,  -394,  1669,
    2123,  -394,  -394,  1669,   152,  -394,  -394,  -394,  1669,  1669,
    1669,  1669,  1669,  1669,  1669,  1669,  1669,  1669,  1669,  1669,
    1669,  1669,  1669,  1669,  1669,  1669,  1669,  1669,  -394,  -394,
    1669,   182,   138,  -394,   136,   137,   153,  -394,  -394,   645,
    -394,  1669,  -394,  -394,    43,  -394,  -394,   645,  -394,  -394,
    -394,  -394,  -394,  -394,  -394,  -394,  -394,  -394,  -394,  1669,
    1669,  -394,  -394,  -394,  1669,    83,  1121,  -394,   -53,   154,
    1121,   156,   -53,   186,  -394,  -394,   157,  -394,   164,  1581,
    -394,  -394,  -394,  -394,  -394,  1669,   170,   155,  -394,   161,
    -394,  -394,  -394,  -394,  -394,    56,    56,    -7,    -7,   -10,
     -10,   -10,   -10,   -56,   -56,    50,   109,   115,   117,   142,
     141,    71,   171,  -394,  -394,  -394,  -394,  -394,   202,   855,
      22,  -394,   946,   645,  -394,  -394,   172,  -394,  -394,   168,
     -53,  -394,  1121,   169,   162,  2072,   -33,  -394,  -394,    55,
    -394,  -394,  1669,   173,   180,  -394,  -394,   946,   645,   155,
     210,   185,   178,   187,  1121,   184,  -394,  1121,  -394,  -394,
    -394,  -394,  -394,   107,   194,   188,  -394,  -394,  -394,   207,
     209,  -394,   -20,  -394,  -394,  1209,  -394,   224,  1669,  -394,
     211,   196,   297,  -394,   213,   750,  -394,   248,  -394,  1121,
    -394,  -394,    79,   107,  -394,   -57,   -47,  -394,  -394,  -394,
    -394,  -394,  -394,    26,  1669,   750,   645,  1121,  -394,  -394,
    -394,  -394,  -394,  -394,   107,    30,   214,   251,   253,   217,
     256,   257,   239,   155,  -394,  -394,  -394,  -394,  -394,  -394,
     249,   232,  -394,   252,   235,  -394,   245,   247,   254,   255,
    -394,  -394,  -394,  -394
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -394,  -394,  -394,  -394,  -394,  -394,  -394,   121,  -394,  -394,
    -394,  -394,    85,  -394,   -58,   -35,  -114,   -64,   116,   102,
     106,   118,   100,   119,  -394,   -79,  -127,  -394,  -115,   -90,
      11,    16,  -394,  -394,  -394,   261,   285,   284,   263,  -394,
    -394,  -328,   -19,     0,   250,  -394,   278,   -72,  -394,   120,
    -283,    15,  -173,  -393,  -394,  -394,  -394,   -70,   299,    92,
      21,  -394,  -394,    -4,  -394,  -394,  -394,  -394,  -394,  -394,
    -394,  -394,  -394,   310,  -394,  -394,  -300,  -394,  -100,  -394,
     165,     9,  -394,  -355,  -394,   -40,  -394,   -93,  -394,   -96,
    -394,  -394,   -26
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -90
static const yytype_int16 yytable[] =
{
      58,   225,   235,   144,   188,   293,   218,   220,   446,   368,
     396,    49,   190,   358,   221,   152,    50,   361,   449,    65,
     245,   246,   438,   144,   380,   219,     1,     2,     3,    64,
     399,   232,   400,    67,    77,   104,   447,   233,   256,     1,
       2,     3,   438,   399,   187,   400,   450,   274,   103,   380,
     103,    66,    77,   260,   448,   247,   248,    81,   104,   261,
     104,    58,   243,   244,   451,   401,    86,    72,    73,    74,
      33,    34,    49,   257,    68,   152,    98,    50,   427,   386,
      72,    73,    74,    33,    34,    86,    70,    86,   314,   457,
      82,   297,   173,   301,   290,   310,   348,   299,   241,    98,
     242,   418,   227,   228,   420,   431,   321,   101,   144,   102,
      78,    80,   294,    79,   317,   103,   378,   -89,   295,   296,
     452,   307,   290,   229,   458,   104,   290,   230,   249,   250,
     444,   329,   330,   331,   332,   191,   442,   262,   192,    71,
     263,   290,   341,   290,   291,   191,   351,    86,   357,    89,
      90,    91,    94,   404,   456,   405,   350,    72,    73,    74,
     315,    82,   354,   355,   238,   239,   240,   131,   100,   310,
     342,   290,   372,   310,   389,   390,   391,   443,   173,   444,
     293,   144,   367,   325,   326,   333,   334,   131,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,    85,   223,
     224,    92,   359,   148,   356,   412,   363,   288,   327,   328,
     153,   154,   155,   183,   184,   144,   222,   237,   -26,   104,
     231,   236,   254,   255,   251,   258,   264,   265,   266,   252,
     253,   302,   270,   267,   268,   310,   272,   379,   271,   275,
     -25,   306,   276,   191,   303,   406,   -20,   343,   345,   346,
     360,   364,   300,   374,   -27,   290,   388,   310,   362,   365,
     310,   366,   379,   455,   385,   347,   371,   373,   383,   173,
     384,   387,   131,   408,   407,   414,   416,   173,   430,   415,
     193,   194,   195,   196,   197,   198,   419,   423,   417,   432,
     435,   424,   310,   433,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   425,
     310,   426,   436,   441,   434,   437,   460,   459,   461,   453,
     462,   463,   464,   322,   323,   324,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   465,   466,   467,   131,   468,   469,   470,   173,
     471,   320,   173,   173,   336,   339,    95,   472,   473,   337,
     185,    99,   186,   147,   375,   454,   226,   335,    93,   353,
     376,    84,   338,   409,   394,   340,   428,   173,   173,   131,
     305,     0,   344,   445,     0,     0,   214,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     370,     0,   193,   194,   195,   196,   197,   198,     0,     0,
       0,     0,     0,     0,     0,   173,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,     0,     0,     0,     0,   173,   173,     0,     1,     2,
       3,     4,     5,     6,     0,     7,     8,   156,   157,   158,
       0,   159,   160,   161,   162,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,     0,
       0,     0,    33,    34,    35,    36,   163,    37,    38,    39,
      40,    41,    42,    43,    44,    45,     0,     0,    46,     0,
     109,    47,   110,   111,   112,     0,   113,     0,   304,   114,
     115,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   116,     0,
       0,     0,   164,   165,     0,     0,     0,     0,   166,   117,
     118,   119,   120,     1,     2,     3,     4,     5,     6,     0,
       7,     8,   156,   157,   158,     0,   159,   160,   161,   162,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,     0,     0,     0,    33,    34,    35,
      36,   163,    37,    38,    39,    40,    41,    42,    43,    44,
      45,     0,     0,    46,     0,   109,    47,   110,   111,   112,
       0,   113,     0,     0,   114,   115,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   116,     0,     0,     0,   164,   292,     0,
       0,     0,     0,   166,   117,   118,   119,   120,     1,     2,
       3,     4,     5,     6,     0,     7,     8,   156,   157,   158,
       0,   159,   160,   161,   162,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,     0,
       0,     0,    33,    34,    35,    36,   163,    37,    38,    39,
      40,    41,    42,    43,    44,    45,     0,     0,    46,     0,
     109,    47,   110,   111,   112,     0,   113,     0,     0,   114,
     115,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   116,     0,
       0,     0,   164,     0,     0,     0,     0,     0,   166,   117,
     118,   119,   120,     1,     2,     3,     4,     5,     6,     0,
       7,     8,   156,   157,   158,     0,   159,   160,   161,   162,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,     0,     0,     0,    33,    34,    35,
      36,   163,    37,    38,    39,    40,    41,    42,    43,    44,
      45,     0,     0,    46,     0,   109,    47,   110,   111,   112,
       0,   113,     0,     0,   114,   115,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   116,     0,     0,     0,    92,     0,     0,
       0,     0,     0,   166,   117,   118,   119,   120,     1,     2,
       3,     4,     5,     6,     0,     7,     8,     0,     0,     0,
       0,     0,     0,     0,     0,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,     0,
       0,     0,    33,    34,    35,    36,     0,    37,    38,    39,
      40,    41,    42,    43,    44,    45,     0,     0,    46,     0,
     109,    47,   110,   111,   112,     0,   113,     0,     0,   114,
     115,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   116,     1,
       2,     3,     4,     5,     6,     0,     7,     8,   166,   117,
     118,   119,   120,     0,     0,     0,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
       0,     0,     0,    33,    34,    35,    36,     0,    37,    38,
      39,    40,    41,    42,    43,    44,    45,     0,     0,    46,
       0,   109,    47,   110,   111,   112,     0,   113,     0,     0,
     114,   115,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    83,     0,   116,
       1,     2,     3,     4,     5,     6,     0,     7,     8,     0,
     117,   118,   119,   120,     0,     0,     0,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,     0,     0,     0,    33,    34,    35,    36,     0,    37,
      38,    39,    40,    41,    42,    43,    44,    45,     0,     0,
      46,     0,     0,    47,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     4,     5,     6,
       0,     7,     8,     0,     0,     0,     0,     0,     0,     0,
      48,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,     0,     0,     0,     0,     0,
      35,    36,     0,    37,    38,    39,    40,    41,    42,    43,
      44,    45,     0,     0,    46,   308,   109,    47,   110,   111,
     112,     0,   113,     0,     0,   114,   115,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   116,     4,     5,     6,   309,     7,
       8,     0,     0,     0,     0,   117,   118,   119,   120,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,     0,     0,     0,     0,     0,    35,    36,
       0,    37,    38,    39,    40,    41,    42,    43,    44,    45,
       0,     0,    46,     0,   109,    47,   110,   111,   112,     0,
     113,     0,     0,   114,   115,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   116,     0,     0,     0,   309,   429,     0,     0,
       0,     0,     0,   117,   118,   119,   120,     4,     5,     6,
       0,     7,     8,     0,     0,     0,     0,     0,     0,     0,
       0,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,     0,     0,     0,     0,     0,
      35,    36,     0,    37,    38,    39,    40,    41,    42,    43,
      44,    45,     0,     0,    46,     0,   109,    47,   110,   111,
     112,     0,   113,     0,     0,   114,   115,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   116,     0,     0,   189,     4,     5,
       6,     0,     7,     8,     0,   117,   118,   119,   120,     0,
       0,     0,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,     0,     0,     0,     0,
       0,    35,    36,     0,    37,    38,    39,    40,    41,    42,
      43,    44,    45,     0,     0,    46,     0,   109,    47,   110,
     111,   112,     0,   113,     0,     0,   114,   115,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   116,     4,     5,     6,     0,
       7,     8,     0,     0,     0,   273,   117,   118,   119,   120,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,     0,     0,     0,     0,     0,    35,
      36,     0,    37,    38,    39,    40,    41,    42,    43,    44,
      45,     0,     0,    46,     0,   109,    47,   110,   111,   112,
       0,   113,     0,     0,   114,   115,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   116,     0,     0,   298,     4,     5,     6,
       0,     7,     8,     0,   117,   118,   119,   120,     0,     0,
       0,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,     0,     0,     0,     0,     0,
      35,    36,     0,    37,    38,    39,    40,    41,    42,    43,
      44,    45,     0,     0,    46,     0,   109,    47,   110,   111,
     112,     0,   113,     0,     0,   114,   115,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   116,     4,     5,     6,   309,     7,
       8,     0,     0,     0,     0,   117,   118,   119,   120,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,     0,     0,     0,     0,     0,    35,    36,
       0,    37,    38,    39,    40,    41,    42,    43,    44,    45,
       0,     0,    46,     0,   109,    47,   110,   111,   112,     0,
     113,     0,     0,   114,   115,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   116,     4,     5,     6,     0,     7,     8,     0,
       0,     0,     0,   117,   118,   119,   120,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,     0,     0,     0,     0,     0,    35,   234,     0,    37,
      38,    39,    40,    41,    42,    43,    44,    45,     0,     0,
      46,     0,   109,    47,   110,   111,   112,     0,   113,     0,
       0,   114,   115,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     116,     1,     2,     3,     4,     5,     6,     0,     7,     8,
       0,   117,   118,   119,   120,     0,     0,     0,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,     0,     0,     0,    33,    34,    35,    36,     0,
      37,    38,    39,    40,    41,    42,    43,    44,    45,     0,
       0,    46,     0,     0,    47,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     4,     5,
       6,     0,     7,     8,     0,     0,     0,     0,     0,     0,
       0,    48,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,     0,     0,     0,     0,
       0,    35,    36,     0,    37,    38,    39,    40,    41,    42,
      43,    44,    45,     0,     0,    46,     0,     0,    47,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     4,     5,     6,
       0,     7,     8,     0,     0,     0,     0,     0,     0,     0,
     151,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,     0,     0,     0,     0,     0,
      35,    36,     0,    37,    38,    39,    40,    41,    42,    43,
      44,    45,     0,     0,    46,     0,     0,    47,   193,   194,
     195,   196,   197,   198,     0,     0,     0,     0,     0,     0,
       0,     0,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,     0,     0,   259,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     4,
       5,     6,     0,     7,     8,     0,     0,     0,     0,   389,
     390,   391,   392,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,     0,     0,   393,
       0,     0,    35,    36,     0,    37,    38,    39,    40,    41,
      42,    43,    44,    45,     0,     0,    46,     0,   318,    47,
       0,     4,     5,     6,   319,     7,     8,     0,     0,     0,
       0,     0,     0,     0,     0,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,     0,
       0,     0,     0,     0,    35,    36,     0,    37,    38,    39,
      40,    41,    42,    43,    44,    45,     0,     0,    46,     0,
       0,    47
};

static const yytype_int16 yycheck[] =
{
       0,   116,   129,    82,   100,   178,   106,   107,    65,   309,
     365,     0,   102,   296,   107,    87,     0,   300,    65,    65,
      76,    77,   415,   102,   352,   101,     3,     4,     5,     4,
      63,    94,    65,   111,    53,   111,    93,   100,    81,     3,
       4,     5,   435,    63,    95,    65,    93,   162,   101,   377,
     101,    97,    71,    95,   111,   111,   112,    57,   111,   101,
     111,    61,    72,    73,   111,    98,    66,    44,    45,    46,
      47,    48,    61,   116,   103,   147,    76,    61,    98,   362,
      44,    45,    46,    47,    48,    85,    94,    87,    94,   444,
      95,   184,    92,   189,   100,   222,   269,   187,   105,    99,
     107,   384,    74,    75,   387,   405,   233,    93,   187,    95,
     100,    65,    95,   103,   229,   101,    94,    94,   101,   102,
      94,   221,   100,    95,    94,   111,   100,    99,    78,    79,
     100,   245,   246,   247,   248,    62,   419,   100,    65,   100,
     103,   100,   257,   100,   103,    62,   103,   147,    65,     6,
       7,     8,   101,    98,   437,   100,   271,    44,    45,    46,
      94,    95,   289,   290,   108,   109,   110,    82,    65,   296,
     260,   100,   101,   300,    67,    68,    69,    98,   178,   100,
     353,   260,   309,   241,   242,   249,   250,   102,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    97,   114,
     115,    97,   298,    65,   294,   378,   302,   102,   243,   244,
     100,   100,   100,    65,    65,   294,   102,   132,    93,   111,
      94,    93,    80,    82,   115,    96,    68,    68,    68,   114,
     113,    96,    93,   103,   103,   362,   103,   352,    93,    93,
      93,    65,    98,    62,    93,   372,    94,    65,   112,   112,
      96,    65,   102,    51,    93,   100,    94,   384,   102,   102,
     387,    97,   377,   436,   360,   112,    96,    96,    96,   269,
     102,   102,   187,    93,   101,    65,    98,   277,   405,    94,
       6,     7,     8,     9,    10,    11,   102,    93,   101,    65,
      94,   103,   419,   408,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,   102,
     437,   102,    15,    65,   103,   102,    65,   103,    65,   434,
     103,    65,    65,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   103,    94,   112,   260,    94,   112,   103,   349,
     103,   230,   352,   353,   252,   255,    71,   103,   103,   253,
      99,    77,    99,    85,   349,   435,   116,   251,    69,   277,
     349,    61,   254,   377,   365,   256,   402,   377,   378,   294,
     215,    -1,   262,   423,    -1,    -1,   112,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     315,    -1,     6,     7,     8,     9,    10,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   415,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,   435,   436,    -1,     3,     4,
       5,     6,     7,     8,    -1,    10,    11,    12,    13,    14,
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    -1,
      -1,    -1,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    -1,    -1,    63,    -1,
      65,    66,    67,    68,    69,    -1,    71,    -1,   112,    74,
      75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,    -1,
      -1,    -1,    97,    98,    -1,    -1,    -1,    -1,   103,   104,
     105,   106,   107,     3,     4,     5,     6,     7,     8,    -1,
      10,    11,    12,    13,    14,    -1,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    -1,    -1,    -1,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    -1,    63,    -1,    65,    66,    67,    68,    69,
      -1,    71,    -1,    -1,    74,    75,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    93,    -1,    -1,    -1,    97,    98,    -1,
      -1,    -1,    -1,   103,   104,   105,   106,   107,     3,     4,
       5,     6,     7,     8,    -1,    10,    11,    12,    13,    14,
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    -1,
      -1,    -1,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    -1,    -1,    63,    -1,
      65,    66,    67,    68,    69,    -1,    71,    -1,    -1,    74,
      75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,    -1,
      -1,    -1,    97,    -1,    -1,    -1,    -1,    -1,   103,   104,
     105,   106,   107,     3,     4,     5,     6,     7,     8,    -1,
      10,    11,    12,    13,    14,    -1,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    -1,    -1,    -1,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    -1,    63,    -1,    65,    66,    67,    68,    69,
      -1,    71,    -1,    -1,    74,    75,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    93,    -1,    -1,    -1,    97,    -1,    -1,
      -1,    -1,    -1,   103,   104,   105,   106,   107,     3,     4,
       5,     6,     7,     8,    -1,    10,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    -1,
      -1,    -1,    47,    48,    49,    50,    -1,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    -1,    -1,    63,    -1,
      65,    66,    67,    68,    69,    -1,    71,    -1,    -1,    74,
      75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,     3,
       4,     5,     6,     7,     8,    -1,    10,    11,   103,   104,
     105,   106,   107,    -1,    -1,    -1,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      -1,    -1,    -1,    47,    48,    49,    50,    -1,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    -1,    -1,    63,
      -1,    65,    66,    67,    68,    69,    -1,    71,    -1,    -1,
      74,    75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     0,    -1,    93,
       3,     4,     5,     6,     7,     8,    -1,    10,    11,    -1,
     104,   105,   106,   107,    -1,    -1,    -1,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    -1,    -1,    -1,    47,    48,    49,    50,    -1,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    -1,    -1,
      63,    -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,     7,     8,
      -1,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     103,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      49,    50,    -1,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    -1,    63,    64,    65,    66,    67,    68,
      69,    -1,    71,    -1,    -1,    74,    75,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    93,     6,     7,     8,    97,    10,
      11,    -1,    -1,    -1,    -1,   104,   105,   106,   107,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    -1,    -1,    -1,    -1,    -1,    49,    50,
      -1,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      -1,    -1,    63,    -1,    65,    66,    67,    68,    69,    -1,
      71,    -1,    -1,    74,    75,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    93,    -1,    -1,    -1,    97,    98,    -1,    -1,
      -1,    -1,    -1,   104,   105,   106,   107,     6,     7,     8,
      -1,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      49,    50,    -1,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    -1,    63,    -1,    65,    66,    67,    68,
      69,    -1,    71,    -1,    -1,    74,    75,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    93,    -1,    -1,    96,     6,     7,
       8,    -1,    10,    11,    -1,   104,   105,   106,   107,    -1,
      -1,    -1,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    49,    50,    -1,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    -1,    -1,    63,    -1,    65,    66,    67,
      68,    69,    -1,    71,    -1,    -1,    74,    75,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    93,     6,     7,     8,    -1,
      10,    11,    -1,    -1,    -1,   103,   104,   105,   106,   107,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,    49,
      50,    -1,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    -1,    63,    -1,    65,    66,    67,    68,    69,
      -1,    71,    -1,    -1,    74,    75,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    93,    -1,    -1,    96,     6,     7,     8,
      -1,    10,    11,    -1,   104,   105,   106,   107,    -1,    -1,
      -1,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      49,    50,    -1,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    -1,    63,    -1,    65,    66,    67,    68,
      69,    -1,    71,    -1,    -1,    74,    75,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    93,     6,     7,     8,    97,    10,
      11,    -1,    -1,    -1,    -1,   104,   105,   106,   107,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    -1,    -1,    -1,    -1,    -1,    49,    50,
      -1,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      -1,    -1,    63,    -1,    65,    66,    67,    68,    69,    -1,
      71,    -1,    -1,    74,    75,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    93,     6,     7,     8,    -1,    10,    11,    -1,
      -1,    -1,    -1,   104,   105,   106,   107,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    49,    50,    -1,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    -1,    -1,
      63,    -1,    65,    66,    67,    68,    69,    -1,    71,    -1,
      -1,    74,    75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      93,     3,     4,     5,     6,     7,     8,    -1,    10,    11,
      -1,   104,   105,   106,   107,    -1,    -1,    -1,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    -1,    -1,    -1,    47,    48,    49,    50,    -1,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    -1,
      -1,    63,    -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,     7,
       8,    -1,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   103,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    49,    50,    -1,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,     7,     8,
      -1,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      98,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      49,    50,    -1,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    -1,    63,    -1,    -1,    66,     6,     7,
       8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    -1,    -1,    98,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,
       7,     8,    -1,    10,    11,    -1,    -1,    -1,    -1,    67,
      68,    69,    70,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    -1,    -1,    97,
      -1,    -1,    49,    50,    -1,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    -1,    -1,    63,    -1,    65,    66,
      -1,     6,     7,     8,    71,    10,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    49,    50,    -1,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    -1,    -1,    63,    -1,
      -1,    66
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,    10,    11,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    47,    48,    49,    50,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    63,    66,   103,   147,
     148,   149,   150,   151,   156,   157,   158,   159,   160,   161,
     162,   189,   190,   191,     4,    65,    97,   111,   103,   192,
      94,   100,    44,    45,    46,   153,   154,   159,   100,   103,
      65,   160,    95,     0,   190,    97,   160,   163,   164,     6,
       7,     8,    97,   175,   101,   153,   152,   155,   160,   154,
      65,    93,    95,   101,   111,   195,   204,   205,   206,    65,
      67,    68,    69,    71,    74,    75,    93,   104,   105,   106,
     107,   118,   119,   120,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   146,   160,   163,    65,   165,
     166,    98,   164,   100,   100,   100,    12,    13,    14,    16,
      17,    18,    19,    51,    97,    98,   103,   129,   142,   143,
     145,   147,   148,   160,   168,   169,   170,   171,   176,   177,
     178,   181,   188,    65,    65,   152,   155,    95,   206,    96,
     146,    62,    65,     6,     7,     8,     9,    10,    11,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,   112,   196,   197,   198,   195,   101,
     195,   204,   102,   129,   129,   145,   161,    74,    75,    95,
      99,    94,    94,   100,    50,   143,    93,   129,   108,   109,
     110,   105,   107,    72,    73,    76,    77,   111,   112,    78,
      79,   115,   114,   113,    80,    82,    81,   116,    96,    98,
      95,   101,   100,   103,    68,    68,    68,   103,   103,   183,
      93,    93,   103,   103,   145,    93,    98,   172,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,   102,   144,
     100,   103,    98,   169,    95,   101,   102,   204,    96,   146,
     102,   206,    96,    93,   112,   197,    65,   195,    64,    97,
     143,   167,   193,   207,    94,    94,   121,   145,    65,    71,
     124,   143,   129,   129,   129,   131,   131,   132,   132,   133,
     133,   133,   133,   134,   134,   135,   136,   137,   138,   139,
     140,   145,   146,    65,   166,   112,   112,   112,   169,   184,
     145,   103,   182,   176,   143,   143,   146,    65,   167,   206,
      96,   167,   102,   206,    65,   102,    97,   143,   193,   194,
     129,    96,   101,    96,    51,   168,   177,   185,    94,   145,
     158,   180,   173,    96,   102,   206,   167,   102,    94,    67,
      68,    69,    70,    97,   198,   199,   200,   201,   203,    63,
      65,    98,   208,   209,    98,   100,   143,   101,    93,   180,
     186,   187,   169,   179,    65,    94,    98,   101,   167,   102,
     167,   200,   202,    93,   103,   102,   102,    98,   209,    98,
     143,   193,    65,   145,   103,    94,    15,   102,   170,   174,
     175,    65,   167,    98,   100,   202,    65,    93,   111,    65,
      93,   111,    94,   145,   174,   169,   167,   200,    94,   103,
      65,    65,   103,    65,    65,   103,    94,   112,    94,   112,
     103,   103,   103,   103
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
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
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
  /* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;

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
#line 190 "hlslang.y"
    {
        // The symbol table search was done in the lexical phase
        const TSymbol* symbol = (yyvsp[(1) - (1)].lex).symbol;
        const TVariable* variable;
        if (symbol == 0) {
            parseContext.error((yyvsp[(1) - (1)].lex).line, "undeclared identifier", (yyvsp[(1) - (1)].lex).string->c_str(), "");
            parseContext.recover();
            TType type(EbtFloat, EbpUndefined);
            TVariable* fakeVariable = new TVariable((yyvsp[(1) - (1)].lex).string, type);
            parseContext.symbolTable.insert(*fakeVariable);
            variable = fakeVariable;
        } else {
            // This identifier can only be a variable type symbol 
            if (! symbol->isVariable()) {
                parseContext.error((yyvsp[(1) - (1)].lex).line, "variable expected", (yyvsp[(1) - (1)].lex).string->c_str(), "");
                parseContext.recover();
            }
            variable = static_cast<const TVariable*>(symbol);
        }

        // don't delete $1.string, it's used by error recovery, and the pool
        // pop will reclaim the memory

        if (variable->getType().getQualifier() == EvqConst ) {
            constUnion* constArray = variable->getConstPointer();
            TType t(variable->getType());
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(constArray, t, (yyvsp[(1) - (1)].lex).line);        
        } else
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addSymbol(variable->getUniqueId(), 
                                                     variable->getName(),
                                                     variable->getInfo(), 
                                                     variable->getType(), (yyvsp[(1) - (1)].lex).line);
    ;}
    break;

  case 3:
#line 226 "hlslang.y"
    {
        (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode);
    ;}
    break;

  case 4:
#line 229 "hlslang.y"
    {        
        constUnion *unionArray = new constUnion[1];
        unionArray->setIConst((yyvsp[(1) - (1)].lex).i);
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtInt, EbpUndefined, EvqConst), (yyvsp[(1) - (1)].lex).line);
    ;}
    break;

  case 5:
#line 234 "hlslang.y"
    {
        constUnion *unionArray = new constUnion[1];
        unionArray->setFConst((yyvsp[(1) - (1)].lex).f);
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtFloat, EbpUndefined, EvqConst), (yyvsp[(1) - (1)].lex).line);
    ;}
    break;

  case 6:
#line 239 "hlslang.y"
    {
        constUnion *unionArray = new constUnion[1];
        unionArray->setBConst((yyvsp[(1) - (1)].lex).b);
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtBool, EbpUndefined, EvqConst), (yyvsp[(1) - (1)].lex).line);
    ;}
    break;

  case 7:
#line 244 "hlslang.y"
    {
        (yyval.interm.intermTypedNode) = (yyvsp[(2) - (3)].interm.intermTypedNode);
    ;}
    break;

  case 8:
#line 250 "hlslang.y"
    { 
        (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode);
    ;}
    break;

  case 9:
#line 253 "hlslang.y"
    {
        if (!(yyvsp[(1) - (4)].interm.intermTypedNode)) {
            parseContext.error((yyvsp[(2) - (4)].lex).line, " left of '[' is null ", "expression", "");
            YYERROR;
        }
        if (!(yyvsp[(1) - (4)].interm.intermTypedNode)->isArray() && !(yyvsp[(1) - (4)].interm.intermTypedNode)->isMatrix() && !(yyvsp[(1) - (4)].interm.intermTypedNode)->isVector()) {
            if ((yyvsp[(1) - (4)].interm.intermTypedNode)->getAsSymbolNode())
                parseContext.error((yyvsp[(2) - (4)].lex).line, " left of '[' is not of type array, matrix, or vector ", (yyvsp[(1) - (4)].interm.intermTypedNode)->getAsSymbolNode()->getSymbol().c_str(), "");
            else
                parseContext.error((yyvsp[(2) - (4)].lex).line, " left of '[' is not of type array, matrix, or vector ", "expression", "");
            parseContext.recover();
        }
        if ((yyvsp[(1) - (4)].interm.intermTypedNode)->getType().getQualifier() == EvqConst && (yyvsp[(3) - (4)].interm.intermTypedNode)->getQualifier() == EvqConst) {
            if ((yyvsp[(1) - (4)].interm.intermTypedNode)->isArray()) { // constant folding for arrays
                (yyval.interm.intermTypedNode) = parseContext.addConstArrayNode((yyvsp[(3) - (4)].interm.intermTypedNode)->getAsConstantUnion()->getUnionArrayPointer()->getIConst(), (yyvsp[(1) - (4)].interm.intermTypedNode), (yyvsp[(2) - (4)].lex).line);
            } else if ((yyvsp[(1) - (4)].interm.intermTypedNode)->isVector()) {  // constant folding for vectors
                TVectorFields fields;                
                fields.num = 1;
                fields.offsets[0] = (yyvsp[(3) - (4)].interm.intermTypedNode)->getAsConstantUnion()->getUnionArrayPointer()->getIConst(); // need to do it this way because v.xy sends fields integer array
                (yyval.interm.intermTypedNode) = parseContext.addConstVectorNode(fields, (yyvsp[(1) - (4)].interm.intermTypedNode), (yyvsp[(2) - (4)].lex).line);
            } else if ((yyvsp[(1) - (4)].interm.intermTypedNode)->isMatrix()) { // constant folding for matrices
                (yyval.interm.intermTypedNode) = parseContext.addConstMatrixNode((yyvsp[(3) - (4)].interm.intermTypedNode)->getAsConstantUnion()->getUnionArrayPointer()->getIConst(), (yyvsp[(1) - (4)].interm.intermTypedNode), (yyvsp[(2) - (4)].lex).line);
            } 
        } else {
            if ((yyvsp[(3) - (4)].interm.intermTypedNode)->getQualifier() == EvqConst) {
                if (((yyvsp[(1) - (4)].interm.intermTypedNode)->isVector() || (yyvsp[(1) - (4)].interm.intermTypedNode)->isMatrix()) && (yyvsp[(1) - (4)].interm.intermTypedNode)->getType().getNominalSize() <= (yyvsp[(3) - (4)].interm.intermTypedNode)->getAsConstantUnion()->getUnionArrayPointer()->getIConst() && !(yyvsp[(1) - (4)].interm.intermTypedNode)->isArray() ) {
                    parseContext.error((yyvsp[(2) - (4)].lex).line, "", "[", "field selection out of range '%d'", (yyvsp[(3) - (4)].interm.intermTypedNode)->getAsConstantUnion()->getUnionArrayPointer()->getIConst());
                    parseContext.recover();
                } else {
                    if ((yyvsp[(1) - (4)].interm.intermTypedNode)->isArray()) {
                        if ((yyvsp[(1) - (4)].interm.intermTypedNode)->getType().getArraySize() == 0) {
                            if ((yyvsp[(1) - (4)].interm.intermTypedNode)->getType().getMaxArraySize() <= (yyvsp[(3) - (4)].interm.intermTypedNode)->getAsConstantUnion()->getUnionArrayPointer()->getIConst()) {
                                if (parseContext.arraySetMaxSize((yyvsp[(1) - (4)].interm.intermTypedNode)->getAsSymbolNode(), (yyvsp[(1) - (4)].interm.intermTypedNode)->getTypePointer(), (yyvsp[(3) - (4)].interm.intermTypedNode)->getAsConstantUnion()->getUnionArrayPointer()->getIConst(), true, (yyvsp[(2) - (4)].lex).line))
                                    parseContext.recover(); 
                            } else {
                                if (parseContext.arraySetMaxSize((yyvsp[(1) - (4)].interm.intermTypedNode)->getAsSymbolNode(), (yyvsp[(1) - (4)].interm.intermTypedNode)->getTypePointer(), 0, false, (yyvsp[(2) - (4)].lex).line))
                                    parseContext.recover(); 
                            }
                        } else if ( (yyvsp[(3) - (4)].interm.intermTypedNode)->getAsConstantUnion()->getUnionArrayPointer()->getIConst() >= (yyvsp[(1) - (4)].interm.intermTypedNode)->getType().getArraySize()) {
                            parseContext.error((yyvsp[(2) - (4)].lex).line, "", "[", "array index out of range '%d'", (yyvsp[(3) - (4)].interm.intermTypedNode)->getAsConstantUnion()->getUnionArrayPointer()->getIConst());
                            parseContext.recover();
                        }
                    }
                    (yyval.interm.intermTypedNode) = parseContext.intermediate.addIndex(EOpIndexDirect, (yyvsp[(1) - (4)].interm.intermTypedNode), (yyvsp[(3) - (4)].interm.intermTypedNode), (yyvsp[(2) - (4)].lex).line);
                }
            } else {
                if ((yyvsp[(1) - (4)].interm.intermTypedNode)->isArray() && (yyvsp[(1) - (4)].interm.intermTypedNode)->getType().getArraySize() == 0) {
                    parseContext.error((yyvsp[(2) - (4)].lex).line, "", "[", "array must be redeclared with a size before being indexed with a variable");
                    parseContext.recover();
                }
                
                (yyval.interm.intermTypedNode) = parseContext.intermediate.addIndex(EOpIndexIndirect, (yyvsp[(1) - (4)].interm.intermTypedNode), (yyvsp[(3) - (4)].interm.intermTypedNode), (yyvsp[(2) - (4)].lex).line);
            }
        } 
        if ((yyval.interm.intermTypedNode) == 0) {
            constUnion *unionArray = new constUnion[1];
            unionArray->setFConst(0.0f);
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtFloat, EbpUndefined, EvqConst), (yyvsp[(2) - (4)].lex).line);
        } else if ((yyvsp[(1) - (4)].interm.intermTypedNode)->isArray()) {
            if ((yyvsp[(1) - (4)].interm.intermTypedNode)->getType().getStruct())
                (yyval.interm.intermTypedNode)->setType(TType((yyvsp[(1) - (4)].interm.intermTypedNode)->getType().getStruct(), (yyvsp[(1) - (4)].interm.intermTypedNode)->getType().getTypeName(), EbpUndefined, (yyvsp[(1) - (4)].interm.intermTypedNode)->getLine()));
            else
                (yyval.interm.intermTypedNode)->setType(TType((yyvsp[(1) - (4)].interm.intermTypedNode)->getBasicType(), (yyvsp[(1) - (4)].interm.intermTypedNode)->getPrecision(), EvqTemporary, (yyvsp[(1) - (4)].interm.intermTypedNode)->getNominalSize(), (yyvsp[(1) - (4)].interm.intermTypedNode)->isMatrix()));
                
            if ((yyvsp[(1) - (4)].interm.intermTypedNode)->getType().getQualifier() == EvqConst)
                (yyval.interm.intermTypedNode)->getTypePointer()->changeQualifier(EvqConst);
        } else if ((yyvsp[(1) - (4)].interm.intermTypedNode)->isMatrix() && (yyvsp[(1) - (4)].interm.intermTypedNode)->getType().getQualifier() == EvqConst)         
            (yyval.interm.intermTypedNode)->setType(TType((yyvsp[(1) - (4)].interm.intermTypedNode)->getBasicType(), (yyvsp[(1) - (4)].interm.intermTypedNode)->getPrecision(), EvqConst, (yyvsp[(1) - (4)].interm.intermTypedNode)->getNominalSize()));     
        else if ((yyvsp[(1) - (4)].interm.intermTypedNode)->isMatrix())            
            (yyval.interm.intermTypedNode)->setType(TType((yyvsp[(1) - (4)].interm.intermTypedNode)->getBasicType(), (yyvsp[(1) - (4)].interm.intermTypedNode)->getPrecision(), EvqTemporary, (yyvsp[(1) - (4)].interm.intermTypedNode)->getNominalSize()));     
        else if ((yyvsp[(1) - (4)].interm.intermTypedNode)->isVector() && (yyvsp[(1) - (4)].interm.intermTypedNode)->getType().getQualifier() == EvqConst)          
            (yyval.interm.intermTypedNode)->setType(TType((yyvsp[(1) - (4)].interm.intermTypedNode)->getBasicType(), (yyvsp[(1) - (4)].interm.intermTypedNode)->getPrecision(), EvqConst));
        else if ((yyvsp[(1) - (4)].interm.intermTypedNode)->isVector())       
            (yyval.interm.intermTypedNode)->setType(TType((yyvsp[(1) - (4)].interm.intermTypedNode)->getBasicType(), (yyvsp[(1) - (4)].interm.intermTypedNode)->getPrecision(), EvqTemporary));
        else
            (yyval.interm.intermTypedNode)->setType((yyvsp[(1) - (4)].interm.intermTypedNode)->getType()); 
    ;}
    break;

  case 10:
#line 330 "hlslang.y"
    {
        (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode);
    ;}
    break;

  case 11:
#line 333 "hlslang.y"
    {      
		if (!(yyvsp[(1) - (3)].interm.intermTypedNode)) {
            parseContext.error((yyvsp[(3) - (3)].lex).line, "field selection on null object", ".", "");
            YYERROR;
		}  
        if ((yyvsp[(1) - (3)].interm.intermTypedNode)->isArray()) {
            parseContext.error((yyvsp[(3) - (3)].lex).line, "cannot apply dot operator to an array", ".", "");
            parseContext.recover();
        }

        if ((yyvsp[(1) - (3)].interm.intermTypedNode)->isVector()) {
            TVectorFields fields;
            if (! parseContext.parseVectorFields(*(yyvsp[(3) - (3)].lex).string, (yyvsp[(1) - (3)].interm.intermTypedNode)->getNominalSize(), fields, (yyvsp[(3) - (3)].lex).line)) {
                fields.num = 1;
                fields.offsets[0] = 0;
                parseContext.recover();
            }

            if ((yyvsp[(1) - (3)].interm.intermTypedNode)->getType().getQualifier() == EvqConst) { // constant folding for vector fields
                (yyval.interm.intermTypedNode) = parseContext.addConstVectorNode(fields, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].lex).line);
                if ((yyval.interm.intermTypedNode) == 0) {
                    parseContext.recover();
                    (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
                }
                else
                    (yyval.interm.intermTypedNode)->setType(TType((yyvsp[(1) - (3)].interm.intermTypedNode)->getBasicType(), (yyvsp[(1) - (3)].interm.intermTypedNode)->getPrecision(), EvqConst, (int) (*(yyvsp[(3) - (3)].lex).string).size()));
            } else {
                if (fields.num == 1) {
                    constUnion *unionArray = new constUnion[1];
                    unionArray->setIConst(fields.offsets[0]);
                    TIntermTyped* index = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtInt, EbpUndefined, EvqConst), (yyvsp[(3) - (3)].lex).line);
                    (yyval.interm.intermTypedNode) = parseContext.intermediate.addIndex(EOpIndexDirect, (yyvsp[(1) - (3)].interm.intermTypedNode), index, (yyvsp[(2) - (3)].lex).line);
                    (yyval.interm.intermTypedNode)->setType(TType((yyvsp[(1) - (3)].interm.intermTypedNode)->getBasicType(), (yyvsp[(1) - (3)].interm.intermTypedNode)->getPrecision()));
                } else {
                    TString vectorString = *(yyvsp[(3) - (3)].lex).string;
                    TIntermTyped* index = parseContext.intermediate.addSwizzle(fields, (yyvsp[(3) - (3)].lex).line);                
                    (yyval.interm.intermTypedNode) = parseContext.intermediate.addIndex(EOpVectorSwizzle, (yyvsp[(1) - (3)].interm.intermTypedNode), index, (yyvsp[(2) - (3)].lex).line);
                    (yyval.interm.intermTypedNode)->setType(TType((yyvsp[(1) - (3)].interm.intermTypedNode)->getBasicType(), (yyvsp[(1) - (3)].interm.intermTypedNode)->getPrecision(), EvqTemporary, (int) vectorString.size()));  
                }
            }
        } else if ((yyvsp[(1) - (3)].interm.intermTypedNode)->isMatrix()) {
            TVectorFields fields;
            if (! parseContext.parseMatrixFields(*(yyvsp[(3) - (3)].lex).string, (yyvsp[(1) - (3)].interm.intermTypedNode)->getNominalSize(), fields, (yyvsp[(3) - (3)].lex).line)) {
                fields.num = 1;
                fields.offsets[0] = 0;
                parseContext.recover();
            }

            TString vectorString = *(yyvsp[(3) - (3)].lex).string;
            TIntermTyped* index = parseContext.intermediate.addSwizzle(fields, (yyvsp[(3) - (3)].lex).line);                
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addIndex(EOpMatrixSwizzle, (yyvsp[(1) - (3)].interm.intermTypedNode), index, (yyvsp[(2) - (3)].lex).line);
            (yyval.interm.intermTypedNode)->setType(TType((yyvsp[(1) - (3)].interm.intermTypedNode)->getBasicType(), (yyvsp[(1) - (3)].interm.intermTypedNode)->getPrecision(), EvqTemporary, fields.num));
                    
        } else if ((yyvsp[(1) - (3)].interm.intermTypedNode)->getBasicType() == EbtStruct) {
            bool fieldFound = false;
            TTypeList* fields = (yyvsp[(1) - (3)].interm.intermTypedNode)->getType().getStruct();
            if (fields == 0) {
                parseContext.error((yyvsp[(2) - (3)].lex).line, "structure has no fields", "Internal Error", "");
                parseContext.recover();
                (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
            } else {
                unsigned int i;
                for (i = 0; i < fields->size(); ++i) {
                    if ((*fields)[i].type->getFieldName() == *(yyvsp[(3) - (3)].lex).string) {
                        fieldFound = true;
                        break;
                    }                
                }
                if (fieldFound) {
                    if ((yyvsp[(1) - (3)].interm.intermTypedNode)->getType().getQualifier() == EvqConst) {
                        (yyval.interm.intermTypedNode) = parseContext.addConstStruct(*(yyvsp[(3) - (3)].lex).string, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(2) - (3)].lex).line);
                        if ((yyval.interm.intermTypedNode) == 0) {
                            parseContext.recover();
                            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
                        }
                        else {
                            (yyval.interm.intermTypedNode)->setType(*(*fields)[i].type);
                            // change the qualifier of the return type, not of the structure field
                            // as the structure definition is shared between various structures.
                            (yyval.interm.intermTypedNode)->getTypePointer()->changeQualifier(EvqConst);
                        }
                    } else {
                        constUnion *unionArray = new constUnion[1];
                        unionArray->setIConst(i);
                        TIntermTyped* index = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtInt, EbpUndefined, EvqConst), (yyvsp[(3) - (3)].lex).line);
                        (yyval.interm.intermTypedNode) = parseContext.intermediate.addIndex(EOpIndexDirectStruct, (yyvsp[(1) - (3)].interm.intermTypedNode), index, (yyvsp[(2) - (3)].lex).line);                
                        (yyval.interm.intermTypedNode)->setType(*(*fields)[i].type);
                    }
                } else {
                    parseContext.error((yyvsp[(2) - (3)].lex).line, " no such field in structure", (yyvsp[(3) - (3)].lex).string->c_str(), "");
                    parseContext.recover();
                    (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
                }
            }
        } else if ((yyvsp[(1) - (3)].interm.intermTypedNode)->getNominalSize() == 1) {

            // HLSL allows ".xxxx" field selection on single component floats.  Handle that here.
            TVectorFields fields;

            // Check to make sure only the "x" component is accessed.
            if (! parseContext.parseVectorFields(*(yyvsp[(3) - (3)].lex).string, (yyvsp[(1) - (3)].interm.intermTypedNode)->getNominalSize(), fields, (yyvsp[(3) - (3)].lex).line)) {
                fields.num = 1;
                fields.offsets[0] = 0;
                parseContext.recover();
            }

            // Create the appropriate constructor based on the number of ".x"'s there are in the selection field
            TString vectorString = *(yyvsp[(3) - (3)].lex).string;
            TQualifier qualifier = (yyvsp[(1) - (3)].interm.intermTypedNode)->getType().getQualifier() == EvqConst ? EvqConst : EvqTemporary;
            TType type((yyvsp[(1) - (3)].interm.intermTypedNode)->getBasicType(), (yyvsp[(1) - (3)].interm.intermTypedNode)->getPrecision(), qualifier, (int) vectorString.size());
            (yyval.interm.intermTypedNode) = parseContext.constructBuiltIn(&type, parseContext.getConstructorOp(type),
                                               (yyval.interm.intermTypedNode), (yyvsp[(1) - (3)].interm.intermTypedNode)->getLine(), false);
        } else {
            parseContext.error((yyvsp[(2) - (3)].lex).line, " field selection requires structure, vector, or matrix on left hand side", (yyvsp[(3) - (3)].lex).string->c_str(), "");
            parseContext.recover();
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
        }
        // don't delete $3.string, it's from the pool
    ;}
    break;

  case 12:
#line 452 "hlslang.y"
    {
        if (parseContext.lValueErrorCheck((yyvsp[(2) - (2)].lex).line, "++", (yyvsp[(1) - (2)].interm.intermTypedNode)))
            parseContext.recover();
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addUnaryMath(EOpPostIncrement, (yyvsp[(1) - (2)].interm.intermTypedNode), (yyvsp[(2) - (2)].lex).line, parseContext.symbolTable);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.unaryOpError((yyvsp[(2) - (2)].lex).line, "++", (yyvsp[(1) - (2)].interm.intermTypedNode)->getCompleteString());
            parseContext.recover();
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (2)].interm.intermTypedNode);
        }
    ;}
    break;

  case 13:
#line 462 "hlslang.y"
    {
        if (parseContext.lValueErrorCheck((yyvsp[(2) - (2)].lex).line, "--", (yyvsp[(1) - (2)].interm.intermTypedNode)))
            parseContext.recover();
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addUnaryMath(EOpPostDecrement, (yyvsp[(1) - (2)].interm.intermTypedNode), (yyvsp[(2) - (2)].lex).line, parseContext.symbolTable);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.unaryOpError((yyvsp[(2) - (2)].lex).line, "--", (yyvsp[(1) - (2)].interm.intermTypedNode)->getCompleteString());
            parseContext.recover();
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (2)].interm.intermTypedNode);
        }
    ;}
    break;

  case 14:
#line 475 "hlslang.y"
    {
        if (parseContext.integerErrorCheck((yyvsp[(1) - (1)].interm.intermTypedNode), "[]"))
            parseContext.recover();
        (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); 
    ;}
    break;

  case 15:
#line 483 "hlslang.y"
    {
        TFunction* fnCall = (yyvsp[(1) - (1)].interm).function;
        TOperator op = fnCall->getBuiltInOp();
        
        if (op == EOpArrayLength) {
            if ((yyvsp[(1) - (1)].interm).intermNode->getAsTyped() == 0 || (yyvsp[(1) - (1)].interm).intermNode->getAsTyped()->getType().getArraySize() == 0) {
                parseContext.error((yyvsp[(1) - (1)].interm).line, "", fnCall->getName().c_str(), "array must be declared with a size before using this method");
                parseContext.recover();
            }

            constUnion *unionArray = new constUnion[1];
            unionArray->setIConst((yyvsp[(1) - (1)].interm).intermNode->getAsTyped()->getType().getArraySize());
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtInt, EbpUndefined, EvqConst), (yyvsp[(1) - (1)].interm).line);
        } else if (op != EOpNull) {
            //
            // Then this should be a constructor.
            // Don't go through the symbol table for constructors.  
            // Their parameters will be verified algorithmically.
            //
            TType type(EbtVoid, EbpUndefined);  // use this to get the type back
            if (parseContext.constructorErrorCheck((yyvsp[(1) - (1)].interm).line, (yyvsp[(1) - (1)].interm).intermNode, *fnCall, op, &type)) {
                (yyval.interm.intermTypedNode) = 0;
            } else {
                //
                // It's a constructor, of type 'type'.
                //
                (yyval.interm.intermTypedNode) = parseContext.addConstructor((yyvsp[(1) - (1)].interm).intermNode, &type, op, fnCall, (yyvsp[(1) - (1)].interm).line);
            }
            
            if ((yyval.interm.intermTypedNode) == 0) {        
                parseContext.recover();
                (yyval.interm.intermTypedNode) = parseContext.intermediate.setAggregateOperator(0, op, (yyvsp[(1) - (1)].interm).line);
            }
            (yyval.interm.intermTypedNode)->setType(type);
        } else {
            //
            // Not a constructor.  Find it in the symbol table.
            //
            const TFunction* fnCandidate;
            bool builtIn;
            fnCandidate = parseContext.findFunction((yyvsp[(1) - (1)].interm).line, fnCall, &builtIn);
            
            if ( fnCandidate && fnCandidate->getMangledName() != fnCall->getMangledName()) {
                //add constructors to arguments to ensure that they have proper types
                TIntermNode *temp = parseContext.promoteFunctionArguments( (yyvsp[(1) - (1)].interm).intermNode,
                                      fnCandidate);
                if (temp)
                    (yyvsp[(1) - (1)].interm).intermNode = temp;
                else {
                    parseContext.error( (yyvsp[(1) - (1)].interm).intermNode->getLine(), " unable to suitably promote arguments to function",
                                        fnCandidate->getName().c_str(), "");
                    fnCandidate = 0;
                }
            }
            
            if (fnCandidate) {
                //
                // A declared function.  But, it might still map to a built-in
                // operation.
                //
                op = fnCandidate->getBuiltInOp();
                if (builtIn && op != EOpNull) {
                    //
                    // A function call mapped to a built-in operation.
                    //
                    if (fnCandidate->getParamCount() == 1) {
                        //
                        // Treat it like a built-in unary operator.
                        //
                        (yyval.interm.intermTypedNode) = parseContext.intermediate.addUnaryMath(op, (yyvsp[(1) - (1)].interm).intermNode, 0, parseContext.symbolTable);
                        if ((yyval.interm.intermTypedNode) == 0)  {
                            parseContext.error((yyvsp[(1) - (1)].interm).intermNode->getLine(), " wrong operand type", "Internal Error", 
                                "built in unary operator function.  Type: %s",
                                static_cast<TIntermTyped*>((yyvsp[(1) - (1)].interm).intermNode)->getCompleteString().c_str());
                            YYERROR;
                        }
                    } else {
                        (yyval.interm.intermTypedNode) = parseContext.intermediate.setAggregateOperator((yyvsp[(1) - (1)].interm).intermAggregate, op, (yyvsp[(1) - (1)].interm).line);
                    }
                } else {
                    // This is a real function call
                    
                    (yyval.interm.intermTypedNode) = parseContext.intermediate.setAggregateOperator((yyvsp[(1) - (1)].interm).intermAggregate, EOpFunctionCall, (yyvsp[(1) - (1)].interm).line);
                    (yyval.interm.intermTypedNode)->setType(fnCandidate->getReturnType());                   
                    
                    (yyval.interm.intermTypedNode)->getAsAggregate()->setName(fnCandidate->getMangledName());
                    (yyval.interm.intermTypedNode)->getAsAggregate()->setPlainName(fnCandidate->getName());

                    TQualifier qual;
                    for (int i = 0; i < fnCandidate->getParamCount(); ++i) {
                        qual = (*fnCandidate)[i].type->getQualifier();
                        if (qual == EvqOut || qual == EvqInOut) {
                            if (parseContext.lValueErrorCheck((yyval.interm.intermTypedNode)->getLine(), "assign", (yyval.interm.intermTypedNode)->getAsAggregate()->getSequence()[i]->getAsTyped())) {
                                parseContext.error((yyvsp[(1) - (1)].interm).intermNode->getLine(), "Constant value cannot be passed for 'out' or 'inout' parameters.", "Error", "");
                                parseContext.recover();
                            }
                        }
                    }
                }
                (yyval.interm.intermTypedNode)->setType(fnCandidate->getReturnType());
            } else {
                // error message was put out by PaFindFunction()
                // Put on a dummy node for error recovery
                constUnion *unionArray = new constUnion[1];
                unionArray->setFConst(0.0f);
                (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtFloat, EbpUndefined, EvqConst), (yyvsp[(1) - (1)].interm).line);
                parseContext.recover();
            }
        }
        delete fnCall;
    ;}
    break;

  case 16:
#line 597 "hlslang.y"
    {
        (yyval.interm) = (yyvsp[(1) - (1)].interm);
    ;}
    break;

  case 17:
#line 600 "hlslang.y"
    {
        if ((yyvsp[(1) - (3)].interm.intermTypedNode)->isArray() && (yyvsp[(3) - (3)].interm).function->getName() == "length") {
            //
            // implement array.length()
            //            
            (yyval.interm) = (yyvsp[(3) - (3)].interm);
            (yyval.interm).intermNode = (yyvsp[(1) - (3)].interm.intermTypedNode);
            (yyval.interm).function->relateToOperator(EOpArrayLength);
            
        } else {
            parseContext.error((yyvsp[(3) - (3)].interm).line, "methods are not supported", "", "");
            parseContext.recover();
            (yyval.interm) = (yyvsp[(3) - (3)].interm);
        }
    ;}
    break;

  case 18:
#line 618 "hlslang.y"
    {
        (yyval.interm) = (yyvsp[(1) - (2)].interm);
        (yyval.interm).line = (yyvsp[(2) - (2)].lex).line;
    ;}
    break;

  case 19:
#line 622 "hlslang.y"
    {
        (yyval.interm) = (yyvsp[(1) - (2)].interm);
        (yyval.interm).line = (yyvsp[(2) - (2)].lex).line;
    ;}
    break;

  case 20:
#line 629 "hlslang.y"
    {
        (yyval.interm).function = (yyvsp[(1) - (2)].interm.function);
        (yyval.interm).intermNode = 0;
    ;}
    break;

  case 21:
#line 633 "hlslang.y"
    {
        (yyval.interm).function = (yyvsp[(1) - (1)].interm.function);
        (yyval.interm).intermNode = 0;
    ;}
    break;

  case 22:
#line 640 "hlslang.y"
    {
		if (!(yyvsp[(2) - (2)].interm.intermTypedNode)) {
          YYERROR;
		}
		TParameter param = { 0, 0, new TType((yyvsp[(2) - (2)].interm.intermTypedNode)->getType()) };
        (yyvsp[(1) - (2)].interm.function)->addParameter(param);
        (yyval.interm).function = (yyvsp[(1) - (2)].interm.function);
        (yyval.interm).intermNode = (yyvsp[(2) - (2)].interm.intermTypedNode);
    ;}
    break;

  case 23:
#line 649 "hlslang.y"
    {
		if (!(yyvsp[(3) - (3)].interm.intermTypedNode)) {
          YYERROR;
		}
        TParameter param = { 0, 0, new TType((yyvsp[(3) - (3)].interm.intermTypedNode)->getType()) };
        (yyvsp[(1) - (3)].interm).function->addParameter(param);
        (yyval.interm).function = (yyvsp[(1) - (3)].interm).function;
        (yyval.interm).intermNode = parseContext.intermediate.growAggregate((yyvsp[(1) - (3)].interm).intermNode, (yyvsp[(3) - (3)].interm.intermTypedNode), (yyvsp[(2) - (3)].lex).line);
    ;}
    break;

  case 24:
#line 661 "hlslang.y"
    {
        (yyval.interm.function) = (yyvsp[(1) - (2)].interm.function);
    ;}
    break;

  case 25:
#line 669 "hlslang.y"
    {
        //
        // Constructor
        //
        if ((yyvsp[(1) - (1)].interm.type).array) {
            //TODO : figure out how to deal with array constructors            
        }

        if ((yyvsp[(1) - (1)].interm.type).userDef) {
            TString tempString = "";
            TType type((yyvsp[(1) - (1)].interm.type));
            TFunction *function = new TFunction(&tempString, type, EOpConstructStruct);
            (yyval.interm.function) = function;
        } else {
            TOperator op = EOpNull;
            switch ((yyvsp[(1) - (1)].interm.type).type) {
            case EbtFloat:
                if ((yyvsp[(1) - (1)].interm.type).matrix) {
                    switch((yyvsp[(1) - (1)].interm.type).size) {
                    case 2:                                     op = EOpConstructMat2;  break;
                    case 3:                                     op = EOpConstructMat3;  break;
                    case 4:                                     op = EOpConstructMat4;  break;
                    }         
                } else {      
                    switch((yyvsp[(1) - (1)].interm.type).size) {
                    case 1:                                     op = EOpConstructFloat; break;
                    case 2:                                     op = EOpConstructVec2;  break;
                    case 3:                                     op = EOpConstructVec3;  break;
                    case 4:                                     op = EOpConstructVec4;  break;
                    }       
                }  
                break;               
            case EbtInt:
                switch((yyvsp[(1) - (1)].interm.type).size) {
                case 1:                                         op = EOpConstructInt;   break;
                case 2:       FRAG_VERT_ONLY("ivec2", (yyvsp[(1) - (1)].interm.type).line); op = EOpConstructIVec2; break;
                case 3:       FRAG_VERT_ONLY("ivec3", (yyvsp[(1) - (1)].interm.type).line); op = EOpConstructIVec3; break;
                case 4:       FRAG_VERT_ONLY("ivec4", (yyvsp[(1) - (1)].interm.type).line); op = EOpConstructIVec4; break;
                }         
                break;    
            case EbtBool:
                switch((yyvsp[(1) - (1)].interm.type).size) {
                case 1:                                         op = EOpConstructBool;  break;
                case 2:       FRAG_VERT_ONLY("bvec2", (yyvsp[(1) - (1)].interm.type).line); op = EOpConstructBVec2; break;
                case 3:       FRAG_VERT_ONLY("bvec3", (yyvsp[(1) - (1)].interm.type).line); op = EOpConstructBVec3; break;
                case 4:       FRAG_VERT_ONLY("bvec4", (yyvsp[(1) - (1)].interm.type).line); op = EOpConstructBVec4; break;
                }         
                break;
            }
            if (op == EOpNull) {                    
                parseContext.error((yyvsp[(1) - (1)].interm.type).line, "cannot construct this type", TType::getBasicString((yyvsp[(1) - (1)].interm.type).type), "");
                parseContext.recover();
                (yyvsp[(1) - (1)].interm.type).type = EbtFloat;
                op = EOpConstructFloat;
            }            
            TString tempString = "";
            TType type((yyvsp[(1) - (1)].interm.type));
            TFunction *function = new TFunction(&tempString, type, op);
            (yyval.interm.function) = function;
        }
    ;}
    break;

  case 26:
#line 730 "hlslang.y"
    {
        if (parseContext.reservedErrorCheck((yyvsp[(1) - (1)].lex).line, *(yyvsp[(1) - (1)].lex).string)) 
            parseContext.recover();
        TType type(EbtVoid, EbpUndefined);
	const TString *mangled;
	if ( *(yyvsp[(1) - (1)].lex).string == "main")
	    mangled = NewPoolTString("xlat_main");
	else
	    mangled = (yyvsp[(1) - (1)].lex).string;
        TFunction *function = new TFunction( mangled, type);
        (yyval.interm.function) = function;
    ;}
    break;

  case 27:
#line 742 "hlslang.y"
    {
        if (parseContext.reservedErrorCheck((yyvsp[(1) - (1)].lex).line, *(yyvsp[(1) - (1)].lex).string)) 
            parseContext.recover();
        TType type(EbtVoid, EbpUndefined);
        TFunction *function = new TFunction((yyvsp[(1) - (1)].lex).string, type);
        (yyval.interm.function) = function;
    ;}
    break;

  case 28:
#line 752 "hlslang.y"
    {
        (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode);
    ;}
    break;

  case 29:
#line 755 "hlslang.y"
    {
        if (parseContext.lValueErrorCheck((yyvsp[(1) - (2)].lex).line, "++", (yyvsp[(2) - (2)].interm.intermTypedNode)))
            parseContext.recover();
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addUnaryMath(EOpPreIncrement, (yyvsp[(2) - (2)].interm.intermTypedNode), (yyvsp[(1) - (2)].lex).line, parseContext.symbolTable);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.unaryOpError((yyvsp[(1) - (2)].lex).line, "++", (yyvsp[(2) - (2)].interm.intermTypedNode)->getCompleteString());
            parseContext.recover();
            (yyval.interm.intermTypedNode) = (yyvsp[(2) - (2)].interm.intermTypedNode);
        }
    ;}
    break;

  case 30:
#line 765 "hlslang.y"
    {
        if (parseContext.lValueErrorCheck((yyvsp[(1) - (2)].lex).line, "--", (yyvsp[(2) - (2)].interm.intermTypedNode)))
            parseContext.recover();
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addUnaryMath(EOpPreDecrement, (yyvsp[(2) - (2)].interm.intermTypedNode), (yyvsp[(1) - (2)].lex).line, parseContext.symbolTable);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.unaryOpError((yyvsp[(1) - (2)].lex).line, "--", (yyvsp[(2) - (2)].interm.intermTypedNode)->getCompleteString());
            parseContext.recover();
            (yyval.interm.intermTypedNode) = (yyvsp[(2) - (2)].interm.intermTypedNode);
        }
    ;}
    break;

  case 31:
#line 775 "hlslang.y"
    {
        if ((yyvsp[(1) - (2)].interm).op != EOpNull) {
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addUnaryMath((yyvsp[(1) - (2)].interm).op, (yyvsp[(2) - (2)].interm.intermTypedNode), (yyvsp[(1) - (2)].interm).line, parseContext.symbolTable);
            if ((yyval.interm.intermTypedNode) == 0) {
                const char* errorOp = "";
                switch((yyvsp[(1) - (2)].interm).op) {
                case EOpNegative:   errorOp = "-"; break;
                case EOpLogicalNot: errorOp = "!"; break;
                case EOpBitwiseNot: errorOp = "~"; break;
				default: break;
                }
                parseContext.unaryOpError((yyvsp[(1) - (2)].interm).line, const_cast<char*> (errorOp), (yyvsp[(2) - (2)].interm.intermTypedNode)->getCompleteString());
                parseContext.recover();
                (yyval.interm.intermTypedNode) = (yyvsp[(2) - (2)].interm.intermTypedNode);
            }
        } else
            (yyval.interm.intermTypedNode) = (yyvsp[(2) - (2)].interm.intermTypedNode);
    ;}
    break;

  case 32:
#line 793 "hlslang.y"
    {
        // cast operator, insert constructor
        TOperator op = EOpNull;
        switch ((yyvsp[(2) - (4)].interm.type).type) {
        case EbtFloat:
            if ((yyvsp[(2) - (4)].interm.type).matrix) {
                switch((yyvsp[(2) - (4)].interm.type).size) {
                case 2:                                     op = EOpConstructMat2;  break;
                case 3:                                     op = EOpConstructMat3;  break;
                case 4:                                     op = EOpConstructMat4;  break;
                }         
            } else {      
                switch((yyvsp[(2) - (4)].interm.type).size) {
                case 1:                                     op = EOpConstructFloat; break;
                case 2:                                     op = EOpConstructVec2;  break;
                case 3:                                     op = EOpConstructVec3;  break;
                case 4:                                     op = EOpConstructVec4;  break;
                }       
            }  
            break;               
        case EbtInt:
            switch((yyvsp[(2) - (4)].interm.type).size) {
            case 1:                                         op = EOpConstructInt;   break;
            case 2:       FRAG_VERT_ONLY("ivec2", (yyvsp[(2) - (4)].interm.type).line); op = EOpConstructIVec2; break;
            case 3:       FRAG_VERT_ONLY("ivec3", (yyvsp[(2) - (4)].interm.type).line); op = EOpConstructIVec3; break;
            case 4:       FRAG_VERT_ONLY("ivec4", (yyvsp[(2) - (4)].interm.type).line); op = EOpConstructIVec4; break;
            }         
            break;    
        case EbtBool:
            switch((yyvsp[(2) - (4)].interm.type).size) {
            case 1:                                         op = EOpConstructBool;  break;
            case 2:       FRAG_VERT_ONLY("bvec2", (yyvsp[(2) - (4)].interm.type).line); op = EOpConstructBVec2; break;
            case 3:       FRAG_VERT_ONLY("bvec3", (yyvsp[(2) - (4)].interm.type).line); op = EOpConstructBVec3; break;
            case 4:       FRAG_VERT_ONLY("bvec4", (yyvsp[(2) - (4)].interm.type).line); op = EOpConstructBVec4; break;
            }         
            break;
        case EbtStruct:
            op = EOpConstructStruct;
            break;
        }
        if (op == EOpNull) {                    
            parseContext.error((yyvsp[(2) - (4)].interm.type).line, "cannot cast this type", TType::getBasicString((yyvsp[(2) - (4)].interm.type).type), "");
            parseContext.recover();
            (yyvsp[(2) - (4)].interm.type).type = EbtFloat;
            op = EOpConstructFloat;
        }            
        TString tempString = "";
        TType type((yyvsp[(2) - (4)].interm.type));
        TFunction *function = new TFunction(&tempString, type, op);
        TParameter param = { 0, 0, new TType((yyvsp[(4) - (4)].interm.intermTypedNode)->getType()) };
        function->addParameter(param);
        TType type2(EbtVoid, EbpUndefined);  // use this to get the type back
        if (parseContext.constructorErrorCheck((yyvsp[(2) - (4)].interm.type).line, (yyvsp[(4) - (4)].interm.intermTypedNode), *function, op, &type2)) {
            (yyval.interm.intermTypedNode) = 0;
        } else {
            //
            // It's a constructor, of type 'type'.
            //
            (yyval.interm.intermTypedNode) = parseContext.addConstructor((yyvsp[(4) - (4)].interm.intermTypedNode), &type2, op, function, (yyvsp[(2) - (4)].interm.type).line);
        }
        
        if ((yyval.interm.intermTypedNode) == 0) {        
            parseContext.recover();
            (yyval.interm.intermTypedNode) = parseContext.intermediate.setAggregateOperator(0, op, (yyvsp[(2) - (4)].interm.type).line);
        }
        (yyval.interm.intermTypedNode)->setType(type2);
    ;}
    break;

  case 33:
#line 864 "hlslang.y"
    { (yyval.interm).line = (yyvsp[(1) - (1)].lex).line; (yyval.interm).op = EOpNull; ;}
    break;

  case 34:
#line 865 "hlslang.y"
    { (yyval.interm).line = (yyvsp[(1) - (1)].lex).line; (yyval.interm).op = EOpNegative; ;}
    break;

  case 35:
#line 866 "hlslang.y"
    { (yyval.interm).line = (yyvsp[(1) - (1)].lex).line; (yyval.interm).op = EOpLogicalNot; ;}
    break;

  case 36:
#line 867 "hlslang.y"
    { UNSUPPORTED_FEATURE("~", (yyvsp[(1) - (1)].lex).line);  
              (yyval.interm).line = (yyvsp[(1) - (1)].lex).line; (yyval.interm).op = EOpBitwiseNot; ;}
    break;

  case 37:
#line 873 "hlslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); ;}
    break;

  case 38:
#line 874 "hlslang.y"
    {
        FRAG_VERT_ONLY("*", (yyvsp[(2) - (3)].lex).line);
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addBinaryMath(EOpMul, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode), (yyvsp[(2) - (3)].lex).line, parseContext.symbolTable);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.binaryOpError((yyvsp[(2) - (3)].lex).line, "*", (yyvsp[(1) - (3)].interm.intermTypedNode)->getCompleteString(), (yyvsp[(3) - (3)].interm.intermTypedNode)->getCompleteString());
            parseContext.recover();
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
        }
    ;}
    break;

  case 39:
#line 883 "hlslang.y"
    {
        FRAG_VERT_ONLY("/", (yyvsp[(2) - (3)].lex).line); 
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addBinaryMath(EOpDiv, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode), (yyvsp[(2) - (3)].lex).line, parseContext.symbolTable);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.binaryOpError((yyvsp[(2) - (3)].lex).line, "/", (yyvsp[(1) - (3)].interm.intermTypedNode)->getCompleteString(), (yyvsp[(3) - (3)].interm.intermTypedNode)->getCompleteString());
            parseContext.recover();
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
        }
    ;}
    break;

  case 40:
#line 892 "hlslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addBinaryMath(EOpMod, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode), (yyvsp[(2) - (3)].lex).line, parseContext.symbolTable);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.binaryOpError((yyvsp[(2) - (3)].lex).line, "%", (yyvsp[(1) - (3)].interm.intermTypedNode)->getCompleteString(), (yyvsp[(3) - (3)].interm.intermTypedNode)->getCompleteString());
            parseContext.recover();
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
        }
    ;}
    break;

  case 41:
#line 903 "hlslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); ;}
    break;

  case 42:
#line 904 "hlslang.y"
    {  
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addBinaryMath(EOpAdd, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode), (yyvsp[(2) - (3)].lex).line, parseContext.symbolTable);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.binaryOpError((yyvsp[(2) - (3)].lex).line, "+", (yyvsp[(1) - (3)].interm.intermTypedNode)->getCompleteString(), (yyvsp[(3) - (3)].interm.intermTypedNode)->getCompleteString());
            parseContext.recover();
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
        }
    ;}
    break;

  case 43:
#line 912 "hlslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addBinaryMath(EOpSub, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode), (yyvsp[(2) - (3)].lex).line, parseContext.symbolTable);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.binaryOpError((yyvsp[(2) - (3)].lex).line, "-", (yyvsp[(1) - (3)].interm.intermTypedNode)->getCompleteString(), (yyvsp[(3) - (3)].interm.intermTypedNode)->getCompleteString());
            parseContext.recover();
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
        } 
    ;}
    break;

  case 44:
#line 923 "hlslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); ;}
    break;

  case 45:
#line 924 "hlslang.y"
    {
        UNSUPPORTED_FEATURE("<<", (yyvsp[(2) - (3)].lex).line);
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addBinaryMath(EOpLeftShift, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode), (yyvsp[(2) - (3)].lex).line, parseContext.symbolTable);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.binaryOpError((yyvsp[(2) - (3)].lex).line, "<<", (yyvsp[(1) - (3)].interm.intermTypedNode)->getCompleteString(), (yyvsp[(3) - (3)].interm.intermTypedNode)->getCompleteString());
            parseContext.recover();
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
        }
    ;}
    break;

  case 46:
#line 933 "hlslang.y"
    {
        UNSUPPORTED_FEATURE(">>", (yyvsp[(2) - (3)].lex).line);
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addBinaryMath(EOpRightShift, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode), (yyvsp[(2) - (3)].lex).line, parseContext.symbolTable);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.binaryOpError((yyvsp[(2) - (3)].lex).line, ">>", (yyvsp[(1) - (3)].interm.intermTypedNode)->getCompleteString(), (yyvsp[(3) - (3)].interm.intermTypedNode)->getCompleteString());
            parseContext.recover();
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
        }
    ;}
    break;

  case 47:
#line 945 "hlslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); ;}
    break;

  case 48:
#line 946 "hlslang.y"
    { 
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addBinaryMath(EOpLessThan, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode), (yyvsp[(2) - (3)].lex).line, parseContext.symbolTable);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.binaryOpError((yyvsp[(2) - (3)].lex).line, "<", (yyvsp[(1) - (3)].interm.intermTypedNode)->getCompleteString(), (yyvsp[(3) - (3)].interm.intermTypedNode)->getCompleteString());
            parseContext.recover();
            constUnion *unionArray = new constUnion[1];
            unionArray->setBConst(false);
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtBool, EbpUndefined, EvqConst), (yyvsp[(2) - (3)].lex).line);
        }
    ;}
    break;

  case 49:
#line 956 "hlslang.y"
    { 
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addBinaryMath(EOpGreaterThan, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode), (yyvsp[(2) - (3)].lex).line, parseContext.symbolTable);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.binaryOpError((yyvsp[(2) - (3)].lex).line, ">", (yyvsp[(1) - (3)].interm.intermTypedNode)->getCompleteString(), (yyvsp[(3) - (3)].interm.intermTypedNode)->getCompleteString());
            parseContext.recover();
            constUnion *unionArray = new constUnion[1];
            unionArray->setBConst(false);
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtBool, EbpUndefined, EvqConst), (yyvsp[(2) - (3)].lex).line);
        }
    ;}
    break;

  case 50:
#line 966 "hlslang.y"
    { 
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addBinaryMath(EOpLessThanEqual, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode), (yyvsp[(2) - (3)].lex).line, parseContext.symbolTable);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.binaryOpError((yyvsp[(2) - (3)].lex).line, "<=", (yyvsp[(1) - (3)].interm.intermTypedNode)->getCompleteString(), (yyvsp[(3) - (3)].interm.intermTypedNode)->getCompleteString());
            parseContext.recover();
            constUnion *unionArray = new constUnion[1];
            unionArray->setBConst(false);
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtBool, EbpUndefined, EvqConst), (yyvsp[(2) - (3)].lex).line);
        }
    ;}
    break;

  case 51:
#line 976 "hlslang.y"
    { 
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addBinaryMath(EOpGreaterThanEqual, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode), (yyvsp[(2) - (3)].lex).line, parseContext.symbolTable);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.binaryOpError((yyvsp[(2) - (3)].lex).line, ">=", (yyvsp[(1) - (3)].interm.intermTypedNode)->getCompleteString(), (yyvsp[(3) - (3)].interm.intermTypedNode)->getCompleteString());
            parseContext.recover();
            constUnion *unionArray = new constUnion[1];
            unionArray->setBConst(false);
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtBool, EbpUndefined, EvqConst), (yyvsp[(2) - (3)].lex).line);
        }
    ;}
    break;

  case 52:
#line 989 "hlslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); ;}
    break;

  case 53:
#line 990 "hlslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addBinaryMath(EOpEqual, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode), (yyvsp[(2) - (3)].lex).line, parseContext.symbolTable);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.binaryOpError((yyvsp[(2) - (3)].lex).line, "==", (yyvsp[(1) - (3)].interm.intermTypedNode)->getCompleteString(), (yyvsp[(3) - (3)].interm.intermTypedNode)->getCompleteString());
            parseContext.recover();
            constUnion *unionArray = new constUnion[1];
            unionArray->setBConst(false);
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtBool, EbpUndefined, EvqConst), (yyvsp[(2) - (3)].lex).line);
        } else if (((yyvsp[(1) - (3)].interm.intermTypedNode)->isArray() || (yyvsp[(3) - (3)].interm.intermTypedNode)->isArray()))
            parseContext.recover();
    ;}
    break;

  case 54:
#line 1001 "hlslang.y"
    { 
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addBinaryMath(EOpNotEqual, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode), (yyvsp[(2) - (3)].lex).line, parseContext.symbolTable);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.binaryOpError((yyvsp[(2) - (3)].lex).line, "!=", (yyvsp[(1) - (3)].interm.intermTypedNode)->getCompleteString(), (yyvsp[(3) - (3)].interm.intermTypedNode)->getCompleteString());
            parseContext.recover();
            constUnion *unionArray = new constUnion[1];
            unionArray->setBConst(false);
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtBool, EbpUndefined, EvqConst), (yyvsp[(2) - (3)].lex).line);
        } else if (((yyvsp[(1) - (3)].interm.intermTypedNode)->isArray() || (yyvsp[(3) - (3)].interm.intermTypedNode)->isArray()))
            parseContext.recover();
    ;}
    break;

  case 55:
#line 1015 "hlslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); ;}
    break;

  case 56:
#line 1016 "hlslang.y"
    {
        UNSUPPORTED_FEATURE("&", (yyvsp[(2) - (3)].lex).line);
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addBinaryMath(EOpAnd, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode), (yyvsp[(2) - (3)].lex).line, parseContext.symbolTable);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.binaryOpError((yyvsp[(2) - (3)].lex).line, "&", (yyvsp[(1) - (3)].interm.intermTypedNode)->getCompleteString(), (yyvsp[(3) - (3)].interm.intermTypedNode)->getCompleteString());
            parseContext.recover();
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
        }
    ;}
    break;

  case 57:
#line 1028 "hlslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); ;}
    break;

  case 58:
#line 1029 "hlslang.y"
    {
        UNSUPPORTED_FEATURE("^", (yyvsp[(2) - (3)].lex).line);
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addBinaryMath(EOpExclusiveOr, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode), (yyvsp[(2) - (3)].lex).line, parseContext.symbolTable);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.binaryOpError((yyvsp[(2) - (3)].lex).line, "^", (yyvsp[(1) - (3)].interm.intermTypedNode)->getCompleteString(), (yyvsp[(3) - (3)].interm.intermTypedNode)->getCompleteString());
            parseContext.recover();
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
        }
    ;}
    break;

  case 59:
#line 1041 "hlslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); ;}
    break;

  case 60:
#line 1042 "hlslang.y"
    {
        UNSUPPORTED_FEATURE("|", (yyvsp[(2) - (3)].lex).line);
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addBinaryMath(EOpInclusiveOr, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode), (yyvsp[(2) - (3)].lex).line, parseContext.symbolTable);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.binaryOpError((yyvsp[(2) - (3)].lex).line, "|", (yyvsp[(1) - (3)].interm.intermTypedNode)->getCompleteString(), (yyvsp[(3) - (3)].interm.intermTypedNode)->getCompleteString());
            parseContext.recover();
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
        }
    ;}
    break;

  case 61:
#line 1054 "hlslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); ;}
    break;

  case 62:
#line 1055 "hlslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addBinaryMath(EOpLogicalAnd, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode), (yyvsp[(2) - (3)].lex).line, parseContext.symbolTable);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.binaryOpError((yyvsp[(2) - (3)].lex).line, "&&", (yyvsp[(1) - (3)].interm.intermTypedNode)->getCompleteString(), (yyvsp[(3) - (3)].interm.intermTypedNode)->getCompleteString());
            parseContext.recover();
            constUnion *unionArray = new constUnion[1];
            unionArray->setBConst(false);
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtBool, EbpUndefined, EvqConst), (yyvsp[(2) - (3)].lex).line);
        }
    ;}
    break;

  case 63:
#line 1068 "hlslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); ;}
    break;

  case 64:
#line 1069 "hlslang.y"
    { 
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addBinaryMath(EOpLogicalXor, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode), (yyvsp[(2) - (3)].lex).line, parseContext.symbolTable);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.binaryOpError((yyvsp[(2) - (3)].lex).line, "^^", (yyvsp[(1) - (3)].interm.intermTypedNode)->getCompleteString(), (yyvsp[(3) - (3)].interm.intermTypedNode)->getCompleteString());
            parseContext.recover();
            constUnion *unionArray = new constUnion[1];
            unionArray->setBConst(false);
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtBool, EbpUndefined, EvqConst), (yyvsp[(2) - (3)].lex).line);
        }
    ;}
    break;

  case 65:
#line 1082 "hlslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); ;}
    break;

  case 66:
#line 1083 "hlslang.y"
    { 
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addBinaryMath(EOpLogicalOr, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode), (yyvsp[(2) - (3)].lex).line, parseContext.symbolTable);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.binaryOpError((yyvsp[(2) - (3)].lex).line, "||", (yyvsp[(1) - (3)].interm.intermTypedNode)->getCompleteString(), (yyvsp[(3) - (3)].interm.intermTypedNode)->getCompleteString());
            parseContext.recover();
            constUnion *unionArray = new constUnion[1];
            unionArray->setBConst(false);
            (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion(unionArray, TType(EbtBool, EbpUndefined, EvqConst), (yyvsp[(2) - (3)].lex).line);
        }
    ;}
    break;

  case 67:
#line 1096 "hlslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); ;}
    break;

  case 68:
#line 1097 "hlslang.y"
    {
       if (parseContext.boolOrVectorErrorCheck((yyvsp[(2) - (5)].lex).line, (yyvsp[(1) - (5)].interm.intermTypedNode)))
            parseContext.recover();
       
		(yyval.interm.intermTypedNode) = parseContext.intermediate.addSelection((yyvsp[(1) - (5)].interm.intermTypedNode), (yyvsp[(3) - (5)].interm.intermTypedNode), (yyvsp[(5) - (5)].interm.intermTypedNode), (yyvsp[(2) - (5)].lex).line);
           
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.binaryOpError((yyvsp[(2) - (5)].lex).line, ":", (yyvsp[(3) - (5)].interm.intermTypedNode)->getCompleteString(), (yyvsp[(5) - (5)].interm.intermTypedNode)->getCompleteString());
            parseContext.recover();
            (yyval.interm.intermTypedNode) = (yyvsp[(5) - (5)].interm.intermTypedNode);
        }
    ;}
    break;

  case 69:
#line 1112 "hlslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); ;}
    break;

  case 70:
#line 1113 "hlslang.y"
    {        
        if (parseContext.lValueErrorCheck((yyvsp[(2) - (3)].interm).line, "assign", (yyvsp[(1) - (3)].interm.intermTypedNode)))
            parseContext.recover();
        (yyval.interm.intermTypedNode) = parseContext.addAssign((yyvsp[(2) - (3)].interm).op, (yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode), (yyvsp[(2) - (3)].interm).line);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.assignError((yyvsp[(2) - (3)].interm).line, "assign", (yyvsp[(1) - (3)].interm.intermTypedNode)->getCompleteString(), (yyvsp[(3) - (3)].interm.intermTypedNode)->getCompleteString());
            parseContext.recover();
            (yyval.interm.intermTypedNode) = (yyvsp[(1) - (3)].interm.intermTypedNode);
        } else if (((yyvsp[(1) - (3)].interm.intermTypedNode)->isArray() || (yyvsp[(3) - (3)].interm.intermTypedNode)->isArray()))
            parseContext.recover();
    ;}
    break;

  case 71:
#line 1127 "hlslang.y"
    {                                    (yyval.interm).line = (yyvsp[(1) - (1)].lex).line; (yyval.interm).op = EOpAssign; ;}
    break;

  case 72:
#line 1128 "hlslang.y"
    { FRAG_VERT_ONLY("*=", (yyvsp[(1) - (1)].lex).line);     (yyval.interm).line = (yyvsp[(1) - (1)].lex).line; (yyval.interm).op = EOpMulAssign; ;}
    break;

  case 73:
#line 1129 "hlslang.y"
    { FRAG_VERT_ONLY("/=", (yyvsp[(1) - (1)].lex).line);     (yyval.interm).line = (yyvsp[(1) - (1)].lex).line; (yyval.interm).op = EOpDivAssign; ;}
    break;

  case 74:
#line 1130 "hlslang.y"
    { UNSUPPORTED_FEATURE("%=", (yyvsp[(1) - (1)].lex).line);   (yyval.interm).line = (yyvsp[(1) - (1)].lex).line; (yyval.interm).op = EOpModAssign; ;}
    break;

  case 75:
#line 1131 "hlslang.y"
    {                                    (yyval.interm).line = (yyvsp[(1) - (1)].lex).line; (yyval.interm).op = EOpAddAssign; ;}
    break;

  case 76:
#line 1132 "hlslang.y"
    {                                    (yyval.interm).line = (yyvsp[(1) - (1)].lex).line; (yyval.interm).op = EOpSubAssign; ;}
    break;

  case 77:
#line 1133 "hlslang.y"
    { UNSUPPORTED_FEATURE("<<=", (yyvsp[(1) - (1)].lex).line);  (yyval.interm).line = (yyvsp[(1) - (1)].lex).line; (yyval.interm).op = EOpLeftShiftAssign; ;}
    break;

  case 78:
#line 1134 "hlslang.y"
    { UNSUPPORTED_FEATURE("<<=", (yyvsp[(1) - (1)].lex).line);  (yyval.interm).line = (yyvsp[(1) - (1)].lex).line; (yyval.interm).op = EOpRightShiftAssign; ;}
    break;

  case 79:
#line 1135 "hlslang.y"
    { UNSUPPORTED_FEATURE("&=",  (yyvsp[(1) - (1)].lex).line);  (yyval.interm).line = (yyvsp[(1) - (1)].lex).line; (yyval.interm).op = EOpAndAssign; ;}
    break;

  case 80:
#line 1136 "hlslang.y"
    { UNSUPPORTED_FEATURE("^=",  (yyvsp[(1) - (1)].lex).line);  (yyval.interm).line = (yyvsp[(1) - (1)].lex).line; (yyval.interm).op = EOpExclusiveOrAssign; ;}
    break;

  case 81:
#line 1137 "hlslang.y"
    { UNSUPPORTED_FEATURE("|=",  (yyvsp[(1) - (1)].lex).line);  (yyval.interm).line = (yyvsp[(1) - (1)].lex).line; (yyval.interm).op = EOpInclusiveOrAssign; ;}
    break;

  case 82:
#line 1141 "hlslang.y"
    {
        (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode);
    ;}
    break;

  case 83:
#line 1144 "hlslang.y"
    {
        (yyval.interm.intermTypedNode) = parseContext.intermediate.addComma((yyvsp[(1) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode), (yyvsp[(2) - (3)].lex).line);
        if ((yyval.interm.intermTypedNode) == 0) {
            parseContext.binaryOpError((yyvsp[(2) - (3)].lex).line, ",", (yyvsp[(1) - (3)].interm.intermTypedNode)->getCompleteString(), (yyvsp[(3) - (3)].interm.intermTypedNode)->getCompleteString());
            parseContext.recover();
            (yyval.interm.intermTypedNode) = (yyvsp[(3) - (3)].interm.intermTypedNode);
        }
    ;}
    break;

  case 84:
#line 1155 "hlslang.y"
    {
        if (parseContext.constErrorCheck((yyvsp[(1) - (1)].interm.intermTypedNode)))
            parseContext.recover();
        (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode);
    ;}
    break;

  case 85:
#line 1163 "hlslang.y"
    { (yyval.interm.intermNode) = 0; ;}
    break;

  case 86:
#line 1164 "hlslang.y"
    { 
        if ((yyvsp[(1) - (2)].interm).intermAggregate)
            (yyvsp[(1) - (2)].interm).intermAggregate->setOperator(EOpSequence); 
        (yyval.interm.intermNode) = (yyvsp[(1) - (2)].interm).intermAggregate; 
    ;}
    break;

  case 87:
#line 1172 "hlslang.y"
    {
        //
        // Multiple declarations of the same function are allowed.
        //
        // If this is a definition, the definition production code will check for redefinitions 
        // (we don't know at this point if it's a definition or not).
        //
        // Redeclarations are allowed.  But, return types and parameter qualifiers must match.
        //        
        TFunction* prevDec = static_cast<TFunction*>(parseContext.symbolTable.find((yyvsp[(1) - (2)].interm.function)->getMangledName()));
        if (prevDec) {
            if (prevDec->getReturnType() != (yyvsp[(1) - (2)].interm.function)->getReturnType()) {
                parseContext.error((yyvsp[(2) - (2)].lex).line, "overloaded functions must have the same return type", (yyvsp[(1) - (2)].interm.function)->getReturnType().getBasicString(), "");
                parseContext.recover();
            }
            for (int i = 0; i < prevDec->getParamCount(); ++i) {
                if ((*prevDec)[i].type->getQualifier() != (*(yyvsp[(1) - (2)].interm.function))[i].type->getQualifier()) {
                    parseContext.error((yyvsp[(2) - (2)].lex).line, "overloaded functions must have the same parameter qualifiers", (*(yyvsp[(1) - (2)].interm.function))[i].type->getQualifierString(), "");
                    parseContext.recover();
                }
            }
        }
        
        //
        // If this is a redeclaration, it could also be a definition,
        // in which case, we want to use the variable names from this one, and not the one that's
        // being redeclared.  So, pass back up this declaration, not the one in the symbol table.
        //
        (yyval.interm).function = (yyvsp[(1) - (2)].interm.function);
        (yyval.interm).line = (yyvsp[(2) - (2)].lex).line;

        parseContext.symbolTable.insert(*(yyval.interm).function);
    ;}
    break;

  case 88:
#line 1205 "hlslang.y"
    {
        //
        // Multiple declarations of the same function are allowed.
        //
        // If this is a definition, the definition production code will check for redefinitions 
        // (we don't know at this point if it's a definition or not).
        //
        // Redeclarations are allowed.  But, return types and parameter qualifiers must match.
        //        
        TFunction* prevDec = static_cast<TFunction*>(parseContext.symbolTable.find((yyvsp[(1) - (4)].interm.function)->getMangledName()));
        if (prevDec) {
            if (prevDec->getReturnType() != (yyvsp[(1) - (4)].interm.function)->getReturnType()) {
                parseContext.error((yyvsp[(2) - (4)].lex).line, "overloaded functions must have the same return type", (yyvsp[(1) - (4)].interm.function)->getReturnType().getBasicString(), "");
                parseContext.recover();
            }
            for (int i = 0; i < prevDec->getParamCount(); ++i) {
                if ((*prevDec)[i].type->getQualifier() != (*(yyvsp[(1) - (4)].interm.function))[i].type->getQualifier()) {
                    parseContext.error((yyvsp[(2) - (4)].lex).line, "overloaded functions must have the same parameter qualifiers", (*(yyvsp[(1) - (4)].interm.function))[i].type->getQualifierString(), "");
                    parseContext.recover();
                }
            }
        }
        
        //
        // If this is a redeclaration, it could also be a definition,
        // in which case, we want to use the variable names from this one, and not the one that's
        // being redeclared.  So, pass back up this declaration, not the one in the symbol table.
        //
        (yyval.interm).function = (yyvsp[(1) - (4)].interm.function);
        (yyval.interm).line = (yyvsp[(2) - (4)].lex).line;
        (yyval.interm).function->setInfo(new TTypeInfo(*(yyvsp[(4) - (4)].lex).string, 0));

        parseContext.symbolTable.insert(*(yyval.interm).function);
    ;}
    break;

  case 89:
#line 1242 "hlslang.y"
    {
        (yyval.interm.function) = (yyvsp[(1) - (1)].interm.function);
    ;}
    break;

  case 90:
#line 1245 "hlslang.y"
    { 
        (yyval.interm.function) = (yyvsp[(1) - (1)].interm.function);  
    ;}
    break;

  case 91:
#line 1252 "hlslang.y"
    {
        // Add the parameter 
        (yyval.interm.function) = (yyvsp[(1) - (2)].interm.function);
        if ((yyvsp[(2) - (2)].interm).param.type->getBasicType() != EbtVoid)
            (yyvsp[(1) - (2)].interm.function)->addParameter((yyvsp[(2) - (2)].interm).param);
        else
            delete (yyvsp[(2) - (2)].interm).param.type;
    ;}
    break;

  case 92:
#line 1260 "hlslang.y"
    {   
        //
        // Only first parameter of one-parameter functions can be void
        // The check for named parameters not being void is done in parameter_declarator 
        //
        if ((yyvsp[(3) - (3)].interm).param.type->getBasicType() == EbtVoid) {
            //
            // This parameter > first is void
            //
            parseContext.error((yyvsp[(2) - (3)].lex).line, "cannot be an argument type except for '(void)'", "void", "");
            parseContext.recover();
            delete (yyvsp[(3) - (3)].interm).param.type;
        } else {
            // Add the parameter 
            (yyval.interm.function) = (yyvsp[(1) - (3)].interm.function); 
            (yyvsp[(1) - (3)].interm.function)->addParameter((yyvsp[(3) - (3)].interm).param);
        }
    ;}
    break;

  case 93:
#line 1281 "hlslang.y"
    {
        if ((yyvsp[(1) - (3)].interm.type).qualifier != EvqGlobal && (yyvsp[(1) - (3)].interm.type).qualifier != EvqTemporary) {
            parseContext.error((yyvsp[(2) - (3)].lex).line, "no qualifiers allowed for function return", getQualifierString((yyvsp[(1) - (3)].interm.type).qualifier), "");
            parseContext.recover();
        }
        // make sure a sampler is not involved as well...
        if (parseContext.structQualifierErrorCheck((yyvsp[(2) - (3)].lex).line, (yyvsp[(1) - (3)].interm.type)))
            parseContext.recover();
        
        // Add the function as a prototype after parsing it (we do not support recursion) 
        TFunction *function;
        TType type((yyvsp[(1) - (3)].interm.type));
	const TString* mangled = 0;
	if ( *(yyvsp[(2) - (3)].lex).string == "main")
	    mangled = NewPoolTString( "xlat_main");
	else
	    mangled = (yyvsp[(2) - (3)].lex).string;

        function = new TFunction(mangled, type);
        (yyval.interm.function) = function;
    ;}
    break;

  case 94:
#line 1306 "hlslang.y"
    {
        if ((yyvsp[(1) - (2)].interm.type).type == EbtVoid) {
            parseContext.error((yyvsp[(2) - (2)].lex).line, "illegal use of type 'void'", (yyvsp[(2) - (2)].lex).string->c_str(), "");
            parseContext.recover();
        }
        if (parseContext.reservedErrorCheck((yyvsp[(2) - (2)].lex).line, *(yyvsp[(2) - (2)].lex).string))
            parseContext.recover();
        TParameter param = {(yyvsp[(2) - (2)].lex).string, 0, new TType((yyvsp[(1) - (2)].interm.type))};
        (yyval.interm).line = (yyvsp[(2) - (2)].lex).line;
        (yyval.interm).param = param; 
    ;}
    break;

  case 95:
#line 1317 "hlslang.y"
    {
        if ((yyvsp[(1) - (4)].interm.type).type == EbtVoid) {
            parseContext.error((yyvsp[(2) - (4)].lex).line, "illegal use of type 'void'", (yyvsp[(2) - (4)].lex).string->c_str(), "");
            parseContext.recover();
        }
        if (parseContext.reservedErrorCheck((yyvsp[(2) - (4)].lex).line, *(yyvsp[(2) - (4)].lex).string))
            parseContext.recover();
        TParameter param = {(yyvsp[(2) - (4)].lex).string, 0, new TType((yyvsp[(1) - (4)].interm.type))};
        (yyval.interm).line = (yyvsp[(2) - (4)].lex).line;
        (yyval.interm).param = param; 
        
        //TODO: add initializer support
    ;}
    break;

  case 96:
#line 1330 "hlslang.y"
    {
        // register is being ignored
        if ((yyvsp[(1) - (3)].interm.type).type == EbtVoid) {
            parseContext.error((yyvsp[(2) - (3)].lex).line, "illegal use of type 'void'", (yyvsp[(2) - (3)].lex).string->c_str(), "");
            parseContext.recover();
        }
        if (parseContext.reservedErrorCheck((yyvsp[(2) - (3)].lex).line, *(yyvsp[(2) - (3)].lex).string))
            parseContext.recover();
        TParameter param = {(yyvsp[(2) - (3)].lex).string, 0, new TType((yyvsp[(1) - (3)].interm.type))};
        (yyval.interm).line = (yyvsp[(2) - (3)].lex).line;
        (yyval.interm).param = param; 
    ;}
    break;

  case 97:
#line 1342 "hlslang.y"
    {
        //Parameter with semantic
        if ((yyvsp[(1) - (4)].interm.type).type == EbtVoid) {
            parseContext.error((yyvsp[(2) - (4)].lex).line, "illegal use of type 'void'", (yyvsp[(2) - (4)].lex).string->c_str(), "");
            parseContext.recover();
        }
        if (parseContext.reservedErrorCheck((yyvsp[(2) - (4)].lex).line, *(yyvsp[(2) - (4)].lex).string))
            parseContext.recover();
        TParameter param = {(yyvsp[(2) - (4)].lex).string, new TTypeInfo(*(yyvsp[(4) - (4)].lex).string, 0), new TType((yyvsp[(1) - (4)].interm.type))};
        (yyval.interm).line = (yyvsp[(2) - (4)].lex).line;
        (yyval.interm).param = param; 
    ;}
    break;

  case 98:
#line 1354 "hlslang.y"
    {
        // Check that we can make an array out of this type
        if (parseContext.arrayTypeErrorCheck((yyvsp[(3) - (5)].lex).line, (yyvsp[(1) - (5)].interm.type)))
            parseContext.recover();
            
        if (parseContext.reservedErrorCheck((yyvsp[(2) - (5)].lex).line, *(yyvsp[(2) - (5)].lex).string))
            parseContext.recover();
            
        int size;
        if (parseContext.arraySizeErrorCheck((yyvsp[(3) - (5)].lex).line, (yyvsp[(4) - (5)].interm.intermTypedNode), size))
            parseContext.recover();
        (yyvsp[(1) - (5)].interm.type).setArray(true, size);
             
        TType* type = new TType((yyvsp[(1) - (5)].interm.type));
        TParameter param = { (yyvsp[(2) - (5)].lex).string, 0, type };
        (yyval.interm).line = (yyvsp[(2) - (5)].lex).line;
        (yyval.interm).param = param;
    ;}
    break;

  case 99:
#line 1372 "hlslang.y"
    {
        // Check that we can make an array out of this type
        if (parseContext.arrayTypeErrorCheck((yyvsp[(3) - (7)].lex).line, (yyvsp[(1) - (7)].interm.type)))
            parseContext.recover();
            
        if (parseContext.reservedErrorCheck((yyvsp[(2) - (7)].lex).line, *(yyvsp[(2) - (7)].lex).string))
            parseContext.recover();
            
        int size;
        if (parseContext.arraySizeErrorCheck((yyvsp[(3) - (7)].lex).line, (yyvsp[(4) - (7)].interm.intermTypedNode), size))
            parseContext.recover();
        (yyvsp[(1) - (7)].interm.type).setArray(true, size);
             
        TType* type = new TType((yyvsp[(1) - (7)].interm.type));
        TParameter param = { (yyvsp[(2) - (7)].lex).string, new TTypeInfo(*(yyvsp[(7) - (7)].lex).string, 0), type };
        (yyval.interm).line = (yyvsp[(2) - (7)].lex).line;
        (yyval.interm).param = param;
    ;}
    break;

  case 100:
#line 1401 "hlslang.y"
    {
        (yyval.interm) = (yyvsp[(3) - (3)].interm);
        if (parseContext.paramErrorCheck((yyvsp[(3) - (3)].interm).line, (yyvsp[(1) - (3)].interm.type).qualifier, (yyvsp[(2) - (3)].interm.qualifier), (yyval.interm).param.type))
            parseContext.recover();
    ;}
    break;

  case 101:
#line 1406 "hlslang.y"
    {
        (yyval.interm) = (yyvsp[(2) - (2)].interm);
        if (parseContext.parameterSamplerErrorCheck((yyvsp[(2) - (2)].interm).line, (yyvsp[(1) - (2)].interm.qualifier), *(yyvsp[(2) - (2)].interm).param.type))
            parseContext.recover();
        if (parseContext.paramErrorCheck((yyvsp[(2) - (2)].interm).line, EvqTemporary, (yyvsp[(1) - (2)].interm.qualifier), (yyval.interm).param.type))
            parseContext.recover();
    ;}
    break;

  case 102:
#line 1416 "hlslang.y"
    {
        (yyval.interm) = (yyvsp[(3) - (3)].interm);
        if (parseContext.paramErrorCheck((yyvsp[(3) - (3)].interm).line, (yyvsp[(1) - (3)].interm.type).qualifier, (yyvsp[(2) - (3)].interm.qualifier), (yyval.interm).param.type))
            parseContext.recover();
    ;}
    break;

  case 103:
#line 1421 "hlslang.y"
    {
        (yyval.interm) = (yyvsp[(2) - (2)].interm);
        if (parseContext.parameterSamplerErrorCheck((yyvsp[(2) - (2)].interm).line, (yyvsp[(1) - (2)].interm.qualifier), *(yyvsp[(2) - (2)].interm).param.type))
            parseContext.recover();
        if (parseContext.paramErrorCheck((yyvsp[(2) - (2)].interm).line, EvqTemporary, (yyvsp[(1) - (2)].interm.qualifier), (yyval.interm).param.type))
            parseContext.recover();
    ;}
    break;

  case 104:
#line 1431 "hlslang.y"
    {
        (yyval.interm.qualifier) = EvqIn;
    ;}
    break;

  case 105:
#line 1434 "hlslang.y"
    {
        (yyval.interm.qualifier) = EvqIn;
    ;}
    break;

  case 106:
#line 1437 "hlslang.y"
    {
        (yyval.interm.qualifier) = EvqOut;
    ;}
    break;

  case 107:
#line 1440 "hlslang.y"
    {
        (yyval.interm.qualifier) = EvqInOut;
    ;}
    break;

  case 108:
#line 1446 "hlslang.y"
    {
        TParameter param = { 0, 0, new TType((yyvsp[(1) - (1)].interm.type)) };
        (yyval.interm).param = param;
    ;}
    break;

  case 109:
#line 1453 "hlslang.y"
    {
        (yyval.interm) = (yyvsp[(1) - (1)].interm);
    ;}
    break;

  case 110:
#line 1456 "hlslang.y"
    {
        (yyval.interm) = (yyvsp[(1) - (4)].interm);
        if (parseContext.structQualifierErrorCheck((yyvsp[(3) - (4)].lex).line, (yyval.interm).type))
            parseContext.recover();
        
        if (parseContext.nonInitConstErrorCheck((yyvsp[(3) - (4)].lex).line, *(yyvsp[(3) - (4)].lex).string, (yyval.interm).type))
            parseContext.recover();

        if (parseContext.nonInitErrorCheck((yyvsp[(3) - (4)].lex).line, *(yyvsp[(3) - (4)].lex).string, (yyvsp[(4) - (4)].interm.typeInfo), (yyval.interm).type))
            parseContext.recover();
    ;}
    break;

  case 111:
#line 1467 "hlslang.y"
    {
        if (parseContext.structQualifierErrorCheck((yyvsp[(3) - (6)].lex).line, (yyvsp[(1) - (6)].interm).type))
            parseContext.recover();
            
        if (parseContext.nonInitConstErrorCheck((yyvsp[(3) - (6)].lex).line, *(yyvsp[(3) - (6)].lex).string, (yyvsp[(1) - (6)].interm).type))
            parseContext.recover();

        (yyval.interm) = (yyvsp[(1) - (6)].interm);
        
        if (parseContext.arrayTypeErrorCheck((yyvsp[(4) - (6)].lex).line, (yyvsp[(1) - (6)].interm).type) || parseContext.arrayQualifierErrorCheck((yyvsp[(4) - (6)].lex).line, (yyvsp[(1) - (6)].interm).type))
            parseContext.recover();
        else {
            (yyvsp[(1) - (6)].interm).type.setArray(true);
            TVariable* variable;
            if (parseContext.arrayErrorCheck((yyvsp[(4) - (6)].lex).line, *(yyvsp[(3) - (6)].lex).string, (yyvsp[(6) - (6)].interm.typeInfo), (yyvsp[(1) - (6)].interm).type, variable))
                parseContext.recover();
        }
    ;}
    break;

  case 112:
#line 1485 "hlslang.y"
    {
        if (parseContext.structQualifierErrorCheck((yyvsp[(3) - (7)].lex).line, (yyvsp[(1) - (7)].interm).type))
            parseContext.recover();
            
        if (parseContext.nonInitConstErrorCheck((yyvsp[(3) - (7)].lex).line, *(yyvsp[(3) - (7)].lex).string, (yyvsp[(1) - (7)].interm).type))
            parseContext.recover();
        
        (yyval.interm) = (yyvsp[(1) - (7)].interm);

        if (parseContext.arrayTypeErrorCheck((yyvsp[(4) - (7)].lex).line, (yyvsp[(1) - (7)].interm).type) || parseContext.arrayQualifierErrorCheck((yyvsp[(4) - (7)].lex).line, (yyvsp[(1) - (7)].interm).type))
            parseContext.recover();
        else {
            int size;
            if (parseContext.arraySizeErrorCheck((yyvsp[(4) - (7)].lex).line, (yyvsp[(5) - (7)].interm.intermTypedNode), size))
                parseContext.recover();
            (yyvsp[(1) - (7)].interm).type.setArray(true, size);        
            TVariable* variable;
            if (parseContext.arrayErrorCheck((yyvsp[(4) - (7)].lex).line, *(yyvsp[(3) - (7)].lex).string, (yyvsp[(7) - (7)].interm.typeInfo), (yyvsp[(1) - (7)].interm).type, variable))
                parseContext.recover();
        }
    ;}
    break;

  case 113:
#line 1506 "hlslang.y"
    {
        if (parseContext.structQualifierErrorCheck((yyvsp[(3) - (8)].lex).line, (yyvsp[(1) - (8)].interm).type))
            parseContext.recover();
            
        (yyval.interm) = (yyvsp[(1) - (8)].interm);
            
        TVariable* variable = 0;
        if (parseContext.arrayTypeErrorCheck((yyvsp[(4) - (8)].lex).line, (yyvsp[(1) - (8)].interm).type) || parseContext.arrayQualifierErrorCheck((yyvsp[(4) - (8)].lex).line, (yyvsp[(1) - (8)].interm).type))
            parseContext.recover();
        else {
			(yyvsp[(1) - (8)].interm).type.setArray(true, (yyvsp[(8) - (8)].interm.intermTypedNode)->getType().getArraySize());
            if (parseContext.arrayErrorCheck((yyvsp[(4) - (8)].lex).line, *(yyvsp[(3) - (8)].lex).string, (yyvsp[(1) - (8)].interm).type, variable))
                parseContext.recover();
        }

        {
            TIntermNode* intermNode;
            if (!parseContext.executeInitializer((yyvsp[(3) - (8)].lex).line, *(yyvsp[(3) - (8)].lex).string, (yyvsp[(6) - (8)].interm.typeInfo), (yyvsp[(1) - (8)].interm).type, (yyvsp[(8) - (8)].interm.intermTypedNode), intermNode, variable)) {
                //
                // build the intermediate representation
                //
                if (intermNode)
                    (yyval.interm).intermAggregate = parseContext.intermediate.growAggregate((yyvsp[(1) - (8)].interm).intermNode, intermNode, (yyvsp[(7) - (8)].lex).line);
                else
                    (yyval.interm).intermAggregate = (yyvsp[(1) - (8)].interm).intermAggregate;
            } else {
                parseContext.recover();
                (yyval.interm).intermAggregate = 0;
            }
        }
    ;}
    break;

  case 114:
#line 1537 "hlslang.y"
    {
        if (parseContext.structQualifierErrorCheck((yyvsp[(3) - (9)].lex).line, (yyvsp[(1) - (9)].interm).type))
            parseContext.recover();
            
        (yyval.interm) = (yyvsp[(1) - (9)].interm);
            
        TVariable* variable = 0;
        if (parseContext.arrayTypeErrorCheck((yyvsp[(4) - (9)].lex).line, (yyvsp[(1) - (9)].interm).type) || parseContext.arrayQualifierErrorCheck((yyvsp[(4) - (9)].lex).line, (yyvsp[(1) - (9)].interm).type))
            parseContext.recover();
        else {
            int size;
            if (parseContext.arraySizeErrorCheck((yyvsp[(4) - (9)].lex).line, (yyvsp[(5) - (9)].interm.intermTypedNode), size))
                parseContext.recover();
            (yyvsp[(1) - (9)].interm).type.setArray(true, size);
            if (parseContext.arrayErrorCheck((yyvsp[(4) - (9)].lex).line, *(yyvsp[(3) - (9)].lex).string, (yyvsp[(7) - (9)].interm.typeInfo), (yyvsp[(1) - (9)].interm).type, variable))
                parseContext.recover();
        }

        {
            TIntermNode* intermNode;
            if (!parseContext.executeInitializer((yyvsp[(3) - (9)].lex).line, *(yyvsp[(3) - (9)].lex).string, (yyvsp[(7) - (9)].interm.typeInfo), (yyvsp[(1) - (9)].interm).type, (yyvsp[(9) - (9)].interm.intermTypedNode), intermNode, variable)) {
                //
                // build the intermediate representation
                //
                if (intermNode)
                    (yyval.interm).intermAggregate = parseContext.intermediate.growAggregate((yyvsp[(1) - (9)].interm).intermNode, intermNode, (yyvsp[(8) - (9)].lex).line);
                else
                    (yyval.interm).intermAggregate = (yyvsp[(1) - (9)].interm).intermAggregate;
            } else {
                parseContext.recover();
                (yyval.interm).intermAggregate = 0;
            }
        }
    ;}
    break;

  case 115:
#line 1571 "hlslang.y"
    {
        if (parseContext.structQualifierErrorCheck((yyvsp[(3) - (6)].lex).line, (yyvsp[(1) - (6)].interm).type))
            parseContext.recover();
        
        (yyval.interm) = (yyvsp[(1) - (6)].interm);
        
        TIntermNode* intermNode;
	if ( !IsSampler((yyvsp[(1) - (6)].interm).type.type)) {
	    if (!parseContext.executeInitializer((yyvsp[(3) - (6)].lex).line, *(yyvsp[(3) - (6)].lex).string, (yyvsp[(4) - (6)].interm.typeInfo), (yyvsp[(1) - (6)].interm).type, (yyvsp[(6) - (6)].interm.intermTypedNode), intermNode)) {
		//
		// build the intermediate representation
		//
		if (intermNode)
		    (yyval.interm).intermAggregate = parseContext.intermediate.growAggregate((yyvsp[(1) - (6)].interm).intermNode, intermNode, (yyvsp[(5) - (6)].lex).line);
		else
		    (yyval.interm).intermAggregate = (yyvsp[(1) - (6)].interm).intermAggregate;
	    } else {
		parseContext.recover();
		(yyval.interm).intermAggregate = 0;
	    }
	}
	else {
	    //Special code to skip initializers for samplers
	    (yyval.interm) = (yyvsp[(1) - (6)].interm);
	    if (parseContext.structQualifierErrorCheck((yyvsp[(3) - (6)].lex).line, (yyval.interm).type))
		parseContext.recover();
	    
	    if (parseContext.nonInitConstErrorCheck((yyvsp[(3) - (6)].lex).line, *(yyvsp[(3) - (6)].lex).string, (yyval.interm).type))
		parseContext.recover();
	    
	    if (parseContext.nonInitErrorCheck((yyvsp[(3) - (6)].lex).line, *(yyvsp[(3) - (6)].lex).string, (yyvsp[(4) - (6)].interm.typeInfo), (yyval.interm).type))
		parseContext.recover();
	}
    ;}
    break;

  case 116:
#line 1608 "hlslang.y"
    {
        (yyval.interm).type = (yyvsp[(1) - (1)].interm.type);
        (yyval.interm).intermAggregate = 0;
    ;}
    break;

  case 117:
#line 1612 "hlslang.y"
    {
        (yyval.interm).intermAggregate = 0;
        (yyval.interm).type = (yyvsp[(1) - (3)].interm.type);

        if (parseContext.structQualifierErrorCheck((yyvsp[(2) - (3)].lex).line, (yyval.interm).type))
            parseContext.recover();
        
        if (parseContext.nonInitConstErrorCheck((yyvsp[(2) - (3)].lex).line, *(yyvsp[(2) - (3)].lex).string, (yyval.interm).type))
            parseContext.recover();

        if (parseContext.nonInitErrorCheck((yyvsp[(2) - (3)].lex).line, *(yyvsp[(2) - (3)].lex).string, (yyvsp[(3) - (3)].interm.typeInfo), (yyval.interm).type))
            parseContext.recover();
    ;}
    break;

  case 118:
#line 1625 "hlslang.y"
    {
        (yyval.interm).intermAggregate = 0;
        if (parseContext.structQualifierErrorCheck((yyvsp[(2) - (5)].lex).line, (yyvsp[(1) - (5)].interm.type)))
            parseContext.recover();

        if (parseContext.nonInitConstErrorCheck((yyvsp[(2) - (5)].lex).line, *(yyvsp[(2) - (5)].lex).string, (yyvsp[(1) - (5)].interm.type)))
            parseContext.recover();

        (yyval.interm).type = (yyvsp[(1) - (5)].interm.type);

        if (parseContext.arrayTypeErrorCheck((yyvsp[(3) - (5)].lex).line, (yyvsp[(1) - (5)].interm.type)) || parseContext.arrayQualifierErrorCheck((yyvsp[(3) - (5)].lex).line, (yyvsp[(1) - (5)].interm.type)))
            parseContext.recover();
        else {
            (yyvsp[(1) - (5)].interm.type).setArray(true);        
            TVariable* variable;
            if (parseContext.arrayErrorCheck((yyvsp[(3) - (5)].lex).line, *(yyvsp[(2) - (5)].lex).string, (yyvsp[(5) - (5)].interm.typeInfo), (yyvsp[(1) - (5)].interm.type), variable))
                parseContext.recover();
        }
    ;}
    break;

  case 119:
#line 1644 "hlslang.y"
    {
        (yyval.interm).intermAggregate = 0;
        if (parseContext.structQualifierErrorCheck((yyvsp[(2) - (6)].lex).line, (yyvsp[(1) - (6)].interm.type)))
            parseContext.recover();

        if (parseContext.nonInitConstErrorCheck((yyvsp[(2) - (6)].lex).line, *(yyvsp[(2) - (6)].lex).string, (yyvsp[(1) - (6)].interm.type)))
            parseContext.recover();
            
        (yyval.interm).type = (yyvsp[(1) - (6)].interm.type);

        if (parseContext.arrayTypeErrorCheck((yyvsp[(3) - (6)].lex).line, (yyvsp[(1) - (6)].interm.type)) || parseContext.arrayQualifierErrorCheck((yyvsp[(3) - (6)].lex).line, (yyvsp[(1) - (6)].interm.type)))
            parseContext.recover();
        else {
            int size;
            if (parseContext.arraySizeErrorCheck((yyvsp[(3) - (6)].lex).line, (yyvsp[(4) - (6)].interm.intermTypedNode), size))
                parseContext.recover();
            
            (yyvsp[(1) - (6)].interm.type).setArray(true, size);
            TVariable* variable;
            if (parseContext.arrayErrorCheck((yyvsp[(3) - (6)].lex).line, *(yyvsp[(2) - (6)].lex).string, (yyvsp[(6) - (6)].interm.typeInfo), (yyvsp[(1) - (6)].interm.type), variable))
                parseContext.recover();
        }
    ;}
    break;

  case 120:
#line 1667 "hlslang.y"
    {
        (yyval.interm).intermAggregate = 0;

        if (parseContext.structQualifierErrorCheck((yyvsp[(2) - (7)].lex).line, (yyvsp[(1) - (7)].interm.type)))
            parseContext.recover();

        (yyval.interm).type = (yyvsp[(1) - (7)].interm.type);

        TVariable* variable = 0;
        if (parseContext.arrayTypeErrorCheck((yyvsp[(3) - (7)].lex).line, (yyvsp[(1) - (7)].interm.type)) || parseContext.arrayQualifierErrorCheck((yyvsp[(3) - (7)].lex).line, (yyvsp[(1) - (7)].interm.type)))
            parseContext.recover();
        else {
            (yyvsp[(1) - (7)].interm.type).setArray(true, (yyvsp[(7) - (7)].interm.intermTypedNode)->getType().getArraySize());
            if (parseContext.arrayErrorCheck((yyvsp[(3) - (7)].lex).line, *(yyvsp[(2) - (7)].lex).string, (yyvsp[(5) - (7)].interm.typeInfo), (yyvsp[(1) - (7)].interm.type), variable))
                parseContext.recover();
        }

        
	     {        
            TIntermNode* intermNode;
            if (!parseContext.executeInitializer((yyvsp[(2) - (7)].lex).line, *(yyvsp[(2) - (7)].lex).string, (yyvsp[(5) - (7)].interm.typeInfo), (yyvsp[(1) - (7)].interm.type), (yyvsp[(7) - (7)].interm.intermTypedNode), intermNode, variable)) {
                //
                // Build intermediate representation
                //
                if (intermNode)
                    (yyval.interm).intermAggregate = parseContext.intermediate.makeAggregate(intermNode, (yyvsp[(6) - (7)].lex).line);
                else
                    (yyval.interm).intermAggregate = 0;
            } else {
                parseContext.recover();
                (yyval.interm).intermAggregate = 0;
            }
        }
    ;}
    break;

  case 121:
#line 1701 "hlslang.y"
    {
        (yyval.interm).intermAggregate = 0;

        if (parseContext.structQualifierErrorCheck((yyvsp[(2) - (8)].lex).line, (yyvsp[(1) - (8)].interm.type)))
            parseContext.recover();

        (yyval.interm).type = (yyvsp[(1) - (8)].interm.type);

        TVariable* variable = 0;
        if (parseContext.arrayTypeErrorCheck((yyvsp[(3) - (8)].lex).line, (yyvsp[(1) - (8)].interm.type)) || parseContext.arrayQualifierErrorCheck((yyvsp[(3) - (8)].lex).line, (yyvsp[(1) - (8)].interm.type)))
            parseContext.recover();
        else {
            int size;
            if (parseContext.arraySizeErrorCheck((yyvsp[(3) - (8)].lex).line, (yyvsp[(4) - (8)].interm.intermTypedNode), size))
                parseContext.recover();
            
            (yyvsp[(1) - (8)].interm.type).setArray(true, size);
            if (parseContext.arrayErrorCheck((yyvsp[(3) - (8)].lex).line, *(yyvsp[(2) - (8)].lex).string, (yyvsp[(6) - (8)].interm.typeInfo), (yyvsp[(1) - (8)].interm.type), variable))
                parseContext.recover();
        }
        
        {        
            TIntermNode* intermNode;
            if (!parseContext.executeInitializer((yyvsp[(2) - (8)].lex).line, *(yyvsp[(2) - (8)].lex).string, (yyvsp[(6) - (8)].interm.typeInfo), (yyvsp[(1) - (8)].interm.type), (yyvsp[(8) - (8)].interm.intermTypedNode), intermNode, variable)) {
                //
                // Build intermediate representation
                //
                if (intermNode)
                    (yyval.interm).intermAggregate = parseContext.intermediate.makeAggregate(intermNode, (yyvsp[(7) - (8)].lex).line);
                else
                    (yyval.interm).intermAggregate = 0;
            } else {
                parseContext.recover();
                (yyval.interm).intermAggregate = 0;
            }
        }        
    ;}
    break;

  case 122:
#line 1738 "hlslang.y"
    {
        if (parseContext.structQualifierErrorCheck((yyvsp[(2) - (5)].lex).line, (yyvsp[(1) - (5)].interm.type)))
            parseContext.recover();

        (yyval.interm).type = (yyvsp[(1) - (5)].interm.type);

        TIntermNode* intermNode;
	if ( !IsSampler((yyvsp[(1) - (5)].interm.type).type)) {
	    if (!parseContext.executeInitializer((yyvsp[(2) - (5)].lex).line, *(yyvsp[(2) - (5)].lex).string, (yyvsp[(3) - (5)].interm.typeInfo), (yyvsp[(1) - (5)].interm.type), (yyvsp[(5) - (5)].interm.intermTypedNode), intermNode)) {
		//
		// Build intermediate representation
		//
		if (intermNode)
		    (yyval.interm).intermAggregate = parseContext.intermediate.makeAggregate(intermNode, (yyvsp[(4) - (5)].lex).line);
		else
		    (yyval.interm).intermAggregate = 0;
	    } else {
		parseContext.recover();
		(yyval.interm).intermAggregate = 0;
	    }
	}
	else {
	    //Skip sampler initializers for now
	    (yyval.interm).intermAggregate = 0;

	    if (parseContext.structQualifierErrorCheck((yyvsp[(2) - (5)].lex).line, (yyval.interm).type))
		parseContext.recover();
	    
	    if (parseContext.nonInitConstErrorCheck((yyvsp[(2) - (5)].lex).line, *(yyvsp[(2) - (5)].lex).string, (yyval.interm).type))
		parseContext.recover();
	    
	    if (parseContext.nonInitErrorCheck((yyvsp[(2) - (5)].lex).line, *(yyvsp[(2) - (5)].lex).string, (yyvsp[(3) - (5)].interm.typeInfo), (yyval.interm).type))
		parseContext.recover();
	}
    ;}
    break;

  case 123:
#line 1789 "hlslang.y"
    {
        (yyval.interm.type) = (yyvsp[(1) - (1)].interm.type);                       
    ;}
    break;

  case 124:
#line 1792 "hlslang.y"
    {                
        if ((yyvsp[(2) - (2)].interm.type).array && parseContext.arrayQualifierErrorCheck((yyvsp[(2) - (2)].interm.type).line, (yyvsp[(1) - (2)].interm.type))) {
            parseContext.recover();
            (yyvsp[(2) - (2)].interm.type).setArray(false);
        }
        
        if ((yyvsp[(1) - (2)].interm.type).qualifier == EvqAttribute &&
            ((yyvsp[(2) - (2)].interm.type).type == EbtBool || (yyvsp[(2) - (2)].interm.type).type == EbtInt)) {
            parseContext.error((yyvsp[(2) - (2)].interm.type).line, "cannot be bool or int", getQualifierString((yyvsp[(1) - (2)].interm.type).qualifier), "");
            parseContext.recover();
        }
        if (((yyvsp[(1) - (2)].interm.type).qualifier == EvqVaryingIn || (yyvsp[(1) - (2)].interm.type).qualifier == EvqVaryingOut) &&
            ((yyvsp[(2) - (2)].interm.type).type == EbtBool || (yyvsp[(2) - (2)].interm.type).type == EbtInt)) {
            parseContext.error((yyvsp[(2) - (2)].interm.type).line, "cannot be bool or int", getQualifierString((yyvsp[(1) - (2)].interm.type).qualifier), "");
            parseContext.recover();
        }
        (yyval.interm.type) = (yyvsp[(2) - (2)].interm.type); 
        (yyval.interm.type).qualifier = (yyvsp[(1) - (2)].interm.type).qualifier;
    ;}
    break;

  case 125:
#line 1814 "hlslang.y"
    {
        (yyval.interm.type).setBasic(EbtVoid, EvqConst, (yyvsp[(1) - (1)].lex).line);
    ;}
    break;

  case 126:
#line 1817 "hlslang.y"
    {
        if (parseContext.globalErrorCheck((yyvsp[(1) - (1)].lex).line, parseContext.symbolTable.atGlobalLevel(), "static"))
            parseContext.recover();
        (yyval.interm.type).setBasic(EbtVoid, EvqStatic, (yyvsp[(1) - (1)].lex).line);
    ;}
    break;

  case 127:
#line 1822 "hlslang.y"
    {
        if (parseContext.globalErrorCheck((yyvsp[(1) - (2)].lex).line, parseContext.symbolTable.atGlobalLevel(), "static const"))
            parseContext.recover();
        (yyval.interm.type).setBasic(EbtVoid, EvqStaticConst, (yyvsp[(1) - (2)].lex).line);
    ;}
    break;

  case 128:
#line 1827 "hlslang.y"
    { 
        VERTEX_ONLY("attribute", (yyvsp[(1) - (1)].lex).line);
        if (parseContext.globalErrorCheck((yyvsp[(1) - (1)].lex).line, parseContext.symbolTable.atGlobalLevel(), "attribute"))
            parseContext.recover();
        (yyval.interm.type).setBasic(EbtVoid, EvqAttribute, (yyvsp[(1) - (1)].lex).line);
    ;}
    break;

  case 129:
#line 1833 "hlslang.y"
    {
        if (parseContext.globalErrorCheck((yyvsp[(1) - (1)].lex).line, parseContext.symbolTable.atGlobalLevel(), "varying"))
            parseContext.recover();
        if (parseContext.language == EShLangVertex)
            (yyval.interm.type).setBasic(EbtVoid, EvqVaryingOut, (yyvsp[(1) - (1)].lex).line);
        else
            (yyval.interm.type).setBasic(EbtVoid, EvqVaryingIn, (yyvsp[(1) - (1)].lex).line);
    ;}
    break;

  case 130:
#line 1841 "hlslang.y"
    {
        if (parseContext.globalErrorCheck((yyvsp[(1) - (1)].lex).line, parseContext.symbolTable.atGlobalLevel(), "uniform"))
            parseContext.recover();
        (yyval.interm.type).setBasic(EbtVoid, EvqUniform, (yyvsp[(1) - (1)].lex).line);
    ;}
    break;

  case 131:
#line 1849 "hlslang.y"
    {
        (yyval.interm.type) = (yyvsp[(1) - (1)].interm.type);
    ;}
    break;

  case 132:
#line 1852 "hlslang.y"
    {
        (yyval.interm.type) = (yyvsp[(1) - (4)].interm.type);
        
        if (parseContext.arrayTypeErrorCheck((yyvsp[(2) - (4)].lex).line, (yyvsp[(1) - (4)].interm.type)))
            parseContext.recover();
        else {
            int size;
            if (parseContext.arraySizeErrorCheck((yyvsp[(2) - (4)].lex).line, (yyvsp[(3) - (4)].interm.intermTypedNode), size))
                parseContext.recover();
            (yyval.interm.type).setArray(true, size);
        }
    ;}
    break;

  case 133:
#line 1867 "hlslang.y"
    {
        SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtVoid,EbpUndefined);
    ;}
    break;

  case 134:
#line 1870 "hlslang.y"
    {
        SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtFloat,EbpHigh);
    ;}
    break;

  case 135:
#line 1873 "hlslang.y"
    {
        SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtFloat,EbpMedium);
    ;}
    break;

  case 136:
#line 1876 "hlslang.y"
    {
        SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtFloat,EbpLow);
    ;}
    break;

  case 137:
#line 1879 "hlslang.y"
    {
        SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtInt,EbpHigh);
    ;}
    break;

  case 138:
#line 1882 "hlslang.y"
    {
        SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtBool,EbpHigh);
    ;}
    break;

  case 139:
#line 1885 "hlslang.y"
    {
        TQualifier qual = parseContext.getDefaultQualifier();
        if ( (yyvsp[(5) - (6)].lex).i > 4 || (yyvsp[(5) - (6)].lex).i < 1 ) {
            parseContext.error((yyvsp[(2) - (6)].lex).line, "vector dimension out of range", "", "");
            parseContext.recover();
            (yyval.interm.type).setBasic(EbtFloat, qual, (yyvsp[(1) - (6)].lex).line);
        } else {
            (yyval.interm.type).setBasic(EbtFloat, qual, (yyvsp[(1) - (6)].lex).line);
            (yyval.interm.type).setAggregate((yyvsp[(5) - (6)].lex).i);
        }
    ;}
    break;

  case 140:
#line 1896 "hlslang.y"
    {
        TQualifier qual = parseContext.getDefaultQualifier();
        if ( (yyvsp[(5) - (6)].lex).i > 4 || (yyvsp[(5) - (6)].lex).i < 1 ) {
            parseContext.error((yyvsp[(2) - (6)].lex).line, "vector dimension out of range", "", "");
            parseContext.recover();
            (yyval.interm.type).setBasic(EbtInt, qual, (yyvsp[(1) - (6)].lex).line);
        } else {
            (yyval.interm.type).setBasic(EbtInt, qual, (yyvsp[(1) - (6)].lex).line);
            (yyval.interm.type).setAggregate((yyvsp[(5) - (6)].lex).i);
        }
    ;}
    break;

  case 141:
#line 1907 "hlslang.y"
    {
        TQualifier qual = parseContext.getDefaultQualifier();
        if ( (yyvsp[(5) - (6)].lex).i > 4 || (yyvsp[(5) - (6)].lex).i < 1 ) {
            parseContext.error((yyvsp[(2) - (6)].lex).line, "vector dimension out of range", "", "");
            parseContext.recover();
            (yyval.interm.type).setBasic(EbtBool, qual, (yyvsp[(1) - (6)].lex).line);
        } else {
            (yyval.interm.type).setBasic(EbtBool, qual, (yyvsp[(1) - (6)].lex).line);
            (yyval.interm.type).setAggregate((yyvsp[(5) - (6)].lex).i);
        }
    ;}
    break;

  case 142:
#line 1918 "hlslang.y"
    {
        SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtFloat,EbpHigh);
        (yyval.interm.type).setAggregate(2);
    ;}
    break;

  case 143:
#line 1922 "hlslang.y"
    {
        SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtFloat,EbpHigh);
        (yyval.interm.type).setAggregate(3);
    ;}
    break;

  case 144:
#line 1926 "hlslang.y"
    {
        SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtFloat,EbpHigh);
        (yyval.interm.type).setAggregate(4);
    ;}
    break;

  case 145:
#line 1930 "hlslang.y"
    {
        SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtFloat,EbpMedium);
        (yyval.interm.type).setAggregate(2);
    ;}
    break;

  case 146:
#line 1934 "hlslang.y"
    {
        SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtFloat,EbpMedium);
        (yyval.interm.type).setAggregate(3);
    ;}
    break;

  case 147:
#line 1938 "hlslang.y"
    {
        SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtFloat,EbpMedium);
        (yyval.interm.type).setAggregate(4);
    ;}
    break;

  case 148:
#line 1942 "hlslang.y"
    {
        SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtFloat,EbpLow);
        (yyval.interm.type).setAggregate(2);
    ;}
    break;

  case 149:
#line 1946 "hlslang.y"
    {
        SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtFloat,EbpLow);
        (yyval.interm.type).setAggregate(3);
    ;}
    break;

  case 150:
#line 1950 "hlslang.y"
    {
        SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtFloat,EbpLow);
        (yyval.interm.type).setAggregate(4);
    ;}
    break;

  case 151:
#line 1954 "hlslang.y"
    {
        SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtBool,EbpHigh);
        (yyval.interm.type).setAggregate(2);
    ;}
    break;

  case 152:
#line 1958 "hlslang.y"
    {
        SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtBool,EbpHigh);
        (yyval.interm.type).setAggregate(3);
    ;}
    break;

  case 153:
#line 1962 "hlslang.y"
    {
        SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtBool,EbpHigh);
        (yyval.interm.type).setAggregate(4);
    ;}
    break;

  case 154:
#line 1966 "hlslang.y"
    {
        SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtInt,EbpHigh);
        (yyval.interm.type).setAggregate(2);
    ;}
    break;

  case 155:
#line 1970 "hlslang.y"
    {
        SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtInt,EbpHigh);
        (yyval.interm.type).setAggregate(3);
    ;}
    break;

  case 156:
#line 1974 "hlslang.y"
    {
        SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtInt,EbpHigh);
        (yyval.interm.type).setAggregate(4);
    ;}
    break;

  case 157:
#line 1978 "hlslang.y"
    {
        FRAG_VERT_ONLY("mat2", (yyvsp[(1) - (1)].lex).line); 
        SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtFloat,EbpHigh);
        (yyval.interm.type).setAggregate(2, true);
    ;}
    break;

  case 158:
#line 1983 "hlslang.y"
    { 
        FRAG_VERT_ONLY("mat3", (yyvsp[(1) - (1)].lex).line); 
        SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtFloat,EbpHigh);
        (yyval.interm.type).setAggregate(3, true);
    ;}
    break;

  case 159:
#line 1988 "hlslang.y"
    { 
        FRAG_VERT_ONLY("mat4", (yyvsp[(1) - (1)].lex).line);
        SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtFloat,EbpHigh);
        (yyval.interm.type).setAggregate(4, true);
    ;}
    break;

  case 160:
#line 1993 "hlslang.y"
    {
		FRAG_VERT_ONLY("mat2", (yyvsp[(1) - (1)].lex).line);
		SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtFloat,EbpMedium);
		(yyval.interm.type).setAggregate(2, true);
	;}
    break;

  case 161:
#line 1998 "hlslang.y"
    { 
		FRAG_VERT_ONLY("mat3", (yyvsp[(1) - (1)].lex).line);
		SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtFloat,EbpMedium);
		(yyval.interm.type).setAggregate(3, true);
	;}
    break;

  case 162:
#line 2003 "hlslang.y"
    { 
		FRAG_VERT_ONLY("mat4", (yyvsp[(1) - (1)].lex).line);
		SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtFloat,EbpMedium);
		(yyval.interm.type).setAggregate(4, true);
	;}
    break;

  case 163:
#line 2008 "hlslang.y"
    {
		FRAG_VERT_ONLY("mat2", (yyvsp[(1) - (1)].lex).line);
		SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtFloat,EbpLow);
		(yyval.interm.type).setAggregate(2, true);
	;}
    break;

  case 164:
#line 2013 "hlslang.y"
    { 
		FRAG_VERT_ONLY("mat3", (yyvsp[(1) - (1)].lex).line);
		SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtFloat,EbpLow);
		(yyval.interm.type).setAggregate(3, true);
	;}
    break;

  case 165:
#line 2018 "hlslang.y"
    { 
		FRAG_VERT_ONLY("mat4", (yyvsp[(1) - (1)].lex).line);
		SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtFloat,EbpLow);
		(yyval.interm.type).setAggregate(4, true);
	;}
    break;

  case 166:
#line 2023 "hlslang.y"
    {
        FRAG_VERT_ONLY("texture", (yyvsp[(1) - (1)].lex).line);
        SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtTexture,EbpUndefined);
    ;}
    break;

  case 167:
#line 2027 "hlslang.y"
    {
        FRAG_VERT_ONLY("sampler", (yyvsp[(1) - (1)].lex).line);
        SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtSamplerGeneric,EbpUndefined);
    ;}
    break;

  case 168:
#line 2031 "hlslang.y"
    {
        FRAG_VERT_ONLY("sampler1D", (yyvsp[(1) - (1)].lex).line);
        SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtSampler1D,EbpUndefined);
    ;}
    break;

  case 169:
#line 2035 "hlslang.y"
    {
        FRAG_VERT_ONLY("sampler2D", (yyvsp[(1) - (1)].lex).line);
        SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtSampler2D,EbpUndefined);
    ;}
    break;

  case 170:
#line 2039 "hlslang.y"
    {
        FRAG_VERT_ONLY("sampler3D", (yyvsp[(1) - (1)].lex).line);
        SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtSampler3D,EbpUndefined);
    ;}
    break;

  case 171:
#line 2043 "hlslang.y"
    {
        FRAG_VERT_ONLY("samplerCube", (yyvsp[(1) - (1)].lex).line);
        SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtSamplerCube,EbpUndefined);
    ;}
    break;

  case 172:
#line 2047 "hlslang.y"
    {
        FRAG_VERT_ONLY("samplerRECT", (yyvsp[(1) - (1)].lex).line);
        SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtSamplerRect,EbpUndefined);
    ;}
    break;

  case 173:
#line 2051 "hlslang.y"
    {
        FRAG_VERT_ONLY("sampler1DShadow", (yyvsp[(1) - (1)].lex).line);
        SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtSampler1DShadow,EbpUndefined);
    ;}
    break;

  case 174:
#line 2055 "hlslang.y"
    {
        FRAG_VERT_ONLY("sampler2DShadow", (yyvsp[(1) - (1)].lex).line);
        SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtSampler2DShadow,EbpUndefined);
    ;}
    break;

  case 175:
#line 2059 "hlslang.y"
    {
        FRAG_VERT_ONLY("struct", (yyvsp[(1) - (1)].interm.type).line);
        (yyval.interm.type) = (yyvsp[(1) - (1)].interm.type);
        (yyval.interm.type).qualifier = parseContext.getDefaultQualifier();
    ;}
    break;

  case 176:
#line 2064 "hlslang.y"
    {     
        //
        // This is for user defined type names.  The lexical phase looked up the 
        // type.
        //
        TType& structure = static_cast<TVariable*>((yyvsp[(1) - (1)].lex).symbol)->getType();
        SET_BASIC_TYPE((yyval.interm.type),(yyvsp[(1) - (1)].lex),EbtStruct,EbpUndefined);
        (yyval.interm.type).userDef = &structure;
    ;}
    break;

  case 177:
#line 2076 "hlslang.y"
    {
        TType* structure = new TType((yyvsp[(4) - (5)].interm.typeList), *(yyvsp[(2) - (5)].lex).string, EbpUndefined, (yyvsp[(2) - (5)].lex).line);
        TVariable* userTypeDef = new TVariable((yyvsp[(2) - (5)].lex).string, *structure, true);
        if (! parseContext.symbolTable.insert(*userTypeDef)) {
            parseContext.error((yyvsp[(2) - (5)].lex).line, "redefinition", (yyvsp[(2) - (5)].lex).string->c_str(), "struct");
            parseContext.recover();
        }
        (yyval.interm.type).setBasic(EbtStruct, EvqTemporary, (yyvsp[(1) - (5)].lex).line);
        (yyval.interm.type).userDef = structure;
    ;}
    break;

  case 178:
#line 2086 "hlslang.y"
    {
        TType* structure = new TType((yyvsp[(3) - (4)].interm.typeList), TString(""), EbpUndefined, (yyvsp[(1) - (4)].lex).line);
        (yyval.interm.type).setBasic(EbtStruct, EvqTemporary, (yyvsp[(1) - (4)].lex).line);
        (yyval.interm.type).userDef = structure;
    ;}
    break;

  case 179:
#line 2094 "hlslang.y"
    {
        (yyval.interm.typeList) = (yyvsp[(1) - (1)].interm.typeList);
    ;}
    break;

  case 180:
#line 2097 "hlslang.y"
    {
        (yyval.interm.typeList) = (yyvsp[(1) - (2)].interm.typeList);
        for (unsigned int i = 0; i < (yyvsp[(2) - (2)].interm.typeList)->size(); ++i) {
            for (unsigned int j = 0; j < (yyval.interm.typeList)->size(); ++j) {
                if ((*(yyval.interm.typeList))[j].type->getFieldName() == (*(yyvsp[(2) - (2)].interm.typeList))[i].type->getFieldName()) {
                    parseContext.error((*(yyvsp[(2) - (2)].interm.typeList))[i].line, "duplicate field name in structure:", "struct", (*(yyvsp[(2) - (2)].interm.typeList))[i].type->getFieldName().c_str());
                    parseContext.recover();
                }
            }
            (yyval.interm.typeList)->push_back((*(yyvsp[(2) - (2)].interm.typeList))[i]);
        }
    ;}
    break;

  case 181:
#line 2112 "hlslang.y"
    {
        (yyval.interm.typeList) = (yyvsp[(2) - (3)].interm.typeList);
        
        if (parseContext.voidErrorCheck((yyvsp[(1) - (3)].interm.type).line, (*(yyvsp[(2) - (3)].interm.typeList))[0].type->getFieldName(), (yyvsp[(1) - (3)].interm.type))) {
            parseContext.recover();
        }
        for (unsigned int i = 0; i < (yyval.interm.typeList)->size(); ++i) {
            //
            // Careful not to replace already know aspects of type, like array-ness
            //
            TType* type = (*(yyval.interm.typeList))[i].type;
            type->setBasicType((yyvsp[(1) - (3)].interm.type).type);
            type->setPrecision((yyvsp[(1) - (3)].interm.type).precision);
            type->setNominalSize((yyvsp[(1) - (3)].interm.type).size);
            type->setMatrix((yyvsp[(1) - (3)].interm.type).matrix);
            
            // don't allow arrays of arrays
            if (type->isArray()) {
                if (parseContext.arrayTypeErrorCheck((yyvsp[(1) - (3)].interm.type).line, (yyvsp[(1) - (3)].interm.type)))
                    parseContext.recover();
            }
            if ((yyvsp[(1) - (3)].interm.type).array)
                type->setArraySize((yyvsp[(1) - (3)].interm.type).arraySize);
            if ((yyvsp[(1) - (3)].interm.type).userDef) {
                type->setStruct((yyvsp[(1) - (3)].interm.type).userDef->getStruct());
                type->setTypeName((yyvsp[(1) - (3)].interm.type).userDef->getTypeName());
            }
        }
    ;}
    break;

  case 182:
#line 2144 "hlslang.y"
    {
        (yyval.interm.typeList) = NewPoolTTypeList();
        (yyval.interm.typeList)->push_back((yyvsp[(1) - (1)].interm.typeLine));
    ;}
    break;

  case 183:
#line 2148 "hlslang.y"
    {
        (yyval.interm.typeList)->push_back((yyvsp[(3) - (3)].interm.typeLine));
    ;}
    break;

  case 184:
#line 2154 "hlslang.y"
    {
        (yyval.interm.typeLine).type = new TType(EbtVoid, EbpUndefined);
        (yyval.interm.typeLine).line = (yyvsp[(1) - (1)].lex).line;
        (yyval.interm.typeLine).type->setFieldName(*(yyvsp[(1) - (1)].lex).string);
    ;}
    break;

  case 185:
#line 2159 "hlslang.y"
    {
        (yyval.interm.typeLine).type = new TType(EbtVoid, EbpUndefined);
        (yyval.interm.typeLine).line = (yyvsp[(1) - (3)].lex).line;
        (yyval.interm.typeLine).type->setFieldName(*(yyvsp[(1) - (3)].lex).string);
        (yyval.interm.typeLine).type->setSemantic(*(yyvsp[(3) - (3)].lex).string);
    ;}
    break;

  case 186:
#line 2165 "hlslang.y"
    {
        (yyval.interm.typeLine).type = new TType(EbtVoid, EbpUndefined);
        (yyval.interm.typeLine).line = (yyvsp[(1) - (4)].lex).line;
        (yyval.interm.typeLine).type->setFieldName(*(yyvsp[(1) - (4)].lex).string);
        
        int size;
        if (parseContext.arraySizeErrorCheck((yyvsp[(2) - (4)].lex).line, (yyvsp[(3) - (4)].interm.intermTypedNode), size))
            parseContext.recover();
        (yyval.interm.typeLine).type->setArraySize(size);
    ;}
    break;

  case 187:
#line 2175 "hlslang.y"
    {
        (yyval.interm.typeLine).type = new TType(EbtVoid, EbpUndefined);
        (yyval.interm.typeLine).line = (yyvsp[(1) - (6)].lex).line;
        (yyval.interm.typeLine).type->setFieldName(*(yyvsp[(1) - (6)].lex).string);
        
        int size;
        if (parseContext.arraySizeErrorCheck((yyvsp[(2) - (6)].lex).line, (yyvsp[(3) - (6)].interm.intermTypedNode), size))
            parseContext.recover();
        (yyval.interm.typeLine).type->setArraySize(size);
        (yyval.interm.typeLine).type->setSemantic(*(yyvsp[(6) - (6)].lex).string);
    ;}
    break;

  case 188:
#line 2191 "hlslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); ;}
    break;

  case 189:
#line 2192 "hlslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); ;}
    break;

  case 190:
#line 2193 "hlslang.y"
    { (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); ;}
    break;

  case 191:
#line 2197 "hlslang.y"
    { (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); ;}
    break;

  case 192:
#line 2201 "hlslang.y"
    { (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermAggregate); ;}
    break;

  case 193:
#line 2202 "hlslang.y"
    { (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); ;}
    break;

  case 194:
#line 2208 "hlslang.y"
    { (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); ;}
    break;

  case 195:
#line 2209 "hlslang.y"
    { (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); ;}
    break;

  case 196:
#line 2210 "hlslang.y"
    { (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); ;}
    break;

  case 197:
#line 2211 "hlslang.y"
    { (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); ;}
    break;

  case 198:
#line 2212 "hlslang.y"
    { (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); ;}
    break;

  case 199:
#line 2216 "hlslang.y"
    { (yyval.interm.intermAggregate) = 0; ;}
    break;

  case 200:
#line 2217 "hlslang.y"
    { parseContext.symbolTable.push(); ;}
    break;

  case 201:
#line 2217 "hlslang.y"
    { parseContext.symbolTable.pop(); ;}
    break;

  case 202:
#line 2217 "hlslang.y"
    {
        if ((yyvsp[(3) - (5)].interm.intermAggregate) != 0)            
            (yyvsp[(3) - (5)].interm.intermAggregate)->setOperator(EOpSequence); 
        (yyval.interm.intermAggregate) = (yyvsp[(3) - (5)].interm.intermAggregate);
    ;}
    break;

  case 203:
#line 2225 "hlslang.y"
    { (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); ;}
    break;

  case 204:
#line 2226 "hlslang.y"
    { (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); ;}
    break;

  case 205:
#line 2231 "hlslang.y"
    { 
        (yyval.interm.intermNode) = 0; 
    ;}
    break;

  case 206:
#line 2234 "hlslang.y"
    { 
        if ((yyvsp[(2) - (3)].interm.intermAggregate))
            (yyvsp[(2) - (3)].interm.intermAggregate)->setOperator(EOpSequence); 
        (yyval.interm.intermNode) = (yyvsp[(2) - (3)].interm.intermAggregate); 
    ;}
    break;

  case 207:
#line 2242 "hlslang.y"
    {
        (yyval.interm.intermAggregate) = parseContext.intermediate.makeAggregate((yyvsp[(1) - (1)].interm.intermNode), 0); 
    ;}
    break;

  case 208:
#line 2245 "hlslang.y"
    { 
        (yyval.interm.intermAggregate) = parseContext.intermediate.growAggregate((yyvsp[(1) - (2)].interm.intermAggregate), (yyvsp[(2) - (2)].interm.intermNode), 0);
    ;}
    break;

  case 209:
#line 2251 "hlslang.y"
    { (yyval.interm.intermNode) = 0; ;}
    break;

  case 210:
#line 2252 "hlslang.y"
    { (yyval.interm.intermNode) = static_cast<TIntermNode*>((yyvsp[(1) - (2)].interm.intermTypedNode)); ;}
    break;

  case 211:
#line 2256 "hlslang.y"
    { 
        if (parseContext.boolErrorCheck((yyvsp[(1) - (5)].lex).line, (yyvsp[(3) - (5)].interm.intermTypedNode)))
            parseContext.recover();
        (yyval.interm.intermNode) = parseContext.intermediate.addSelection((yyvsp[(3) - (5)].interm.intermTypedNode), (yyvsp[(5) - (5)].interm.nodePair), (yyvsp[(1) - (5)].lex).line);
    ;}
    break;

  case 212:
#line 2264 "hlslang.y"
    {
        (yyval.interm.nodePair).node1 = (yyvsp[(1) - (3)].interm.intermNode);
        (yyval.interm.nodePair).node2 = (yyvsp[(3) - (3)].interm.intermNode);
    ;}
    break;

  case 213:
#line 2268 "hlslang.y"
    { 
        (yyval.interm.nodePair).node1 = (yyvsp[(1) - (1)].interm.intermNode);
        (yyval.interm.nodePair).node2 = 0;
    ;}
    break;

  case 214:
#line 2278 "hlslang.y"
    {
        (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode);
        if (parseContext.boolErrorCheck((yyvsp[(1) - (1)].interm.intermTypedNode)->getLine(), (yyvsp[(1) - (1)].interm.intermTypedNode)))
            parseContext.recover();          
    ;}
    break;

  case 215:
#line 2283 "hlslang.y"
    {
        TIntermNode* intermNode;
        if (parseContext.structQualifierErrorCheck((yyvsp[(2) - (4)].lex).line, (yyvsp[(1) - (4)].interm.type)))
            parseContext.recover();
        if (parseContext.boolErrorCheck((yyvsp[(2) - (4)].lex).line, (yyvsp[(1) - (4)].interm.type)))
            parseContext.recover();
        
        if (!parseContext.executeInitializer((yyvsp[(2) - (4)].lex).line, *(yyvsp[(2) - (4)].lex).string, (yyvsp[(1) - (4)].interm.type), (yyvsp[(4) - (4)].interm.intermTypedNode), intermNode))
            (yyval.interm.intermTypedNode) = (yyvsp[(4) - (4)].interm.intermTypedNode);
        else {
            parseContext.recover();
            (yyval.interm.intermTypedNode) = 0;
        }
    ;}
    break;

  case 216:
#line 2300 "hlslang.y"
    { parseContext.symbolTable.push(); ++parseContext.loopNestingLevel; ;}
    break;

  case 217:
#line 2300 "hlslang.y"
    { 
        parseContext.symbolTable.pop();
        (yyval.interm.intermNode) = parseContext.intermediate.addLoop((yyvsp[(6) - (6)].interm.intermNode), (yyvsp[(4) - (6)].interm.intermTypedNode), 0, true, (yyvsp[(1) - (6)].lex).line);
        --parseContext.loopNestingLevel;
    ;}
    break;

  case 218:
#line 2305 "hlslang.y"
    { ++parseContext.loopNestingLevel; ;}
    break;

  case 219:
#line 2305 "hlslang.y"
    {
        if (parseContext.boolErrorCheck((yyvsp[(8) - (8)].lex).line, (yyvsp[(6) - (8)].interm.intermTypedNode)))
            parseContext.recover();
                    
        (yyval.interm.intermNode) = parseContext.intermediate.addLoop((yyvsp[(3) - (8)].interm.intermNode), (yyvsp[(6) - (8)].interm.intermTypedNode), 0, false, (yyvsp[(4) - (8)].lex).line);
        --parseContext.loopNestingLevel;
    ;}
    break;

  case 220:
#line 2312 "hlslang.y"
    { parseContext.symbolTable.push(); ++parseContext.loopNestingLevel; ;}
    break;

  case 221:
#line 2312 "hlslang.y"
    {
        parseContext.symbolTable.pop();
        (yyval.interm.intermNode) = parseContext.intermediate.makeAggregate((yyvsp[(4) - (7)].interm.intermNode), (yyvsp[(2) - (7)].lex).line);
        (yyval.interm.intermNode) = parseContext.intermediate.growAggregate(
                (yyval.interm.intermNode),
                parseContext.intermediate.addLoop((yyvsp[(7) - (7)].interm.intermNode), reinterpret_cast<TIntermTyped*>((yyvsp[(5) - (7)].interm.nodePair).node1), reinterpret_cast<TIntermTyped*>((yyvsp[(5) - (7)].interm.nodePair).node2), true, (yyvsp[(1) - (7)].lex).line),
                (yyvsp[(1) - (7)].lex).line);
        (yyval.interm.intermNode)->getAsAggregate()->setOperator(EOpSequence);
        --parseContext.loopNestingLevel;
    ;}
    break;

  case 222:
#line 2325 "hlslang.y"
    {
        (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); 
    ;}
    break;

  case 223:
#line 2328 "hlslang.y"
    {
        (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode);
    ;}
    break;

  case 224:
#line 2334 "hlslang.y"
    { 
        (yyval.interm.intermTypedNode) = (yyvsp[(1) - (1)].interm.intermTypedNode); 
    ;}
    break;

  case 225:
#line 2337 "hlslang.y"
    { 
        (yyval.interm.intermTypedNode) = 0; 
    ;}
    break;

  case 226:
#line 2343 "hlslang.y"
    { 
        (yyval.interm.nodePair).node1 = (yyvsp[(1) - (2)].interm.intermTypedNode);
        (yyval.interm.nodePair).node2 = 0;
    ;}
    break;

  case 227:
#line 2347 "hlslang.y"
    {
        (yyval.interm.nodePair).node1 = (yyvsp[(1) - (3)].interm.intermTypedNode);
        (yyval.interm.nodePair).node2 = (yyvsp[(3) - (3)].interm.intermTypedNode);
    ;}
    break;

  case 228:
#line 2354 "hlslang.y"
    {
        if (parseContext.loopNestingLevel <= 0) {
            parseContext.error((yyvsp[(1) - (2)].lex).line, "continue statement only allowed in loops", "", "");
            parseContext.recover();
        }        
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpContinue, (yyvsp[(1) - (2)].lex).line);
    ;}
    break;

  case 229:
#line 2361 "hlslang.y"
    {
        if (parseContext.loopNestingLevel <= 0) {
            parseContext.error((yyvsp[(1) - (2)].lex).line, "break statement only allowed in loops", "", "");
            parseContext.recover();
        }        
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpBreak, (yyvsp[(1) - (2)].lex).line);
    ;}
    break;

  case 230:
#line 2368 "hlslang.y"
    {
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpReturn, (yyvsp[(1) - (2)].lex).line);
        if (parseContext.currentFunctionType->getBasicType() != EbtVoid) {
            parseContext.error((yyvsp[(1) - (2)].lex).line, "non-void function must return a value", "return", "");
            parseContext.recover();
        }
    ;}
    break;

  case 231:
#line 2375 "hlslang.y"
    {        
        TIntermTyped *temp = (yyvsp[(2) - (3)].interm.intermTypedNode);
        if (parseContext.currentFunctionType->getBasicType() == EbtVoid) {
            parseContext.error((yyvsp[(1) - (3)].lex).line, "void function cannot return a value", "return", "");
            parseContext.recover();
        } else if (*(parseContext.currentFunctionType) != (yyvsp[(2) - (3)].interm.intermTypedNode)->getType()) {
            TOperator op = parseContext.getConstructorOp( *(parseContext.currentFunctionType));
            if ( op != EOpNull)
                temp = parseContext.constructBuiltIn( (parseContext.currentFunctionType), op, (yyvsp[(2) - (3)].interm.intermTypedNode), (yyvsp[(1) - (3)].lex).line, false);
            else
                temp = 0;
            if ( temp == 0) {
                parseContext.error((yyvsp[(1) - (3)].lex).line, "function return is not matching type:", "return", "");
                parseContext.recover();
                temp = (yyvsp[(2) - (3)].interm.intermTypedNode);
            }
        }
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpReturn, temp, (yyvsp[(1) - (3)].lex).line);
        parseContext.functionReturnsValue = true;
    ;}
    break;

  case 232:
#line 2395 "hlslang.y"
    {
        FRAG_ONLY("discard", (yyvsp[(1) - (2)].lex).line);
        (yyval.interm.intermNode) = parseContext.intermediate.addBranch(EOpKill, (yyvsp[(1) - (2)].lex).line);
    ;}
    break;

  case 233:
#line 2404 "hlslang.y"
    { 
        (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); 
        parseContext.treeRoot = (yyval.interm.intermNode); 
    ;}
    break;

  case 234:
#line 2408 "hlslang.y"
    {
        (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[(1) - (2)].interm.intermNode), (yyvsp[(2) - (2)].interm.intermNode), 0);
        parseContext.treeRoot = (yyval.interm.intermNode);
    ;}
    break;

  case 235:
#line 2415 "hlslang.y"
    { 
        (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); 
    ;}
    break;

  case 236:
#line 2418 "hlslang.y"
    { 
        (yyval.interm.intermNode) = (yyvsp[(1) - (1)].interm.intermNode); 
    ;}
    break;

  case 237:
#line 2421 "hlslang.y"
    { (yyval.interm.intermNode) = 0; ;}
    break;

  case 238:
#line 2425 "hlslang.y"
    {
        TFunction& function = *((yyvsp[(1) - (1)].interm).function);
        TFunction* prevDec = static_cast<TFunction*>(parseContext.symbolTable.find(function.getMangledName()));
        //
        // Note:  'prevDec' could be 'function' if this is the first time we've seen function
        // as it would have just been put in the symbol table.  Otherwise, we're looking up
        // an earlier occurance.
        //
        if (prevDec->isDefined()) {
            //
            // Then this function already has a body.
            //
            parseContext.error((yyvsp[(1) - (1)].interm).line, "function already has a body", function.getName().c_str(), "");
            parseContext.recover();
        }
        prevDec->setDefined();
        
        //
        // Raise error message if main function takes any parameters or return anything other than void
        //
        /* TODO: this is unneeded for HLSL, but it might need to name mangle 
        if (function.getName() == "main") {
            if (function.getParamCount() > 0) {
                parseContext.error($1.line, "function cannot take any parameter(s)", function.getName().c_str(), "");
                parseContext.recover();
            }
            if (function.getReturnType().getBasicType() != EbtVoid) {
                parseContext.error($1.line, "", function.getReturnType().getBasicString(), "main function cannot return a value");
                parseContext.recover();
            }            
        }
        */
   
        //
        // New symbol table scope for body of function plus its arguments
        //
        parseContext.symbolTable.push();
        
        //
        // Remember the return type for later checking for RETURN statements.
        //
        parseContext.currentFunctionType = &(prevDec->getReturnType());
        parseContext.functionReturnsValue = false;
        
        // 
        // Insert parameters into the symbol table.
        // If the parameter has no name, it's not an error, just don't insert it 
        // (could be used for unused args).
        //
        // Also, accumulate the list of parameters into the HIL, so lower level code
        // knows where to find parameters.
        //
        TIntermAggregate* paramNodes = new TIntermAggregate;
        for (int i = 0; i < function.getParamCount(); i++) {
            TParameter& param = function[i];
            if (param.name != 0) {
                TVariable *variable = new TVariable(param.name, param.info, *param.type);
                // 
                // Insert the parameters with name in the symbol table.
                //
                if (! parseContext.symbolTable.insert(*variable)) {
                    parseContext.error((yyvsp[(1) - (1)].interm).line, "redefinition", variable->getName().c_str(), "");
                    parseContext.recover();
                    delete variable;
                }
                //
                // Transfer ownership of name pointer to symbol table.
                //
                param.name = 0;
                
                //
                // Add the parameter to the HIL
                //                
                paramNodes = parseContext.intermediate.growAggregate(
                                               paramNodes, 
                                               parseContext.intermediate.addSymbol(variable->getUniqueId(),
                                                                       variable->getName(),
                                                                       variable->getInfo(),
                                                                       variable->getType(), (yyvsp[(1) - (1)].interm).line), 
                                               (yyvsp[(1) - (1)].interm).line);
            } else {
                paramNodes = parseContext.intermediate.growAggregate(paramNodes, parseContext.intermediate.addSymbol(0, "", param.info, *param.type, (yyvsp[(1) - (1)].interm).line), (yyvsp[(1) - (1)].interm).line);
            }
        }
        parseContext.intermediate.setAggregateOperator(paramNodes, EOpParameters, (yyvsp[(1) - (1)].interm).line);
        (yyvsp[(1) - (1)].interm).intermAggregate = paramNodes;
        parseContext.loopNestingLevel = 0;
    ;}
    break;

  case 239:
#line 2513 "hlslang.y"
    {
        //?? Check that all paths return a value if return type != void ?
        //   May be best done as post process phase on intermediate code
        if (parseContext.currentFunctionType->getBasicType() != EbtVoid && ! parseContext.functionReturnsValue) {
            parseContext.error((yyvsp[(1) - (3)].interm).line, "function does not return a value:", "", (yyvsp[(1) - (3)].interm).function->getName().c_str());
            parseContext.recover();
        }
        parseContext.symbolTable.pop();
        (yyval.interm.intermNode) = parseContext.intermediate.growAggregate((yyvsp[(1) - (3)].interm).intermAggregate, (yyvsp[(3) - (3)].interm.intermNode), 0);
        parseContext.intermediate.setAggregateOperator((yyval.interm.intermNode), EOpFunction, (yyvsp[(1) - (3)].interm).line);
        (yyval.interm.intermNode)->getAsAggregate()->setName((yyvsp[(1) - (3)].interm).function->getMangledName().c_str());
        (yyval.interm.intermNode)->getAsAggregate()->setPlainName((yyvsp[(1) - (3)].interm).function->getName().c_str());
        (yyval.interm.intermNode)->getAsAggregate()->setType((yyvsp[(1) - (3)].interm).function->getReturnType());
        
	if ( (yyvsp[(1) - (3)].interm).function->getInfo())
	    (yyval.interm.intermNode)->getAsAggregate()->setSemantic((yyvsp[(1) - (3)].interm).function->getInfo()->getSemantic());
    ;}
    break;

  case 240:
#line 2533 "hlslang.y"
    {
       (yyval.interm.intermTypedNode) = (yyvsp[(2) - (3)].interm.intermAggregate);
    ;}
    break;

  case 241:
#line 2536 "hlslang.y"
    {
       (yyval.interm.intermTypedNode) = (yyvsp[(2) - (4)].interm.intermAggregate);
    ;}
    break;

  case 242:
#line 2543 "hlslang.y"
    {
        //create a new aggNode
       (yyval.interm.intermAggregate) = parseContext.intermediate.makeAggregate( (yyvsp[(1) - (1)].interm.intermTypedNode), (yyvsp[(1) - (1)].interm.intermTypedNode)->getLine());       
    ;}
    break;

  case 243:
#line 2547 "hlslang.y"
    {
       //take the inherited aggNode and return it
       (yyval.interm.intermAggregate) = (yyvsp[(1) - (1)].interm.intermTypedNode)->getAsAggregate();       
    ;}
    break;

  case 244:
#line 2551 "hlslang.y"
    {
        // append to the aggNode
       (yyval.interm.intermAggregate) = parseContext.intermediate.growAggregate( (yyvsp[(1) - (3)].interm.intermAggregate), (yyvsp[(3) - (3)].interm.intermTypedNode), (yyvsp[(3) - (3)].interm.intermTypedNode)->getLine());       
    ;}
    break;

  case 245:
#line 2555 "hlslang.y"
    {
       // append all children or $3 to $1 
       (yyval.interm.intermAggregate) = parseContext.mergeAggregates( (yyvsp[(1) - (3)].interm.intermAggregate), (yyvsp[(3) - (3)].interm.intermTypedNode)->getAsAggregate());
    ;}
    break;

  case 246:
#line 2562 "hlslang.y"
    {
        //empty annotation
	  (yyval.interm.ann) = 0;
    ;}
    break;

  case 247:
#line 2566 "hlslang.y"
    {
      (yyval.interm.ann) = (yyvsp[(2) - (3)].interm.ann);
    ;}
    break;

  case 248:
#line 2572 "hlslang.y"
    {
        (yyval.interm.ann) = new TAnnotation;
	(yyval.interm.ann)->addKey( *(yyvsp[(1) - (1)].lex).string);
    ;}
    break;

  case 249:
#line 2576 "hlslang.y"
    {
        (yyvsp[(1) - (2)].interm.ann)->addKey( *(yyvsp[(2) - (2)].lex).string);
	(yyval.interm.ann) = (yyvsp[(1) - (2)].interm.ann);
    ;}
    break;

  case 250:
#line 2583 "hlslang.y"
    {
        (yyval.lex).string = (yyvsp[(2) - (5)].lex).string;
    ;}
    break;

  case 251:
#line 2589 "hlslang.y"
    {;}
    break;

  case 252:
#line 2590 "hlslang.y"
    {;}
    break;

  case 253:
#line 2591 "hlslang.y"
    {;}
    break;

  case 254:
#line 2592 "hlslang.y"
    {;}
    break;

  case 255:
#line 2593 "hlslang.y"
    {;}
    break;

  case 256:
#line 2594 "hlslang.y"
    {;}
    break;

  case 257:
#line 2595 "hlslang.y"
    {;}
    break;

  case 258:
#line 2596 "hlslang.y"
    {;}
    break;

  case 259:
#line 2597 "hlslang.y"
    {;}
    break;

  case 260:
#line 2598 "hlslang.y"
    {;}
    break;

  case 261:
#line 2599 "hlslang.y"
    {;}
    break;

  case 262:
#line 2600 "hlslang.y"
    {;}
    break;

  case 263:
#line 2601 "hlslang.y"
    {;}
    break;

  case 264:
#line 2602 "hlslang.y"
    {;}
    break;

  case 265:
#line 2603 "hlslang.y"
    {;}
    break;

  case 266:
#line 2604 "hlslang.y"
    {;}
    break;

  case 267:
#line 2605 "hlslang.y"
    {;}
    break;

  case 268:
#line 2606 "hlslang.y"
    {;}
    break;

  case 269:
#line 2607 "hlslang.y"
    {;}
    break;

  case 270:
#line 2608 "hlslang.y"
    {;}
    break;

  case 271:
#line 2609 "hlslang.y"
    {;}
    break;

  case 272:
#line 2613 "hlslang.y"
    {;}
    break;

  case 273:
#line 2614 "hlslang.y"
    {;}
    break;

  case 274:
#line 2615 "hlslang.y"
    {;}
    break;

  case 275:
#line 2616 "hlslang.y"
    {;}
    break;

  case 276:
#line 2620 "hlslang.y"
    {
    (yyval.lex).f = (float)(yyvsp[(1) - (1)].lex).i;
;}
    break;

  case 277:
#line 2623 "hlslang.y"
    {
    (yyval.lex).f = ((yyvsp[(1) - (1)].lex).b) ? 1.0f : 0.0f;
;}
    break;

  case 278:
#line 2626 "hlslang.y"
    {
    (yyval.lex) = (yyvsp[(1) - (1)].lex);
;}
    break;

  case 279:
#line 2632 "hlslang.y"
    {;}
    break;

  case 280:
#line 2636 "hlslang.y"
    {;}
    break;

  case 281:
#line 2637 "hlslang.y"
    {;}
    break;

  case 282:
#line 2641 "hlslang.y"
    {;}
    break;

  case 283:
#line 2645 "hlslang.y"
    {
        // This is being thrown away
    ;}
    break;

  case 284:
#line 2651 "hlslang.y"
    { (yyval.lex).string = (yyvsp[(2) - (2)].lex).string;;}
    break;

  case 285:
#line 2655 "hlslang.y"
    { (yyval.interm.typeInfo) = 0;;}
    break;

  case 286:
#line 2656 "hlslang.y"
    { (yyval.interm.typeInfo) = new TTypeInfo( *(yyvsp[(1) - (1)].lex).string, 0); ;}
    break;

  case 287:
#line 2657 "hlslang.y"
    { (yyval.interm.typeInfo) = 0; ;}
    break;

  case 288:
#line 2658 "hlslang.y"
    { (yyval.interm.typeInfo) = new TTypeInfo( "", (yyvsp[(1) - (1)].interm.ann)); ;}
    break;

  case 289:
#line 2659 "hlslang.y"
    { (yyval.interm.typeInfo) = new TTypeInfo( *(yyvsp[(1) - (2)].lex).string, (yyvsp[(2) - (2)].interm.ann)); ;}
    break;

  case 290:
#line 2660 "hlslang.y"
    { (yyval.interm.typeInfo) = new TTypeInfo( *(yyvsp[(1) - (2)].lex).string, 0); ;}
    break;

  case 291:
#line 2661 "hlslang.y"
    { (yyval.interm.typeInfo) = new TTypeInfo( "", (yyvsp[(2) - (2)].interm.ann)); ;}
    break;

  case 292:
#line 2662 "hlslang.y"
    { (yyval.interm.typeInfo) = new TTypeInfo( *(yyvsp[(1) - (3)].lex).string, (yyvsp[(3) - (3)].interm.ann)); ;}
    break;

  case 293:
#line 2666 "hlslang.y"
    {
    constUnion *cUnion = new constUnion[1];
    cUnion[0].setFConst(0.0f);
    (yyval.interm.intermTypedNode) = parseContext.intermediate.addConstantUnion( cUnion, TType(EbtFloat, EbpUndefined, EvqConst, 1), (yyvsp[(1) - (4)].lex).line);
;}
    break;

  case 294:
#line 2671 "hlslang.y"
    {
;}
    break;

  case 295:
#line 2676 "hlslang.y"
    {
;}
    break;

  case 296:
#line 2678 "hlslang.y"
    {
;}
    break;

  case 297:
#line 2683 "hlslang.y"
    {;}
    break;

  case 298:
#line 2684 "hlslang.y"
    {;}
    break;

  case 299:
#line 2685 "hlslang.y"
    {;}
    break;

  case 300:
#line 2686 "hlslang.y"
    {;}
    break;

  case 301:
#line 2687 "hlslang.y"
    {;}
    break;

  case 302:
#line 2688 "hlslang.y"
    {;}
    break;


/* Line 1267 of yacc.c.  */
#line 5939 "hlslang_tab.cpp"
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


#line 2691 "hlslang.y"


