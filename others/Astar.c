#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#define SIZE 100

struct Node{							//Structures for the Nodes/Cars
	int x;
	int y;
	char dir;
	int width;
  //struct Node *prev;
};

typedef struct Node CAR;

struct States{							//Structures for the Nodes/Cars
	CAR thecars;
	int g;	//cost
	int f;	//f(x)
	int h; 	//heuristics
	struct States* parent, *child;
    //struct Node *prev;
};

typedef struct States STATE;
int dim, cntMV, numCars; //+3 for the borders and the newline "\n"
//STATE states[SIZE];

/*          _________________________
___________/ FUNCTION PROTOTYPES     \_____________________________________________________________________________*/
void draw(CAR [], char [dim+3][dim+3][5]);       //Prints the current set-up/condition of the cars
void draw_cars(CAR [], char [dim+3][dim+3][5]);       //Prints the current set-up/condition of the cars
void init_board(char themap[dim+3][dim+3][5]);
char readChar(FILE *);										//Filereading
//QUEUES
void PQ_insert(int *PQ, STATE x);
int PQ_extract(int *PQ, int PQsize);


void setCar(STATE start, CAR car){
	start.thecars = car;
};

/*     ___________________
______/ Main Function     \_______________________________________________________________________________________________________*/

int main(){
	int i, j, cntMV = 0;

	//file reading
	FILE *fp;
    fp = fopen("input.txt", "r");
    if(fp==NULL)	return;
    dim = readChar(fp) - '0';
    char themap[dim+3][dim+3][5];
    CAR thecars[(dim*dim)/2];
    for(i = 1; (!feof(fp)) ; i++){
        thecars[i].x = (readChar(fp) - '0') + 1;	//because the [0]th array is the border |
        thecars[i].y = (readChar(fp) - '0') + 1;
        thecars[i].dir = readChar(fp);
        thecars[i].width = readChar(fp) - '0';
        if((numCars = fgetc(fp)) == EOF) numCars = i;
    }

	//draw_initial_board
    draw(thecars, themap);

	STATE *move, start, *list;

	move =  (struct States *) malloc(sizeof(STATE));
	if (move == NULL)   printf("malloc fail");

	list =  (struct States *) malloc(sizeof(STATE));
	if (list == NULL)   printf("malloc fail");

	//setCar(start, thecars[1]);

	return 0;
}

void insert_move(STATE *move, STATE x){			//Insert an element to the PQ, and find its place.
	move = realloc(move, sizeof(char)*(cntMV));

	move[cntMV] = x;
	cntMV++;
}

/*int PQ_extract(int *PQ, int PQsize){				//Returns the element with the higest priority AND delete it.
	int temp, n = PQsize;
	temp = PQ[0];
    PQ[0] = PQ[PQsize-1];
    PQsize--;
	HEAPIFY(PQ, PQsize, 0);
	return temp;
}

/*     ___________________
______/ DRAWING FUNCTIONS \_______________________________________________________________________________________________________*/
void draw(CAR thecars[], char themap[dim+3][dim+3][5]){
	int i, j;

	init_board(themap);
	draw_cars(thecars, themap);

	//print the board
	for(i = 0; i<= dim+2; i++) for(j = 0; j <= dim+2; j++)	printf("%s", themap[j][i]);
}

void init_board(char themap[dim+3][dim+3][5]){
	int i, j;
	//place empty board
	for(i = 0; i<= dim+1; i++){
			for(j = 0; j <= dim+1; j++){
					if(i == 0 || i == dim+1){
						if (j == 0) strcpy(themap[j][i], "+");
						else if(j == dim+1) strcpy(themap[j][i], "+");
						else  strcpy(themap[j][i], "---");
					}
					else if(j == 0)		strcpy(themap[j][i], "|");
					else if(j == dim+1)	strcpy(themap[j][i], "|");
					else strcpy(themap[j][i]," . ");
			}
	}
	//place spaces and new line
	for(i = 0; i<dim+3; i++)	strcpy(themap[dim+2][i],"\n");
	for(i = 0; i<dim+3; i++){
				strcpy(themap[i][dim+2]," ");
				if(i==dim+2)		strcpy(themap[i][dim+2],"\n");
	}
}

void draw_cars(CAR thecars[], char themap[dim+3][dim+3][5]){
	int i, j;
	//exit
	if(thecars[1].dir == 'h') strcpy(themap[(dim+1)][thecars[1].y], " ");
	else if(thecars[1].dir == 'v') strcpy(themap[thecars[1].x][(dim+1)], " ");
	//placing the car accdg to their x & y coordinates and checking their orientations to know which way to expand legth of car accdg to its width
	for(i = 1; i <= numCars; i++){
		if(thecars[i].dir == 'v'){
			strcpy(themap[thecars[i].x][thecars[i].y], " ^ ");
			for(j = 1; j < thecars[i].width - 1; j++)	strcpy(themap[thecars[i].x][thecars[i].y+j], " | ");
			strcpy(themap[thecars[i].x][thecars[i].y+(thecars[i].width-1)], " v ");
		}
		else if(thecars[i].dir == 'h'){
			strcpy(themap[thecars[i].x][thecars[i].y], " < ");
			for(j = 1; j < thecars[i].width - 1; j++)	strcpy(themap[thecars[i].x+j][thecars[i].y], " = ");
			strcpy(themap[thecars[i].x+(thecars[i].width-1)][thecars[i].y], " > ");
		}
	}
}

/*     ___________________
______/ FILE READING      \_______________________________________________________________________________________________________*/

char readChar(FILE *fp){
    char a = fgetc(fp);
    if (isspace(a))	a = fgetc(fp);
    return a;
}
