%{
    #include <stdlib.h>
    #include <stdio.h>
    #include "symb_tab.h"
    int yylex();
    void yyerror (char *s);
%}

%union{
    float flt;
    char* str;
}

%type <flt> INT FLOAT
%type <str> STRING_VALUE FISCAL_CODE DATE_VALUE ACADEMIC_YEAR

%token YEAR FIRST_STEP BAND START_INF ARROW MC EURO INT FLOAT
%token SECOND_STEP START_EXTRA ELE_ENE SEWER COUNTER DOT IVA PER NA_PER FIS_COD
%token THIRD_STEP COLUMN

%locations

%%
main: first_section FIRST_STEP second_section SECOND_STEP  third_section THIRD_STEP people;
first_section: YEAR INT;

second_section: 
  | second_section band;
  
band: BAND INT START_INF INT ARROW INT ARROW EURO FLOAT MC { ins_band($2, $4, $6, $9);}
	| BAND INT START_INF FLOAT ARROW INT ARROW EURO FLOAT MC { ins_band($2, $4, $6, $9);}
	| BAND INT START_INF INT ARROW FLOAT ARROW EURO FLOAT MC { ins_band($2, $4, $6, $9);}
	| BAND INT START_INF FLOAT ARROW FLOAT ARROW EURO FLOAT MC { ins_band($2, $4, $6, $9);}
	|   BAND INT START_INF INT ARROW ARROW EURO FLOAT MC{ ins_band($2, $4, 0, $8);};
	|   BAND INT START_INF FLOAT ARROW ARROW EURO FLOAT MC{ ins_band($2, $4, 0, $8);};

third_section: START_EXTRA ELE_ENE START_INF EURO FLOAT MC SEWER START_INF EURO FLOAT MC COUNTER START_INF EURO FLOAT DOT IVA START_INF INT PER DOT{ins_extra( $5, $10, $15, $19);};

people: | people NA_PER COLUMN FIS_COD COLUMN FLOAT COLUMN FLOAT {ins_person($2, $4, $8-$6);};
	| people NA_PER COLUMN FIS_COD COLUMN INT COLUMN INT {ins_person($2, $4, $8-$6);};
%%
extern int current_line;
yyerror(char *s) {
    printf("Error at line %d: %s", current_line, s);
    exit(1);
    //print_sym_table();
}
int main() {
    if (yyparse()==0){
        print_people();
    }
}
