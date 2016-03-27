#include "declaration.h"

int dim, listCtr, numCars; //+3 for the borders and the newline "\n"

//AALL ABOUT THE NODE
STATE allocate_map(STATE node){
	int i;
	node.themap = malloc(sizeof * node.themap * (dim+3));
	if (node.themap) for (i = 0; i < dim+5; i++) node.themap[i] = malloc(sizeof *node.themap[i] * (dim+3));
	return node;
}

void init(STATE node){
	node.g = 0;
	node.h = 0;
}

int get_h(STATE node){
	return node.h;
}

void addCost(STATE node){
	node.g += 1;
}

int get_g(STATE node){
	return node.g;
}

//ALL ABOUT THE LIST/MOVE
/*void addmove(STATE move){
	move = (struct States *) realloc(sizeof(STATE)*listCtr, move);	//need to allocate dynamically
	move[Ctr];
	listCtr++;


}
*/
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
