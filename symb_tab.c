#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symb_tab.h"

candidate *candidate_to_insert;

float calculate_points(int degree_vote_candidate, int test_vote_candidate,  int degree_vote_course, int test_vote_course)
{
	return (((degree_vote_candidate*degree_vote_course)/100)+ ((degree_vote_course*test_vote_course)/100))
}



unsigned int hash(char *id) {
	int h=0;
	for(;*id!='\0';id++){
		h=(127*h+*id)%HASHSIZE;
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

//Insert new course
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

int insert_candidate_degree_vote(int degree_vote)
{
	if (candidate_to_insert ==NULL)
		return 0;

	candidate_to_insert->degree_vote = degree_vote;

	return 1;
}

int insert_candidate_test_vote(int test_vote)
{
	if (candidate_to_insert ==NULL)
		return 0;

	candidate_to_insert->test_vote = test_vote;
	printf("%s\n",candidate_to_insert->name);
	printf("%s\n",candidate_to_insert->fiscal_code);
	printf("%s\n",candidate_to_insert->birth_date);
	printf("%d\n",candidate_to_insert->degree_vote);
	printf("%d\n",candidate_to_insert->test_vote);
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

//Insert new course
int insert_course(char *name_course, int amount_of_place_available, int degree_vote, int test_vote){	

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
	new_course->degree_vote = degree_vote;
	new_course->test_vote = test_vote;
	new_course->next = hash_table_courses[hash_index];
    
    hash_table_courses[hash_index] = new_course;

	return 1;
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


