#define HASHSIZE 101 //size of hast table
//structure of course entity
typedef struct ranking_course{
	char* candidate_name;
	char* fiscal_code;
	char* birth_date;
	float score;
	struct ranking_course* next;
}ranking_course;

typedef struct course{
	char* name;
	int amount_of_place_available;
	int degree_vote;
	int test_vote;
	struct ranking_course *ranking;
	struct course* next;
}course;

typedef struct course_selected{
	char* name;
	struct course_selected* next;
}course_selected;


typedef struct candidate{
	char* name;
	char* fiscal_code;
	char* birth_date;
	int degree_vote;
	int test_vote;
	struct course_selected* courses;
	struct candidate* next;
}candidate;

course *hash_table_courses[HASHSIZE];
candidate *hash_table_candidates[HASHSIZE];

unsigned int hash(char *id);
candidate *lookup_candidate(char *fsc);
course *lookup_course(char *name_course);

int insert_candidate();
int insert_candidate_name(char *name);
int insert_candidate_fiscal_code(char *fiscal_code);
int insert_candidate_birthdate(char *birth_date);
int insert_candidate_degree_vote(int degree_vote);
int insert_candidate_test_vote(int test_vote);
int insert_candidate_course_selected(char *course);
int insert_course(char *name_course, int amount_of_place_available, int degree_vote, int test_vote);

void calculate_ranking();

void print_candidates();
void print_courses();
void print_ranking();