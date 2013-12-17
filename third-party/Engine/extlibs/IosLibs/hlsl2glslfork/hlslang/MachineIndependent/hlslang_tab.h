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
/* Line 1529 of yacc.c.  */
#line 314 "hlslang_tab.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



