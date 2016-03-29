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

struct States{							//Structures for the Nodes/Cars
	CAR thecars[SIZE];
	char **themap;
	int g;	//cost
	int f;	//f(x)
	int h; 	//heuristics
	struct States* parent, *child;
};
typedef struct States STATE;
STATE *move, *visited;							//creates nodes for STATE

//FUNCTION PROTOTYPES
char **draw(STATE move);       //Prints the current set-up/condition of the cars
void draw_cars(CAR [], char **);       //Prints the current set-up/condition of the cars
void init_board(char **);
char readChar(FILE *);
void printMap(STATE node);
int addVisited(STATE *move, int i);


STATE allocate_map(STATE node);
void init(STATE node);
int h(STATE node);
void addCost(STATE node);
int g(STATE node);
int addmove(STATE newmove);
STATE get_move_lowF();
void mallocate(STATE *node);
STATE set_xy(STATE node, int i, int newX, int newY);
int right(STATE node, int i);
int left(STATE node, int i);
int up(STATE node, int i);
int down(STATE node, int i);












#endif
