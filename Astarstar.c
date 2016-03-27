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
    CAR thecars[SIZE];
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
	for(i = 1; i < numCars; i++) start.car[i] = thecars[i];
	start = allocate_map(start);
	init(start);
	//ADDING START NODE TO QUEUE
	listCtr=addmove(start);
	//printf("%d", listCtr);
	int mika;
	while(listCtr>0){
		 current = get_move_lowF();
		 //draw(thecars, current.themap);
		 if(goal(current)){
			 printf("THIS IS IT");
			 break; // for no goal() == 1 always. Ayusing later
		 }
		 //GENERATE(current);
	}
	return 0;
}
