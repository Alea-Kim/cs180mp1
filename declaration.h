#ifndef HEADER_FILE
#define HEADER_FILE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//STRUCTS
struct Node{							//Structures for the Cars
	int x;
	int y;
	char dir;
	int width;
  //struct Node *prev;
};
typedef struct Node CAR;

struct States{							//Structures for the Nodes/Cars
	char **themap;
	int g;	//cost
	int f;	//f(x)
	int h; 	//heuristics
	struct States* parent, *child;
};
typedef struct States STATE;


//FUNCTION PROTOTYPES
void draw(CAR [], char **);       //Prints the current set-up/condition of the cars
void draw_cars(CAR [], char **);       //Prints the current set-up/condition of the cars
void init_board(char **);
char readChar(FILE *);

STATE allocate_map(STATE node);
void init(STATE node);
void set_h(STATE node);
int get_h(STATE node);
void addCost(STATE node);
int get_g(STATE node);
#endif
