#include<stdio.h>
#include<string.h>
#include <stdlib.h>

#include "declaration.h"
#include "functions.c"

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

	STATE *move, start, *list;							//creates nodes for STATE

	move =  (struct States *) malloc(sizeof(STATE));	//need to allocate dynamically
	if (move == NULL)   printf("malloc fail");

	list =  (struct States *) malloc(sizeof(STATE));
	if (list == NULL)   printf("malloc fail");

	start.themap = malloc(sizeof * start.themap * (dim+3));
	if (start.themap)
	{
	  for (i = 0; i < dim+5; i++)
	  {
		  start.themap[i] = malloc(sizeof *start.themap[i] * (dim+3));
	  }
	}

	//draw_initial_board
	draw(thecars, start.themap);

	//start.arr = themap;
	return 0;
}
