#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symb_tab.h"

candidate *candidate_to_insert;
char *academic_year;

float calculate_points(int high_school_vote_candidate, int test_vote_candidate,  int high_school_vote_course, int test_vote_course)
{
	return (((float)(high_school_vote_candidate*high_school_vote_course)/100)+ ((float)(high_school_vote_course*test_vote_course)/100));
}

int check_date(char *data1, char *data2) {
    int g1, m1, a1, g2, m2, a2;

    sscanf(data1, "%d/%d/%d", &g1, &m1, &a1);
    sscanf(data2, "%d/%d/%d", &g2, &m2, &a2);

    if (a1 != a2) return a1 - a2;
    if (m1 != m2) return m1 - m2;
    return g1 - g2;
}

int check_node(ranking_course *ranking, ranking_course *new_ranking)
{
	if(ranking->score > new_ranking -> score)
	{
		return 1;
	}
	else if(ranking->score == new_ranking -> score)
	{
		return check_date(ranking->birth_date, new_ranking->birth_date) > 0 ? 1 : -1;
	}
	else
	{
		return -1;
	}
}

void check_course_data(course *new_course)
{
	if(new_course->amount_of_place_available<1 ||  new_course->amount_of_place_available>999)
	{
		printf("The number of available seats for course %s is not between 1 and 999.\n",new_course->name);
		exit(1);
	}

	if(new_course->high_school_vote<0 ||  new_course->high_school_vote>100)
	{
		printf("The high school grade percentage for course %s is not between 0 and 100.\n", new_course->name);
		exit(1);
	}

	if(new_course->test_vote<0 ||  new_course->test_vote>100)
	{
		printf("The test grade percentage for course %s is not between 0 and 100.\n", new_course->name);
		exit(1);
	}

	if(new_course->high_school_vote+new_course->test_vote > 100)
	{
		printf("The sum of diploma grade percentage and test grade percentage for course %s is larger than 100\n", new_course->name);
		exit(1);
	}
}

unsigned int hash(char *id) {
	int h=0;
	int a = 128;
	for(;*id!='\0';id++){
		h=(a*h+*id)%HASHSIZE;
		}
	return h;
}


candidate *lookup_candidate(char *fsc) {
	candidate *c;
	for (c = hash_table_candidates[hash(fsc)]; c != NULL; c = c->next){
		if (strcmp(fsc,c->fiscal_code) == 0){
			return c;
			}
		}

	return NULL;
}

course *lookup_course(char *name_course) {
	course *c;
	for (c = hash_table_courses[hash(name_course)]; c != NULL; c = c->next){
		if (strcmp(name_course,c->name) == 0){
			return c;
			}
		}
	
	return NULL;
}

int insert_academic_year(char *academic_year_input)
{
	academic_year = academic_year_input;
	return 1;
}

int insert_candidate(){	

	if(lookup_candidate(candidate_to_insert->fiscal_code)!=NULL){
	 	printf("The candidate %s has just been insterted into the symbol table\n", candidate_to_insert->fiscal_code);
	  	return 0;
	}

	unsigned int hash_index =  hash(candidate_to_insert->fiscal_code);

	candidate_to_insert->next = hash_table_candidates[hash_index];
    hash_table_candidates[hash_index] = candidate_to_insert;

	return 1;
}


int insert_candidate_name(char *name)
{
	if ((candidate_to_insert = (candidate *)malloc(sizeof(*candidate_to_insert)))==NULL)
		return 0;

	candidate_to_insert->name = name;

	return 1;
}

int insert_candidate_fiscal_code(char *fiscal_code)
{
	if (candidate_to_insert == NULL)
		return 0;

	candidate_to_insert->fiscal_code = fiscal_code;

	return 1;
}

int insert_candidate_birthdate(char *birth_date)
{
	if (candidate_to_insert ==NULL)
		return 0;

	candidate_to_insert->birth_date = birth_date;

	return 1;
}

int insert_candidate_high_school_vote(int high_school_vote)
{
	if (candidate_to_insert ==NULL)
		return 0;

	if(high_school_vote < 0 || high_school_vote > 100)
	{
		printf("Student %s's high school score is not between 0 and 100.\n", candidate_to_insert->name);
		exit(1);
	}
	
	candidate_to_insert->high_school_vote = high_school_vote;

	return 1;
}

int insert_candidate_test_vote(int test_vote)
{
	if (candidate_to_insert ==NULL)
		return 0;

	if(test_vote < 0 || test_vote > 100)
	{
		printf("Student %s's test score is not between 0 and 100.\n", candidate_to_insert->name);
		exit(1);
	}
	candidate_to_insert->test_vote = test_vote;
	return 1;
}

