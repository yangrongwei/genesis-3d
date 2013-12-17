
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse         Genesisparse
#define yylex           Genesislex
#define yyerror         Genesiserror
#define yylval          Genesislval
#define yychar          Genesischar
#define yydebug         Genesisdebug
#define yynerrs         Genesisnerrs


/* Copy the first part of user declarations.  */


#include "stdneb.h"
#include "rendersystem/base/RenderDeviceTypes.h"
#include "GenesisShaderParser.h"
#include "../GenesisMaterial.h"
#include "addons/shadercompiler/Utility/ShaderCompilerUtil.h"

void ResetParserParams();
int yyerror (const char *s);
extern int Genesislineno;
extern char* yytext;
int yylex ();

using namespace GenesisMaterialMaker;
using namespace ShaderProgramCompiler;

GenesisMaterial* g_GenesisMaterial;
static  GenesisMakePass* g_curMakePass = NULL;
static  GenesisMakeTechnique* g_curGenesisMakeTechnique = NULL;
static  GenesisMakeMaterial* g_curGenesisMakeMaterial = NULL;
static  GenesisMakeGPUProgram* g_curGenesisMakeGPUProgram = NULL;
static  Graphic::ShaderParam* g_curShaderParameter = NULL;
static  Graphic::MaterialParam* g_curMatParam = NULL;
static  GPtr<RenderBase::RenderStateDesc> g_rsDesc = 0;

#define ASSIGN(s,d) {s = *d; delete d;}
#define YYDEBUG 1




/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TSHADER = 258,
     TTECHNIQUE = 259,
     TPASS = 260,
     TSETSHADERCODE = 261,
     TPARAMETERS = 262,
     TRENDERQUEUE = 263,
     TSHADERTYPE = 264,
     TRENDERDEVICETYPE = 265,
     TSETPARAM = 266,
     TRENDERSTATE = 267,
     TCULLMODE = 268,
     TFILLMODE = 269,
     TCOLORMASK = 270,
     TDEPTHTEST = 271,
     TDEPTHWRITE = 272,
     TBLENDCOLOR = 273,
     TALPHATEST = 274,
     TSAMPLER = 275,
     TMATTYPE = 276,
     TMATRIX = 277,
     TVECTOR = 278,
     TFLOAT = 279,
     TTEXTURE = 280,
     TREALSTRING = 281,
     TVAR = 282,
     TOPERATOR = 283,
     TNUMBER = 284,
     TBOOLEAN = 285
   };
