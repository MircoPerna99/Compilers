#define HASHSIZE 101 //size of hast table
//structure of course entity
typedef struct course{
	char* name;
	int amount_of_place_available;
	int degree_vote;
	int test_vote;
	struct course* next;
}course;

//struttura per i costi aggiuntivi
typedef struct extra{
	float elettricEnergy;
	float sewer;
	float counter;
	float iva;
}extra;

//struttura per le persone
typedef struct person{
	char* name;
	char* fsc;
	float amount;
	struct person*  personNext;
}person;



//hashtable per per le persone
person *hash_table_person[HASHSIZE];
course *hash_table_courses[HASHSIZE];

//funzioni
unsigned int hash(char *fsc);
course *lookup_course(char *fsc);
int insert_course(char* name_course, int amount_of_place_available, int degree_vote, int test_vote);
void print_courses();
// int ins_extra(float elettricEnergy, float sewer, float counter, float iva);
// int ins_person(char* name, char* fsc, float totalWater);
// float calculateCost(float totalWater, extra e, float valueCubicMeter);
// void print_people();