int insert_candidate_course_selected(char *course)
{
	if (candidate_to_insert == NULL)
		return 0;

	course_selected *new_course;
	if ((new_course = (course_selected *)malloc(sizeof(*new_course)))==NULL)
		return 0;
	
	new_course->name = course;
	new_course->next = candidate_to_insert->courses;
	candidate_to_insert->courses = new_course;

	return 1;
}


int insert_course(char *name_course, int amount_of_place_available, int high_school_vote, int test_vote){	

	if(lookup_course(name_course)!=NULL){
		printf("'%s' has just been insterted into the symbol table\n", name_course);
	 	return 0;
	} 

	unsigned int hash_index =  hash(name_course);

	course *new_course;

	if ((new_course = (course *)malloc(sizeof(*new_course)))==NULL)
		return 0;

	new_course->name = name_course;
	new_course->amount_of_place_available = amount_of_place_available;
	new_course->high_school_vote = high_school_vote;
	new_course->test_vote = test_vote;
	new_course->next = hash_table_courses[hash_index];

	check_course_data(new_course);

	hash_table_courses[hash_index] = new_course;

	return 1;
}

void calculate_ranking(){
	candidate *ptr;
	ranking_course *new_ranking;
	for(int i = 0; i<HASHSIZE;i++){
		for(ptr = hash_table_candidates[i]; ptr!=NULL; ptr = ptr->next){
					course_selected *candidate_courses_selected = ptr->courses;

					while(candidate_courses_selected)
					{
						course *c = lookup_course(candidate_courses_selected->name);

						if ((new_ranking = (ranking_course *)malloc(sizeof(*new_ranking)))==NULL)
						{
							printf("Error on calculate_ranking\n");
							exit(1);
						}

						if(c != NULL)
						{
							new_ranking->candidate_name = ptr->name;
							new_ranking->fiscal_code = ptr->fiscal_code;
							new_ranking->birth_date = ptr->birth_date;
							new_ranking->score = calculate_points(ptr->high_school_vote, ptr->test_vote, c->high_school_vote, c->test_vote);
							
							ranking_course *ranking = c->ranking;
							if(ranking == NULL)
							{
								ranking = new_ranking;
							}
							else
							{	

								if(check_node(ranking, new_ranking)<0)
								{
									new_ranking->next = ranking;
									ranking = new_ranking;
								}
								else
								{
									while(ranking->next != NULL)
									{
										if(check_node(ranking->next, new_ranking) > 0)
										{
											ranking = ranking->next;
										}
										else
										{
											new_ranking->next = ranking->next;
											ranking->next = new_ranking;
											break;
										}
									}

									if(ranking->next == NULL)
									{
										ranking->next = new_ranking;
									}
								}
							}
							c->ranking = ranking;
						}
						candidate_courses_selected = candidate_courses_selected->next;
					}
			}
	}
}

void print_candidates() {
	candidate *ptr;
	printf("Candidates:\n");
	
	
	for(int i = 0; i<HASHSIZE;i++){
		for(ptr = hash_table_candidates[i]; ptr!=NULL; ptr = ptr->next){
  	                printf("%s\n",ptr->fiscal_code);
					while(ptr->courses != NULL)
					{
						  printf("%s\n",ptr->courses->name);
						  ptr->courses = ptr->courses->next;
					}
		 }
	}
}

void print_courses() {
	course *ptr;
	printf("Courses:\n");
	
	
	for(int i = 0; i<HASHSIZE;i++){
		for(ptr = hash_table_courses[i]; ptr!=NULL; ptr = ptr->next){
  	                printf("%s\n",ptr->name);
		 }
	}
}

void replace_char(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '/') {
            str[i] = '_';
        }
    }
}

void print_ranking()
{
    char filename[100];
	replace_char(academic_year);
    snprintf(filename, sizeof(filename), "Ranking_%s.txt", academic_year);
	FILE *file = fopen(filename, "w");
	course *ptr;

	if (file == NULL) {
        printf("Errore nell'apertura del file %s\n", filename);
		exit(1);
    }
	fprintf(file,"Ranking:\n");
	for(int i = 0; i<HASHSIZE;i++){
		for(ptr = hash_table_courses[i]; ptr!=NULL; ptr = ptr->next){
				fprintf(file,"%s", ptr->name);
				ranking_course *ranking = ptr->ranking;
				int max_amount_of_place_available = ptr->amount_of_place_available;
				int candidate_insert = 0;
  	            while(ranking != NULL && candidate_insert < max_amount_of_place_available)
				{
					fprintf(file,"->(%s:%f)",ranking->candidate_name, ranking->score);

					ranking = ranking->next;
					candidate_insert = candidate_insert + 1;
				}
				fprintf(file,"\n");
		 }
	}
}


