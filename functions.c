#include "declaration.h"

int dim, cntMV, numCars; //+3 for the borders and the newline "\n"

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
