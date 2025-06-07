%{
    #include <stdlib.h>
    #include <stdio.h>
    #include "symb_tab.h"
    int yylex();
    void yyerror (char *s);
%}

%union{
    int integer;
    char* str;
}

%type <integer> INT
%type <str> STRING_VALUE FISCAL_CODE DATE_VALUE DEGREE_COURSE

%token DEGREE_COURSES_SECTION CANDIDATES_SECTION DEGREE_COURSE END_COURSE_REQUIREMENTS 
%token CANDIDATE_NAME_PROPERTY CANDIDATE_FISCAL_CODE_PROPERTY CANDIDATE_BIRTHDATE_PROPERTY
%token CANDIDATE_DEGREE_VOTE_PROPERTY CANDIDATE_TEST_VOTE_PROPERTY CANDIDATE_COURSE_PROPERTY
%token CANDIDATE_COURSE_PROPERTY_START CANDIDATE_COURSE_PROPERTY_END END_CANDIDATE_GENERAL_INFORMATION CANDIDATE_END_PROPERTY
%token DIVEDER END_CANDIDATE_PROPERTY EQUAL_TO ACADEMIC_YEAR FISCAL_CODE INT FLOAT
%token DATE_VALUE STRING_VALUE ARROW 

%locations

%%
main: ACADEMIC_YEAR  DEGREE_COURSES_SECTION Degree_Courses_Section CANDIDATES_SECTION Candidates_Section

Degree_Courses_Section:  | Degree_Courses_Section Degre_Course
Degre_Course: DEGREE_COURSE ARROW INT DIVEDER INT DIVEDER INT END_COURSE_REQUIREMENTS{insert_course($1, $3, $5, $7);} 

Candidates_Section: | Candidates_Section Candidate_Properties;
Candidate_Properties: Candidate Fiscal_Code Birthdate Degree_Vote Test_Vote Selected_Courses CANDIDATE_END_PROPERTY {insert_candidate();}

Candidate : CANDIDATE_NAME_PROPERTY EQUAL_TO STRING_VALUE DIVEDER  {insert_candidate_name($3);} 
Fiscal_Code : CANDIDATE_FISCAL_CODE_PROPERTY EQUAL_TO FISCAL_CODE DIVEDER  {insert_candidate_fiscal_code($3);} 
Birthdate : CANDIDATE_BIRTHDATE_PROPERTY EQUAL_TO DATE_VALUE DIVEDER {insert_candidate_birthdate($3);} 
Degree_Vote : CANDIDATE_DEGREE_VOTE_PROPERTY EQUAL_TO INT DIVEDER {insert_candidate_degree_vote($3);} 
Test_Vote : CANDIDATE_TEST_VOTE_PROPERTY EQUAL_TO INT END_CANDIDATE_GENERAL_INFORMATION {insert_candidate_test_vote($3);} 
Selected_Courses : CANDIDATE_COURSE_PROPERTY EQUAL_TO CANDIDATE_COURSE_PROPERTY_START Courses CANDIDATE_COURSE_PROPERTY_END END_CANDIDATE_GENERAL_INFORMATION
Courses : Course_Selected  | Courses DIVEDER Course_Selected 
Course_Selected : STRING_VALUE {insert_candidate_course_selected($1);} 
%%
extern int current_line;

void yyerror(char *s) {
    printf("Error at line %d: %s", current_line, s);
    exit(1);
    //print_sym_table();
}
int main() {
    if (yyparse()==0){
        calculate_ranking();
        print_ranking();
    }
}
