#define HASHSIZE 101 //definizione della costante lunghezza della hashtable(numero primo)

//struttura delle fasce
typedef struct band{
	float startBand;
	float endBand;
	float cubicMeter;
}band;

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
person *hashTable[HASHSIZE];

//funzioni
unsigned int hash(char *fsc);
person *lookup(char *fsc);
int ins_band(int numberBand, float start, float end, float cost);
int ins_extra(float elettricEnergy, float sewer, float counter, float iva);
int ins_person(char* name, char* fsc, float totalWater);
float calculateCost(float totalWater, extra e, float valueCubicMeter);
void print_people();
