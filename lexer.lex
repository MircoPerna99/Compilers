%option noyywrap
%x lossyBig
Academic_Year [0-9]{4}\/[0-9]{2}
Arrow "->"
Course_Of_Study_Parameters_Section "%%"
Candidate_Parameters_Section "$$$"
Integer 0|[1-9][0-9]*
Decimal {Integer}[,][0-9]{1,2}
Fiscal_Code [A-Z]{6}[0-9]{2}[A-Z][0-9]{2}[A-Z][0-9]{3}[A-Z] 
Candidate ([A-Z][a-z]*)([ ][A-Z][a-z]*)*
String_Value ([A-Z][a-z]*)([ ][A-Z][a-z]*)*
Date_Value (0[1-9]|1[0-9]|2[0-9]|3[01])\/(0[1-9]|1[0-2])\/[0-9]{4}
Divider_Course_Requirements ";"
Dot "."
Equal_To ":"
Candidate_Name_Property "Nome e Cognome"
Candidate_Fiscal_Code_Property "Codice Fiscale"
Candidate_Birthdate_Property  "Data di nascita"
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
{Course_Of_Study_Parameters_Section} {BEGIN(Degree_Courses_Section);fputs("DEGRE_COURSES_SECTION", yyout);}
{Candidate_Parameters_Section} {BEGIN(Candidates_Section); fputs("CANDIDATES_SECTION", yyout);}

<Degree_Courses_Section>{String_Value} {fputs("DEGREE_COURSE", yyout); }
<Degree_Courses_Section>{Divider_Course_Requirements} {fputs("DIVEDER", yyout); }
<Degree_Courses_Section>{Dot} {fputs("END_COURSE_REQUIREMENTS", yyout); }

<Candidates_Section>{Candidate_Name_Property} {fputs("CANDIDATE_NAME_PROPERTY", yyout); }
<Candidates_Section>{Candidate_Fiscal_Code_Property} {fputs("CANDIDATE_FISCAL_CODE_PROPERTY", yyout); }
<Candidates_Section>{Candidate_Birthdate_Property} {fputs("CANDIDATE_BIRTHDATE_PROPERTY", yyout); }
<Candidates_Section>{Candidate_Degree_Vote_Property} {fputs("CANDIDATE_DEGREE_VOTE_PROPERTY", yyout); }
<Candidates_Section>{Candidate_Test_Vote_Property} {fputs("CANDIDATE_TEST_VOTE_PROPERTY", yyout); }
<Candidates_Section>{Candidate_Course_Property} {fputs("CANDIDATE_COURSE_PROPERTY", yyout); }
<Candidates_Section>{Candidate_Course_Property_Start} {fputs("CANDIDATE_COURSE_PROPERTY_START", yyout); }
<Candidates_Section>{Candidate_Course_Property_End} {fputs("CANDIDATE_COURSE_PROPERTY_END", yyout); }
<Candidates_Section>{Candidate_End_Propery} {fputs("CANDIDATE_END_PROPERY", yyout); }
<Candidates_Section>{Comma} {fputs("DIVEDER", yyout); }
<Candidates_Section>{Dot} {fputs("END_CANDIDATE_PROPERTY", yyout); }
<Candidates_Section>{Equal_To} {fputs("EQUAL_TO", yyout); }

 
{Academic_Year} {fputs("ACADEMIC_YEAR", yyout);}
{Fiscal_Code} {fputs("FISCAL_CODE", yyout); }
{Integer}  {fputs("INT", yyout); }
{Decimal} {fputs("FLOAT", yyout); }
{Date_Value} {fputs("DATE_VALUE", yyout); }
{String_Value} {fputs("STRING_VALUE", yyout);}
{Arrow} {fputs("ARROW", yyout);}
%%

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Uso: %s input.txt output.txt\n", argv[0]);
        return 1;
    }

    FILE *in = fopen(argv[1], "r");
    if (!in) {
        perror("Errore apertura file input");
        return 1;
    }

    FILE *out = fopen(argv[2], "w");
    if (!out) {
        perror("Errore apertura file output");
        fclose(in);
        return 1;
    }

    yyin = in;
    yyout = out;

    yylex();

    fclose(in);
    fclose(out);
    return 0;
}