#endif
/* Tokens.  */
#define TSHADER 258
#define TTECHNIQUE 259
#define TPASS 260
#define TSETSHADERCODE 261
#define TPARAMETERS 262
#define TRENDERQUEUE 263
#define TSHADERTYPE 264
#define TRENDERDEVICETYPE 265
#define TSETPARAM 266
#define TRENDERSTATE 267
#define TCULLMODE 268
#define TFILLMODE 269
#define TCOLORMASK 270
#define TDEPTHTEST 271
#define TDEPTHWRITE 272
#define TBLENDCOLOR 273
#define TALPHATEST 274
#define TSAMPLER 275
#define TMATTYPE 276
#define TMATRIX 277
#define TVECTOR 278
#define TFLOAT 279
#define TTEXTURE 280
#define TREALSTRING 281
#define TVAR 282
#define TOPERATOR 283
#define TNUMBER 284
#define TBOOLEAN 285




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{


	char* str;
	float num;
	Graphic::ShaderParamType spt;
	bool boolean;



} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */



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
# if YYENABLE_NLS
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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   100

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  73
/* YYNRULES -- Number of states.  */
#define YYNSTATES  130

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   285

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
       2,    33,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    31,     2,    32,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     5,     6,    15,    16,    17,    18,
      26,    30,    31,    37,    38,    45,    46,    52,    59,    66,
      72,    79,    85,    92,    98,    99,   100,   104,   105,   109,
     110,   111,   112,   122,   123,   126,   127,   130,   133,   134,
     135,   136,   144,   145,   149,   153,   157,   160,   164,   167,
     170,   173,   177,   182,   185,   188,   193,   196,   200,   203,
     204,   205,   206,   215,   216,   217,   218,   219,   229,   230,
     234,   240,   246,   252
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      35,     0,    -1,    -1,    -1,    -1,     3,    26,    36,    31,
      37,    39,    38,    32,    -1,    -1,    -1,    -1,    39,     7,
      31,    40,    44,    41,    32,    -1,    39,     8,    26,    -1,
      -1,    39,     4,    31,    42,    45,    -1,    -1,    39,     4,
      26,    31,    43,    45,    -1,    -1,    44,    25,    27,    33,
      26,    -1,    44,    25,    27,    28,    33,    26,    -1,    44,
      22,    27,    28,    33,    26,    -1,    44,    22,    27,    33,
      26,    -1,    44,    23,    27,    28,    33,    26,    -1,    44,
      23,    27,    33,    26,    -1,    44,    24,    27,    28,    33,
      26,    -1,    44,    24,    27,    33,    26,    -1,    -1,    -1,
      47,    46,    32,    -1,    -1,    47,    21,    26,    -1,    -1,
      -1,    -1,    47,     5,    51,    48,    31,    49,    52,    50,
      32,    -1,    -1,    51,    26,    -1,    -1,    52,    53,    -1,
      52,    61,    -1,    -1,    -1,    -1,    53,    12,    31,    54,
      56,    55,    32,    -1,    -1,    56,    13,    26,    -1,    56,
      14,    26,    -1,    56,    15,    26,    -1,    56,    58,    -1,
      56,    17,    30,    -1,    56,    59,    -1,    56,    60,    -1,
      56,    57,    -1,    20,    26,    27,    -1,    20,    26,    27,
      27,    -1,    16,    27,    -1,    16,    30,    -1,    18,    27,
      26,    26,    -1,    18,    30,    -1,    19,    27,    26,    -1,
      19,    30,    -1,    -1,    -1,    -1,     9,    26,    62,    31,
      63,    65,    64,    32,    -1,    -1,    -1,    -1,    -1,    65,
      10,    26,    66,    31,    67,    69,    68,    32,    -1,    -1,
      69,     6,    26,    -1,    69,    11,    29,    27,    25,    -1,
      69,    11,    29,    27,    22,    -1,    69,    11,    29,    27,
      23,    -1,    69,    11,    29,    27,    24,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    68,    68,    74,    76,    68,    83,    85,    87,    85,
      91,    94,    94,    99,    99,   105,   107,   151,   195,   203,
     211,   219,   227,   235,   244,   246,   246,   254,   256,   259,
     261,   264,   259,   273,   278,   284,   286,   288,   291,   293,
     298,   293,   305,   307,   312,   317,   322,   324,   329,   331,
     333,   336,   339,   343,   350,   357,   366,   373,   390,   397,
     403,   405,   397,   416,   417,   422,   424,   417,   430,   432,
     437,   446,   455,   464
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TSHADER", "TTECHNIQUE", "TPASS",
  "TSETSHADERCODE", "TPARAMETERS", "TRENDERQUEUE", "TSHADERTYPE",
  "TRENDERDEVICETYPE", "TSETPARAM", "TRENDERSTATE", "TCULLMODE",
  "TFILLMODE", "TCOLORMASK", "TDEPTHTEST", "TDEPTHWRITE", "TBLENDCOLOR",
  "TALPHATEST", "TSAMPLER", "TMATTYPE", "TMATRIX", "TVECTOR", "TFLOAT",
  "TTEXTURE", "TREALSTRING", "TVAR", "TOPERATOR", "TNUMBER", "TBOOLEAN",
  "'{'", "'}'", "'='", "$accept", "shader", "$@1", "$@2", "$@3",
  "PropertySection", "$@4", "$@5", "$@6", "$@7", "ParameterSection",
  "TechniqueSection", "$@8", "PassSection", "$@9", "$@10", "$@11",
  "PassType", "codeSection", "StateSection", "$@12", "$@13",
  "RenderStateSetup", "SamplerSetup", "DepthTestSetup", "BlendSetup",
  "AlphaTestSetup", "shadertype", "$@14", "$@15", "$@16",
  "DeviceTypeSetup", "$@17", "$@18", "$@19", "CodeBlock", 0
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
     285,   123,   125,    61
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    34,    36,    37,    38,    35,    39,    40,    41,    39,
      39,    42,    39,    43,    39,    44,    44,    44,    44,    44,
      44,    44,    44,    44,    45,    46,    45,    47,    47,    48,
      49,    50,    47,    51,    51,    52,    52,    52,    53,    54,
      55,    53,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    57,    57,    58,    58,    59,    59,    60,    60,    62,
      63,    64,    61,    65,    66,    67,    68,    65,    69,    69,
      69,    69,    69,    69
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,     0,     8,     0,     0,     0,     7,
       3,     0,     5,     0,     6,     0,     5,     6,     6,     5,
       6,     5,     6,     5,     0,     0,     3,     0,     3,     0,
       0,     0,     9,     0,     2,     0,     2,     2,     0,     0,
       0,     7,     0,     3,     3,     3,     2,     3,     2,     2,
       2,     3,     4,     2,     2,     4,     2,     3,     2,     0,
       0,     0,     8,     0,     0,     0,     0,     9,     0,     3,
       5,     5,     5,     5
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     1,     0,     3,     6,     4,     0,
       0,     0,     0,     0,    11,     7,    10,     5,    13,    24,
      15,    24,    12,    25,     8,    14,    33,     0,     0,     0,
       0,     0,     0,     0,    29,    28,    26,     0,     0,     0,
       0,     9,    34,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    30,     0,    19,     0,    21,     0,    23,     0,
      16,    35,    18,    20,    22,    17,    31,     0,     0,    36,
      37,    59,    32,     0,     0,    39,    60,    42,    63,    40,
      61,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      50,    46,    48,    49,     0,     0,    43,    44,    45,    53,
      54,    47,     0,    56,     0,    58,     0,    41,    64,    62,
       0,    57,    51,     0,    55,    52,    65,    68,    66,     0,
       0,     0,    69,     0,    67,     0,    71,    72,    73,    70
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     5,     7,    12,     8,    20,    33,    19,    21,
      24,    22,    28,    23,    43,    61,    68,    34,    66,    69,
      77,    89,    79,    90,    91,    92,    93,    70,    74,    78,
      95,    80,   113,   117,   121,   118
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -17
static const yytype_int8 yypact[] =
{
       8,    -3,    12,   -17,   -17,    -2,   -17,   -17,    24,   -16,
      -1,    17,    10,    21,   -17,   -17,   -17,   -17,   -17,    -5,
     -17,    -5,   -17,    -4,    11,   -17,   -17,    25,    22,    26,
      28,    29,    30,    27,    34,   -17,   -17,   -15,   -14,    -8,
      -7,   -17,   -17,    31,    -9,    35,    33,    37,    36,    38,
      39,    41,   -17,    42,   -17,    44,   -17,    45,   -17,    47,
     -17,   -17,   -17,   -17,   -17,   -17,    32,    48,    43,    46,
     -17,   -17,   -17,    49,    50,   -17,   -17,   -17,   -17,   -11,
      55,    51,    52,    53,    18,    54,    19,    20,    56,    57,
     -17,   -17,   -17,   -17,    59,    58,   -17,   -17,   -17,   -17,
     -17,   -17,    60,   -17,    61,   -17,    64,   -17,   -17,   -17,
      62,   -17,    65,    63,   -17,   -17,   -17,   -17,    16,    67,
      66,    68,   -17,    69,   -17,    15,   -17,   -17,   -17,   -17
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -17,   -17,   -17,   -17,   -17,   -17,   -17,   -17,   -17,   -17,
     -17,    76,   -17,   -17,   -17,   -17,   -17,   -17,   -17,   -17,
     -17,   -17,   -17,   -17,   -17,   -17,   -17,   -17,   -17,   -17,
     -17,   -17,   -17,   -17,   -17,   -17
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -39
static const yytype_int16 yytable[] =
{
     -27,    26,    81,    82,    83,    84,    85,    86,    87,    88,
      13,     1,     4,    44,    46,    14,   -27,    27,    45,    47,
      48,    50,   119,     3,    53,    49,    51,   120,     9,     6,
      15,    10,    11,    29,    30,    31,    32,   126,   127,   128,
     129,    67,    17,    16,   -38,    99,   102,   104,   100,   103,
     105,    35,    18,    37,    36,    38,    39,    40,    73,    41,
      42,    54,    52,    56,    58,    94,    55,    60,    62,    57,
      63,    64,    59,    65,    71,    72,     0,    96,    97,    98,
      75,    76,   106,     0,   101,   108,   110,   111,   114,   107,
     109,   112,   115,   122,   116,   123,   125,    25,     0,     0,
     124
};

static const yytype_int8 yycheck[] =
{
       5,     5,    13,    14,    15,    16,    17,    18,    19,    20,
      26,     3,     0,    28,    28,    31,    21,    21,    33,    33,
      28,    28,     6,    26,    33,    33,    33,    11,     4,    31,
      31,     7,     8,    22,    23,    24,    25,    22,    23,    24,
      25,     9,    32,    26,    12,    27,    27,    27,    30,    30,
      30,    26,    31,    27,    32,    27,    27,    27,    12,    32,
      26,    26,    31,    26,    26,    10,    33,    26,    26,    33,
      26,    26,    33,    26,    26,    32,    -1,    26,    26,    26,
      31,    31,    26,    -1,    30,    26,    26,    26,    26,    32,
      32,    27,    27,    26,    31,    29,    27,    21,    -1,    -1,
      32
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    35,    26,     0,    36,    31,    37,    39,     4,
       7,     8,    38,    26,    31,    31,    26,    32,    31,    42,
      40,    43,    45,    47,    44,    45,     5,    21,    46,    22,
      23,    24,    25,    41,    51,    26,    32,    27,    27,    27,
      27,    32,    26,    48,    28,    33,    28,    33,    28,    33,
      28,    33,    31,    33,    26,    33,    26,    33,    26,    33,
      26,    49,    26,    26,    26,    26,    52,     9,    50,    53,
      61,    26,    32,    12,    62,    31,    31,    54,    63,    56,
      65,    13,    14,    15,    16,    17,    18,    19,    20,    55,
      57,    58,    59,    60,    10,    64,    26,    26,    26,    27,
      30,    30,    27,    30,    27,    30,    26,    32,    26,    32,
      26,    26,    27,    66,    26,    27,    31,    67,    69,     6,
      11,    68,    26,    29,    32,    27,    22,    23,    24,    25
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
# if YYLTYPE_IS_TRIVIAL
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
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

    { //n_printf("init genesisshader\n");
									  g_GenesisMaterial->SetName((yyvsp[(2) - (2)].str));
										delete[] (yyvsp[(2) - (2)].str);
									  ResetParserParams();
									  g_curGenesisMakeMaterial = new GenesisMakeMaterial();
									}
    break;

  case 3:

    { //n_printf("in genesisshader,left\n"); 
									}
    break;

  case 4:

    { //n_printf("from PropertySection to genesisshader\n"); 
									}
    break;

  case 5:

    { //n_printf("out genesisshader,right\n");
										g_GenesisMaterial->AddMaterial(*g_curGenesisMakeMaterial);
										delete	g_curGenesisMakeMaterial;
										g_curGenesisMakeMaterial = 0;
									 }
    break;

  case 6:

    {//n_printf("init PropertySection\n");
									}
    break;

  case 7:

    {//n_printf("in ParameterSection,left\n"); 
														}
    break;

  case 8:

    {//n_printf("from ParameterSection to PropertySection\n");
									}
    break;

  case 9:

    { //n_printf("out ParameterSection,right\n");
									}
    break;

  case 10:

    {	g_curGenesisMakeMaterial->SetRenderQueue(Graphic::RenderQueue::FromString((yyvsp[(3) - (3)].str)));
															//n_printf("in PropertySection,setrenderqueue:%s\n", Util::String($3).AsCharPtr()); 
														}
    break;

  case 11:

    {	//n_printf("in TechniqueSection,left\n");
														g_curGenesisMakeTechnique = new GenesisMakeTechnique(); 
													}
    break;

  case 12:

    {//n_printf("from TechniqueSection to PropertySection\n");
									}
    break;

  case 13:

    {	//n_printf("in TechniqueSection,left\n");
														g_curGenesisMakeTechnique = new GenesisMakeTechnique();
														g_curGenesisMakeTechnique->SetName((yyvsp[(3) - (4)].str)); 
													}
    break;

  case 14:

    {//n_printf("from TechniqueSection to PropertySection\n");
									}
    break;

  case 15:

    {//n_printf("init ParameterSection\n");
										}
    break;

  case 16:

    { if((yyvsp[(2) - (5)].spt) == Graphic::eShaderParamTexture2D)
																		{
																			g_curMatParam = new Graphic::MaterialParamTex2D();
																		}
																		else if((yyvsp[(2) - (5)].spt) == Graphic::eShaderParamTextureCUBE)
																		{
																			g_curMatParam = new Graphic::MaterialParamTexCube();
																		}
																		else if((yyvsp[(2) - (5)].spt) == Graphic::eShaderParamTexture1D)
																		{
																			g_curMatParam = new Graphic::MaterialParamTex1D();
																		}
																		else if((yyvsp[(2) - (5)].spt) == Graphic::eShaderParamTexture3D)
																		{
																			g_curMatParam = new Graphic::MaterialParamTex3D();
																		}
																		else
																		{
																			n_error("GenesisShader Parser : Invalid Texture Type !");
																		}
																		
																		g_curMatParam->SetName((yyvsp[(3) - (5)].str));
																		g_curMatParam->SetDesc((yyvsp[(3) - (5)].str));
																		g_curMatParam->SetStringValue((yyvsp[(5) - (5)].str));
																		//n_printf("define texture\n");
																		g_curGenesisMakeMaterial->AddMatParam(g_curMatParam);
																		g_curMatParam = NULL;

                                                                        if ((yyvsp[(2) - (5)].spt) == Graphic::eShaderParamTexture2D)
                                                                        {
																		char texOffestScaleValue[] = "0.0,0.0,1.0,1.0";
																		Util::String texOffestScale;
																		texOffestScale.Clear();
																		texOffestScale.Format("%s_UV_OffsetScale",(yyvsp[(3) - (5)].str));

																		g_curMatParam = new Graphic::MaterialParamVector();
																		g_curMatParam->SetName(texOffestScale);
																		g_curMatParam->SetDesc(texOffestScale);
																		g_curMatParam->SetStringValue(texOffestScaleValue);
																		g_curGenesisMakeMaterial->AddMatParam(g_curMatParam);
																		g_curMatParam = NULL;
                                                                        }

																		}
    break;

  case 17:

    { if((yyvsp[(2) - (6)].spt) == Graphic::eShaderParamTexture2D)
																		{
																			g_curMatParam = new Graphic::MaterialParamTex2D();
																		}
																		else if((yyvsp[(2) - (6)].spt) == Graphic::eShaderParamTextureCUBE)
																		{
																			g_curMatParam = new Graphic::MaterialParamTexCube();
																		}
																		else if((yyvsp[(2) - (6)].spt) == Graphic::eShaderParamTexture1D)
																		{
																			g_curMatParam = new Graphic::MaterialParamTex1D();
																		}
																		else if((yyvsp[(2) - (6)].spt) == Graphic::eShaderParamTexture3D)
																		{
																			g_curMatParam = new Graphic::MaterialParamTex3D();
																		}
																		else
																		{
																			n_error("GenesisShader Parser : Invalid Texture Type !");
																		}
																		
																		g_curMatParam->SetName((yyvsp[(3) - (6)].str));
																		g_curMatParam->SetDesc((yyvsp[(4) - (6)].str));
																		g_curMatParam->SetStringValue((yyvsp[(6) - (6)].str));
																		//n_printf("define texture\n");
																		g_curGenesisMakeMaterial->AddMatParam(g_curMatParam);
																		g_curMatParam = NULL;

                                                                        if ((yyvsp[(2) - (6)].spt) == Graphic::eShaderParamTexture2D)
                                                                        {
																		char texOffestScaleValue[] = "0.0,0.0,1.0,1.0";
																		Util::String texOffestScale;
																		texOffestScale.Clear();
																		texOffestScale.Format("%s_UV_OffsetScale",(yyvsp[(3) - (6)].str));

																		g_curMatParam = new Graphic::MaterialParamVector();
																		g_curMatParam->SetName(texOffestScale);
																		g_curMatParam->SetDesc(texOffestScale);
																		g_curMatParam->SetStringValue(texOffestScaleValue);
																		g_curGenesisMakeMaterial->AddMatParam(g_curMatParam);
																		g_curMatParam = NULL;
                                                                        }

																		}
    break;

  case 18:

    { g_curMatParam = new Graphic::MaterialParamMatrix();
																		g_curMatParam->SetName((yyvsp[(3) - (6)].str));
																		g_curMatParam->SetDesc((yyvsp[(4) - (6)].str));
																		g_curMatParam->SetStringValue((yyvsp[(6) - (6)].str));
																		
																		g_curGenesisMakeMaterial->AddMatParam(g_curMatParam);
																		g_curMatParam = NULL;
																		}
    break;

  case 19:

    { g_curMatParam = new Graphic::MaterialParamMatrix();
																		g_curMatParam->SetName((yyvsp[(3) - (5)].str));
																		g_curMatParam->SetDesc((yyvsp[(3) - (5)].str));
																		g_curMatParam->SetStringValue((yyvsp[(5) - (5)].str));
																		
																		g_curGenesisMakeMaterial->AddMatParam(g_curMatParam);
																		g_curMatParam = NULL;
																		}
    break;

  case 20:

    { g_curMatParam = new Graphic::MaterialParamVector();
																		g_curMatParam->SetName((yyvsp[(3) - (6)].str));
																		g_curMatParam->SetDesc((yyvsp[(4) - (6)].str));
																		g_curMatParam->SetStringValue((yyvsp[(6) - (6)].str));
																		
																		g_curGenesisMakeMaterial->AddMatParam(g_curMatParam);
																		g_curMatParam = NULL;
																		}
    break;

  case 21:

    { g_curMatParam = new Graphic::MaterialParamVector();
																		g_curMatParam->SetName((yyvsp[(3) - (5)].str));
																		g_curMatParam->SetDesc((yyvsp[(3) - (5)].str));
																		g_curMatParam->SetStringValue((yyvsp[(5) - (5)].str));
																		
																		g_curGenesisMakeMaterial->AddMatParam(g_curMatParam);
																		g_curMatParam = NULL;
																		}
    break;

  case 22:

    { g_curMatParam = new Graphic::MaterialParamFloat();
																		g_curMatParam->SetName((yyvsp[(3) - (6)].str));
																		g_curMatParam->SetDesc((yyvsp[(4) - (6)].str));
																		g_curMatParam->SetStringValue((yyvsp[(6) - (6)].str));
																			
																		g_curGenesisMakeMaterial->AddMatParam(g_curMatParam);
																		g_curMatParam = NULL;
																		}
    break;

  case 23:

    { g_curMatParam = new Graphic::MaterialParamFloat();
																		g_curMatParam->SetName((yyvsp[(3) - (5)].str));
																		g_curMatParam->SetDesc((yyvsp[(3) - (5)].str));
																		g_curMatParam->SetStringValue((yyvsp[(5) - (5)].str));
																			
																		g_curGenesisMakeMaterial->AddMatParam(g_curMatParam);
																		g_curMatParam = NULL;
																		}
    break;

  case 24:

    { //n_printf("init TechniqueSection\n");
									 }
    break;

  case 25:

    { //n_printf("from PassSection to TechniqueSection\n"); 
									}
    break;

  case 26:

    { //n_printf("out TechniqueSection,right\n");
									  g_curGenesisMakeMaterial->AddTechnique(*g_curGenesisMakeTechnique);
										delete g_curGenesisMakeTechnique;
										g_curGenesisMakeTechnique = 0; 
									}
    break;

  case 27:

    { //n_printf("init PassSection\n");
									}
    break;

  case 28:

    { printf("set MatType\n");
													g_curGenesisMakeTechnique->SetIsMatTemplate((yyvsp[(3) - (3)].str));
												}
    break;

  case 29:

    { //n_printf("init Pass\n");
												}
    break;

  case 30:

    { //n_printf("in PassSection,left\n");
									  
									}
    break;

  case 31:

    { //n_printf("from codeSection to PassSection\n");
									}
    break;

  case 32:

    {
										//n_printf("out PassSection,right\n");
										g_curGenesisMakeTechnique->AddPass(*g_curMakePass); 
										delete g_curMakePass;
										g_curMakePass = 0; 
									}
    break;

  case 33:

    {
											n_printf("in PassSection,left\n");
											g_curMakePass = new GenesisMakePass(); 
											g_curMakePass->SetName("NoName");
										}
    break;

  case 34:

    {
											n_printf("in PassSection,left\n");
											g_curMakePass = new GenesisMakePass(); 
											g_curMakePass->SetName((yyvsp[(2) - (2)].str));
										}
    break;

  case 35:

    { //n_printf("in codeSection\n");
									}
    break;

  case 36:

    { //n_printf("from shadertype,to StateSection\n"); 
									}
    break;

  case 37:

    { //n_printf("from shadertype,to shadertype\n"); 
									}
    break;

  case 38:

    { //n_printf("in StateSection\n");
									}
    break;

  case 39:

    { 
												g_rsDesc = RenderBase::RenderStateDesc::Create();
												g_rsDesc->Setup(); 
												//n_printf("Create StateSection\n");//n_printf("init StateSection\n");
											}
    break;

  case 40:

    { }
    break;

  case 41:

    {
												g_curMakePass->SetRenderStateDesc(g_rsDesc);
												g_rsDesc = 0;
												//n_printf("from RenderStateSetup,to shadertype\n");
											}
    break;

  case 42:

    { //n_printf("in RenderStateSetup\n");
									}
    break;

  case 43:

    {   RenderBase::DeviceRasterizerState rrs = g_rsDesc->GetRasterizerState();
															rrs.m_cullMode = RenderBase::CullModeConverter::FromString((yyvsp[(3) - (3)].str));	
															
															g_rsDesc->SetRasterizerState(rrs);
														}
    break;

  case 44:

    {   RenderBase::DeviceRasterizerState rrs = g_rsDesc->GetRasterizerState();
															rrs.m_fillMode = RenderBase::FillModeConverter::FromString((yyvsp[(3) - (3)].str));	
															
															g_rsDesc->SetRasterizerState(rrs);
														}
    break;

  case 45:

    {   RenderBase::DeviceBlendState rbs = g_rsDesc->GetBlendState();
															rbs.m_colorWriteMask[0] = RenderBase::ColorMaskConverter::FromString((yyvsp[(3) - (3)].str));	
															
															g_rsDesc->SetBlendState(rbs);
														}
    break;

  case 46:

    { //n_printf("set depthtest complete \n");
														}
    break;

  case 47:

    {   RenderBase::DeviceDepthAndStencilState rdss = g_rsDesc->GetDepthAndStencilState();
																rdss.m_depthWriteMask = (yyvsp[(3) - (3)].boolean);	
																
																g_rsDesc->SetDepthAndStencilState(rdss);
															}
    break;

  case 48:

    {  //n_printf("set blendmode complete \n"); 
														}
    break;

  case 49:

    { //n_printf("set alphatest complete \n");
														}
    break;

  case 50:

    { //n_printf("set samplerstate complete \n");
														}
    break;

  case 51:

    { g_curGenesisMakeMaterial->AddTextureSampler((yyvsp[(2) - (3)].str),RenderBase::TextureAddressModeConverter::FromString((yyvsp[(3) - (3)].str)));
														 
														}
    break;

  case 52:

    {
																	g_curGenesisMakeMaterial->AddTextureSampler((yyvsp[(2) - (4)].str),RenderBase::TextureAddressModeConverter::FromString((yyvsp[(3) - (4)].str)),RenderBase::TextureFilterOperationConverter::FromString((yyvsp[(4) - (4)].str)));
																	
																}
    break;

  case 53:

    {   
															RenderBase::DeviceDepthAndStencilState rdss = g_rsDesc->GetDepthAndStencilState();
															rdss.m_depthEnable = true;
															rdss.m_zFunc = RenderBase::CompareFunctionConverter::FromString((yyvsp[(2) - (2)].str));			
															
															g_rsDesc->SetDepthAndStencilState(rdss);
											}
    break;

  case 54:

    {
															RenderBase::DeviceDepthAndStencilState rdss = g_rsDesc->GetDepthAndStencilState();
															rdss.m_depthEnable = (yyvsp[(2) - (2)].boolean);		
															
															g_rsDesc->SetDepthAndStencilState(rdss);
											}
    break;

  case 55:

    {
																	RenderBase::DeviceBlendState rbs = g_rsDesc->GetBlendState();
																	rbs.m_alphaBlendEnable[0] = true;
																	rbs.m_blendOP[0] = RenderBase::BlendOperationConverter::FromString((yyvsp[(2) - (4)].str));
																	rbs.m_srcBlend[0] = RenderBase::AlphaBlendFactorConverter::FromString((yyvsp[(3) - (4)].str));
																	rbs.m_destBlend[0] = RenderBase::AlphaBlendFactorConverter::FromString((yyvsp[(4) - (4)].str));	
																	
																	g_rsDesc->SetBlendState(rbs);		
																}
    break;

  case 56:

    {
																	RenderBase::DeviceBlendState rbs = g_rsDesc->GetBlendState();
																	rbs.m_alphaBlendEnable[0] = (yyvsp[(2) - (2)].boolean);
																	
																	g_rsDesc->SetBlendState(rbs);		
																}
    break;

  case 57:

    {
																	RenderBase::DeviceBlendState rbs = g_rsDesc->GetBlendState();
																	rbs.m_alphaTestEnable = true;
																	rbs.m_alphaFunc = RenderBase::CompareFunctionConverter::FromString((yyvsp[(2) - (3)].str));
																	const Util::String& valueStr = g_curGenesisMakeMaterial->GetMatParamValueByName((yyvsp[(3) - (3)].str));
																	if(!valueStr.IsValidFloat() || valueStr.IsEmpty())
																	{
																		n_error("Invalid alpha_to_coverage_ref value!please check your parameter type(float) and name!");
																	}
																	else
																	{
																		rbs.m_alphaRef = valueStr.AsFloat();
																	}
																	
																	
																	g_rsDesc->SetBlendState(rbs);
																}
    break;

  case 58:

    {
																	RenderBase::DeviceBlendState rbs = g_rsDesc->GetBlendState();
																	rbs.m_alphaTestEnable = (yyvsp[(2) - (2)].boolean);
																	
																	g_rsDesc->SetBlendState(rbs);
																}
    break;

  case 59:

    {
											g_curGenesisMakeGPUProgram = new GenesisMakeGPUProgram();
											g_curGenesisMakeGPUProgram->SetShaderType((yyvsp[(2) - (2)].str));
											//n_printf("in shaderType,SetShaderType\n");
											delete[] (yyvsp[(2) - (2)].str);
										}
    break;

  case 60:

    { //n_printf("in shaderType,left\n");
										}
    break;

  case 61:

    { //n_printf("from DeviceTypeSetup to shaderType\n");
										}
    break;

  case 62:

    { 
											if(g_curGenesisMakeGPUProgram != NULL)
											{
												delete g_curGenesisMakeGPUProgram;
												g_curGenesisMakeGPUProgram = NULL;
											}
											//n_printf("out shaderType,right\n");
										}
    break;

  case 63:

    {	n_printf("in DeviceTypeSetup\n");}
    break;

  case 64:

    { 
											g_curGenesisMakeGPUProgram->SetDeviceType((yyvsp[(3) - (3)].str));
											//n_printf("in DeviceTypeSetup\n");
											delete[] (yyvsp[(3) - (3)].str);
											}
    break;

  case 65:

    { //n_printf("in DeviceTypeSetup,left\n");
										}
    break;

  case 66:

    { //n_printf("from CodeBlock to DeviceTypeSetup\n");
										}
    break;

  case 67:

    { //n_printf("out DeviceTypeSetup,right\n");
										  g_curMakePass->AddShaderProgram(*g_curGenesisMakeGPUProgram);
										}
    break;

  case 68:

    { //n_printf("in CodeBlock\n");
										}
    break;

  case 69:

    { 
												g_curGenesisMakeGPUProgram->SetShaderCode((yyvsp[(3) - (3)].str));
												//n_printf("in CodeBlock,AddGPUProgram\n");
												delete[] (yyvsp[(3) - (3)].str);
											 }
    break;

  case 70:

    { g_curShaderParameter = new Graphic::ShaderParam();
																		  g_curShaderParameter->SetParamType((yyvsp[(5) - (5)].spt));
																		  g_curShaderParameter->SetRegister((yyvsp[(3) - (5)].num));
																		  g_curShaderParameter->SetName((yyvsp[(4) - (5)].str));
																		  g_curGenesisMakeGPUProgram->AddParam(*g_curShaderParameter);
																		  //n_printf("bind texture\n"); delete[] $4;
																		  delete g_curShaderParameter;
																		  g_curShaderParameter = 0;
																		 }
    break;

  case 71:

    {	g_curShaderParameter = new Graphic::ShaderParam();
																			g_curShaderParameter->SetParamType((yyvsp[(5) - (5)].spt));
																			g_curShaderParameter->SetRegister((yyvsp[(3) - (5)].num));
																			g_curShaderParameter->SetName((yyvsp[(4) - (5)].str));
																			g_curGenesisMakeGPUProgram->AddParam(*g_curShaderParameter);
																			//n_printf("setparam matrix register\n"); delete[] $4;
																			delete g_curShaderParameter;
																			g_curShaderParameter = 0;
																		}
    break;

  case 72:

    {	g_curShaderParameter = new Graphic::ShaderParam();
																			g_curShaderParameter->SetParamType((yyvsp[(5) - (5)].spt));
																			g_curShaderParameter->SetRegister((yyvsp[(3) - (5)].num));
																			g_curShaderParameter->SetName((yyvsp[(4) - (5)].str));
																			g_curGenesisMakeGPUProgram->AddParam(*g_curShaderParameter);
																			//n_printf("setparam vector register\n"); delete[] $4;
																			delete g_curShaderParameter;
																			g_curShaderParameter = 0;
																		}
    break;

  case 73:

    {	g_curShaderParameter = new Graphic::ShaderParam();
																			g_curShaderParameter->SetParamType((yyvsp[(5) - (5)].spt));
																			g_curShaderParameter->SetRegister((yyvsp[(3) - (5)].num));
																			g_curShaderParameter->SetName((yyvsp[(4) - (5)].str));
																			g_curGenesisMakeGPUProgram->AddParam(*g_curShaderParameter);
																			//n_printf("setparam float register\n"); delete[] $4;
																			delete g_curShaderParameter;
																			g_curShaderParameter = 0;
																		}
    break;



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
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
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





int yyerror (const char *s)
{
	n_printf("GenesisShader Error: %s At line:%d\n",s,Genesislineno);
	return 0;
}

void ResetParserParams()
{

	if(g_curGenesisMakeGPUProgram != NULL)
	{
		delete g_curGenesisMakeGPUProgram;
		g_curGenesisMakeGPUProgram = NULL;
	}
	
	if(g_curShaderParameter != NULL)
	{
		delete g_curShaderParameter;
		g_curShaderParameter = NULL;
	}
	
	if(g_curMatParam != NULL)
	{
		delete g_curMatParam;
		g_curMatParam = NULL;
	}
	
	if(g_rsDesc.isvalid())
	{
		g_rsDesc = 0;
	}
	
	if(g_curMakePass != NULL)
	{
		delete g_curMakePass;
		g_curMakePass = NULL;
	}
	
	if(g_curGenesisMakeTechnique != NULL)
	{
		delete g_curGenesisMakeTechnique;
		g_curGenesisMakeTechnique = NULL;
	}
	
	if(g_curGenesisMakeMaterial != NULL)
	{
		delete g_curGenesisMakeMaterial;
		g_curGenesisMakeMaterial = NULL;
	}

}

