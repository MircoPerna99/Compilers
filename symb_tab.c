#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symb_tab.h"

//funzione hash
unsigned int hash(char *fsc) {
	int h=0;
	for(;*fsc!='\0';fsc++){
		h=(127*h+*fsc)%HASHSIZE;
		}
	return h;
}


course *lookup_course(char *name) {
	course *c;
	for (c = hash_table_courses[hash(name)]; c != NULL; c = c->next){
		if (strcmp(name,c->name) == 0){
			return c;
			}
		}
	
	return NULL;
}

//Insert new course
int insert_course(char *name_course, int amount_of_place_available, int degree_vote, int test_vote){	

	if(lookup_course(name_course)!=NULL){
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

void print_courses() {
	course *ptr;
	printf("Courses:\n");
	
	
	for(int i = 0; i<HASHSIZE;i++){
		for(ptr = hash_table_courses[i]; ptr!=NULL; ptr = ptr->next){
  	                printf("%s\n",ptr->name);
		 }
	}
}
