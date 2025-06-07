#define HASHSIZE 101 //size of hast table
//structure of course entity
typedef struct course{
	char* name;
	int amount_of_place_available;
	int degree_vote;
	int test_vote;
	struct course* next;
}course;


course *hash_table_courses[HASHSIZE];

unsigned int hash(char *fsc);
course *lookup_course(char *fsc);
int insert_course(char *name_course, int amount_of_place_available, int degree_vote, int test_vote);
void print_courses();

