#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#define SIZE 100


int dim, cntMV, numCars; //+3 for the borders and the newline "\n"

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
    //struct Node *prev;
};

typedef struct States STATE;


/*          _________________________
___________/ FUNCTION PROTOTYPES     \_____________________________________________________________________________*/
void draw(CAR [], char **);       //Prints the current set-up/condition of the cars
void draw_cars(CAR [], char **);       //Prints the current set-up/condition of the cars
void init_board(char **);
char readChar(FILE *);										//Filereading

/*     ___________________
______/ Main Function     \_______________________________________________________________________________________________________*/

int main(){
	int i, j, cntMV = 0;

	//file reading
	FILE *fp;
    fp = fopen("input.txt", "r");
    if(fp==NULL)	return;
    dim = readChar(fp) - '0';
    //char themap[dim+3][dim+3][5];
    CAR thecars[(dim*dim)/2];
    for(i = 1; (!feof(fp)) ; i++){
        thecars[i].x = (readChar(fp) - '0') + 1;	//because the [0]th array is the border |
        thecars[i].y = (readChar(fp) - '0') + 1;
        thecars[i].dir = readChar(fp);
        thecars[i].width = readChar(fp) - '0';
        if((numCars = fgetc(fp)) == EOF) numCars = i;
    }

	//draw_initial_board
    //draw(thecars, themap);

	STATE *move, start, *list;

	move =  (struct States *) malloc(sizeof(STATE));
	if (move == NULL)   printf("malloc fail");

	list =  (struct States *) malloc(sizeof(STATE));
	if (list == NULL)   printf("malloc fail");
	//draw_initial_board
	//start->themap =  (char *) malloc(sizeof(char));
	start.themap = malloc(sizeof * start.themap * (dim+3));
	if (start.themap)
	{
	  for (i = 0; i < dim+5; i++)
	  {
		  start.themap[i] = malloc(sizeof *start.themap[i] * (dim+3));
	  }
	}


    draw(thecars, start.themap);

	//start.arr = themap;
	return 0;
}
/*     ___________________
______/ DRAWING FUNCTIONS \_______________________________________________________________________________________________________*/
void draw(CAR thecars[], char ** themap){
	int i, j;

	init_board(themap);
	draw_cars(thecars, themap);

	//print the board
	for(i = 0; i<= dim+2; i++) for(j = 0; j <= dim+2; j++)	printf(" %c",  themap[j][i]);
}
void init_board(char **themap){
	int i, j, mika;
	//place empty board
	for(i = 0; i<= dim+1; i++){
			for(j = 0; j <= dim+1; j++){
					if(i == 0 || i == dim+1){
						if (j == 0 || j == dim+1)   themap[j][i] = '+';
						else    themap[j][i] = '-';
					}
					else if(j == 0 || j == dim+1)	  themap[j][i] = '|';
					else  themap[j][i] ='.';
//					scanf("%d", &mika);
			}
	}

	//place spaces and new line
	for(i = 0; i<dim+3; i++)	  themap[dim+2][i] = '\n';
	for(i = 0; i<dim+3; i++){
				 themap[i][dim+2] = ' ';
				if(i==dim+2)  themap[i][dim+2] = '\n';
	}
}

void draw_cars(CAR thecars[], char ** themap){
	int i, j;
	//exit
	if(thecars[1].dir == 'h')    themap[(dim+1)][thecars[1].y] = ' ';
	else if(thecars[1].dir == 'v')    themap[thecars[1].x][(dim+1)] = ' ';
	//placing the car accdg to their x & y coordinates and checking their orientations to know which way to expand legth of car accdg to its width
	for(i = 1; i <= numCars; i++){
		if(thecars[i].dir == 'v'){
			  themap[thecars[i].x][thecars[i].y] = '^';
			for(j = 1; j < thecars[i].width - 1; j++)	   themap[thecars[i].x][thecars[i].y+j] = '|';
			  themap[thecars[i].x][thecars[i].y+(thecars[i].width-1)] = 'v';
		}
		else if(thecars[i].dir == 'h'){
			  themap[thecars[i].x][thecars[i].y] = '<';
			for(j = 1; j < thecars[i].width - 1; j++)	   themap[thecars[i].x+j][thecars[i].y] = '=';
			  themap[thecars[i].x+(thecars[i].width-1)][thecars[i].y] = '>';
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
