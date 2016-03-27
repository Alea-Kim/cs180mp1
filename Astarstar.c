#include<stdio.h>
#include<string.h>
#include <stdlib.h>

#include "declaration.h"
#include "functions.c"

/*     ___________________
______/ Main Function     \_______________________________________________________________________________________________________*/

int main(){
	int i, j, listCtr = 0;
	STATE start, newmove, current;

	//file reading
	FILE *fp;
    fp = fopen("input.txt", "r");
    if(fp==NULL)	return;
    dim = readChar(fp) - '0';
    CAR thecars[(dim*dim)/2];
    for(i = 1; (!feof(fp)) ; i++){
        thecars[i].x = (readChar(fp) - '0') + 1;	//because the [0]th j is the left border | <---      |
        thecars[i].y = (readChar(fp) - '0') + 1;	// because the [0]th i is the top border -------------
        thecars[i].dir = readChar(fp);
        thecars[i].width = readChar(fp) - '0';
        if((numCars = fgetc(fp)) == EOF) numCars = i;
    }

	//ALLOCATE
	move =  (struct States *) malloc(sizeof(STATE));	//need to allocate dynamically
	if (move == NULL)   printf("malloc fail");

	//CREATE START NODE
	start = allocate_map(start);
	init(start);
	//ADDING START NODE TO QUEUE
	addmove(start);

	while(listCtr>0){
		 current = get_move_lowF();
		 //GENERATE(current);
	}

	//draw_initial_board
	draw(thecars, start.themap);
	return 0;
}
