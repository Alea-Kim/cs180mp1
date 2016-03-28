#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "declaration.h"
#include "functions.c"

/*     ___________________
______/ Main Function     \_______________________________________________________________________________________________________*/

int main(){
	int i, j, listCtr = 0, newX = 0, newY=0;
	STATE start, newmove, current, temp;

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

    //GOAL X AND Y POSITION
	if(thecars[1].dir == 'h') {
		x = dim+2 - thecars[1].width;
		y = thecars[1].y;
	}
	else{
		y = dim+2 - thecars[1].width;
		x = thecars[1].x;
	}
	//ALLOCATE
	mallocate(move);
	int mika;
	//CREATE START NODE
	for(i = 1; i < numCars; i++) start.thecars[i] = thecars[i];
	start = allocate_map(start);
	init(start);
	//ADDING START NODE TO QUEUE
	listCtr=addmove(start);
	while(listCtr>0){
		 current = get_move_lowF();
		 draw(current.thecars, current.themap);
		 //FINAL: if(goal(current))	 break; // for no goal() == 1 always. Ayusing later


		for(j = 1; j < numCars; j++){
			if(current.thecars[j].dir='h'){
				//RIGHT
				newX = right(current, j);
				if(newX > current.thecars[j].x){
					newmove = set_xy(current, j, newX, current.thecars[j].y);
					printf("moved right:\n");
					draw(newmove.thecars, newmove.themap);
				}
				//LEFT
				newX = left(current, j);
				if(newX < current.thecars[j].x){
					newmove = set_xy(current, j, newX, current.thecars[j].y);
					printf("moved left:\n");	
					draw(newmove.thecars, newmove.themap);
				}	
			}

			else if(current.thecars[j].dir='v'){
				//UP
				newY = up(current, j);
				if(newY < current.thecars[j].y){
					newmove = set_xy(current, j, current.thecars[j].x, newY);
					printf("moved up:\n");	
					draw(newmove.thecars, newmove.themap);
				}
				//DOWN
				newY = down(current, j);
				if(newY > current.thecars[j].y){
					newmove = set_xy(current, j, current.thecars[j].x, newY);
					printf("moved down:\n");	
					draw(newmove.thecars, newmove.themap);
				}
			}	
			exit(0);
		}
	}
	return 0;
}
