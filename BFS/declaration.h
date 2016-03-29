#ifndef HEADER_FILE
#define HEADER_FILE
#define SIZE 50
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//STRUCTS
struct Node{							//Structures for the Cars
	int x;
	int y;
	char dir;
	int width;
};
typedef struct Node CAR;

struct States{							//Structures for the Nodes/MOVE
	CAR thecars[SIZE];
	int g;	//cost
	int f;	//f(x)
	int h; 	//heuristics
	struct States* parent;
};

typedef struct States STATE;
STATE *move;//, *visited;							//creates nodes for STATE

/*
struct NodeStack{
	STATE data;
	struct NodeStack *prev;

}*top, *cur;
*/

//FUNCTION PROTOTYPES
void draw(CAR thecars[]);       //Prints the current set-up/condition of the cars
char readChar(FILE *);
void printMap(STATE node);

STATE allocate_map(STATE node);
void init(STATE *node);
int h(STATE node);
void addCost(STATE node);
int g(STATE node);
int addmove(STATE newmove);
STATE get_move_lowF();
void mallocate(STATE *node);
STATE set_xy(STATE node, int i, int newX, int newY);
int right(CAR thecars[], int i);
int left(CAR thecars[], int i);
int up(CAR thecars[], int i);
int down(CAR thecars[], int i);
int removeNode(STATE node);
int goal(STATE node, STATE start);


#endif
