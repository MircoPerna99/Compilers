%{
    #include "parser.tab.h"
    int current_line = 0;
%}
%option noyywrap
%x lossyBig
Academic_Year [0-9]{4}\/[0-9]{2}
Arrow "->"
Course_Of_Study_Parameters_Section "%%"
Candidate_Parameters_Section "$$$"
Integer 0|[1-9][0-9]*
Fiscal_Code [A-Z]{6}[0-9]{2}[A-Z][0-9]{2}[A-Z][0-9]{3}[A-Z] 
Candidate ([A-Z][a-z]*)([ ][A-Z][a-z]*)*
String_Value ([A-Z][a-z]*)([ ][A-Z][a-z]*)*
Date_Value (0[1-9]|1[0-9]|2[0-9]|3[01])\/(0[1-9]|1[0-2])\/[0-9]{4}
Divider_Course_Requirements ";"
Dot "."
Equal_To ":"
Candidate_Name_Property "Nome e Cognome"
Candidate_Fiscal_Code_Property "Codice Fiscale"
Candidate_Birthdate_Property  "Data di Nascita"
Candidate_Degree_Vote_Property "Voto di Laurea"
Candidate_Test_Vote_Property "Voto di Test"
Candidate_Course_Property "Iscrizione corsi di laurea"
Candidate_Course_Property_Start "("
Candidate_Course_Property_End ")"
Candidate_End_Propery "!!!"
Comma ","
%s Year_Section
%s Degree_Courses_Section
%s Candidates_Section
%%
{Course_Of_Study_Parameters_Section} {BEGIN(Degree_Courses_Section);return (DEGREE_COURSES_SECTION);}
{Candidate_Parameters_Section} {BEGIN(Candidates_Section); return (CANDIDATES_SECTION);}

<Degree_Courses_Section>{String_Value} {return (DEGREE_COURSE); }
<Degree_Courses_Section>{Divider_Course_Requirements} {return (DIVEDER); }
<Degree_Courses_Section>{Dot} {return (END_COURSE_REQUIREMENTS); }

<Candidates_Section>{Candidate_Name_Property} {return (CANDIDATE_NAME_PROPERTY); }
<Candidates_Section>{Candidate_Fiscal_Code_Property} {return (CANDIDATE_FISCAL_CODE_PROPERTY); }
<Candidates_Section>{Candidate_Birthdate_Property} {return (CANDIDATE_BIRTHDATE_PROPERTY); }
<Candidates_Section>{Candidate_Degree_Vote_Property} {return (CANDIDATE_DEGREE_VOTE_PROPERTY); }
<Candidates_Section>{Candidate_Test_Vote_Property} {return (CANDIDATE_TEST_VOTE_PROPERTY); }
<Candidates_Section>{Candidate_Course_Property} {return (CANDIDATE_COURSE_PROPERTY); }
<Candidates_Section>{Candidate_Course_Property_Start} {return (CANDIDATE_COURSE_PROPERTY_START); }
<Candidates_Section>{Candidate_Course_Property_End} {return (CANDIDATE_COURSE_PROPERTY_END); }
<Candidates_Section>{Candidate_End_Propery} {return (CANDIDATE_END_PROPERTY); }
<Candidates_Section>{Comma} {return (DIVEDER); }
<Candidates_Section>{Dot} {return (END_CANDIDATE_GENERAL_INFORMATION); }
<Candidates_Section>{Equal_To} {return (EQUAL_TO); }

 
{Academic_Year} {return (ACADEMIC_YEAR);}
{Fiscal_Code} {yylval.str=strdup(yytext); return (FISCAL_CODE); }
{Integer}  { yylval.integer=atoi(yytext);return (INT); }
{Date_Value} { yylval.str=strdup(yytext); return (DATE_VALUE); }
{String_Value} {yylval.str=strdup(yytext);return (STRING_VALUE);}
{Arrow} {return (ARROW);}
" " {}
\n {current_line++;}
. {printf("errore lexer alla riga %d: \"%s\" inaspettato", current_line, yytext); exit(1);}
%%