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
     DEGREE_COURSES_SECTION = 258,
     CANDIDATES_SECTION = 259,
     DEGREE_COURSE = 260,
     END_COURSE_REQUIREMENTS = 261,
     CANDIDATE_NAME_PROPERTY = 262,
     CANDIDATE_FISCAL_CODE_PROPERTY = 263,
     CANDIDATE_BIRTHDATE_PROPERTY = 264,
     CANDIDATE_HIGH_SCHOOL_VOTE_PROPERTY = 265,
     CANDIDATE_TEST_VOTE_PROPERTY = 266,
     CANDIDATE_COURSE_PROPERTY = 267,
     CANDIDATE_COURSE_PROPERTY_START = 268,
     CANDIDATE_COURSE_PROPERTY_END = 269,
     END_CANDIDATE_GENERAL_INFORMATION = 270,
     CANDIDATE_END_PROPERTY = 271,
     DIVEDER = 272,
     END_CANDIDATE_PROPERTY = 273,
     EQUAL_TO = 274,
     ACADEMIC_YEAR = 275,
     FISCAL_CODE = 276,
     INT = 277,
     FLOAT = 278,
     DATE_VALUE = 279,
     STRING_VALUE = 280,
     ARROW = 281
   };
#endif
/* Tokens.  */
#define DEGREE_COURSES_SECTION 258
#define CANDIDATES_SECTION 259
#define DEGREE_COURSE 260
#define END_COURSE_REQUIREMENTS 261
#define CANDIDATE_NAME_PROPERTY 262
#define CANDIDATE_FISCAL_CODE_PROPERTY 263
#define CANDIDATE_BIRTHDATE_PROPERTY 264
#define CANDIDATE_HIGH_SCHOOL_VOTE_PROPERTY 265
#define CANDIDATE_TEST_VOTE_PROPERTY 266
#define CANDIDATE_COURSE_PROPERTY 267
#define CANDIDATE_COURSE_PROPERTY_START 268
#define CANDIDATE_COURSE_PROPERTY_END 269
#define END_CANDIDATE_GENERAL_INFORMATION 270
#define CANDIDATE_END_PROPERTY 271
#define DIVEDER 272
#define END_CANDIDATE_PROPERTY 273
#define EQUAL_TO 274
#define ACADEMIC_YEAR 275
#define FISCAL_CODE 276
#define INT 277
#define FLOAT 278
#define DATE_VALUE 279
#define STRING_VALUE 280
#define ARROW 281




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 9 "parser.y"
{
    int integer;
    char* str;
}
/* Line 1529 of yacc.c.  */
#line 106 "parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE yylloc;
