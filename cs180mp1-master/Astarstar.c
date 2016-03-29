#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "declaration.h"
#include "functions.c"

/*     ___________________
______/ Main Function     \_______________________________________________________________________________________________________*/

int main(){
	int i, j, m, n, k, ay,  listCtr = 0, newX = 0, newY=0, inList;
	STATE start, newmove, current, *ptr, temp;

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
		 //FINAL: if(goal(current))	 break; // for no goal() == 1 always. Ayusing later

		for(j = 1; j < numCars; j++){
			if(current.thecars[j].dir=='h'){
				current.themap = draw(current);
		   		 printf("START MAP:\n");
		   		 printMap(current);
				//RIGHT
				newX = right(current, j);
				if(newX > current.thecars[j].x){
					newmove = set_xy(current, j, newX, current.thecars[j].y);

					newmove.themap = draw(newmove);
					printf("MOVED RIGHT:\n");
					printMap(newmove);

					newmove.g = current.g+1;
					newmove.h = 0;
					inList = 0;

					//Check if newmove in move[i]/open list
					for(i = 0; i < listCtr; i++){
						for(m = 0; m<= dim+2; m++){
							//printf("C: [%d][%d] %c vs. %c \n", n, m, move[i].themap[n][m], newmove.themap[n][m]);
							//printf("C: [%d] %d vs. %d \n", m, move[i].thecars[m].x, newmove.thecars[m].x);
							if (newmove.thecars[m].x != move[i].thecars[m].x || newmove.thecars[m].y != move[i].thecars[m].y) {
									inList = 0;
									break;
							}
							else inList = 1;
						}
					}

					//If Not In list
					if(inList == 0){
						printf("NOT IN LIST PA\n");
						ptr = &current;
						newmove.parent = ptr;
						inList = 0;
						listCtr = addmove(newmove);
						printf("Moves-> %d\n", listCtr);
					}
					else printf("NASA LIST NA\n");
				}
				//LEFT
				newX = left(current, j);
				if(newX < current.thecars[j].x){
					newmove = set_xy(current, j, newX, current.thecars[j].y);

					newmove.themap = draw(newmove);
					printf("MOVED LEFT(car[%d]):\n", j);
					printMap(newmove);

					newmove.g = current.g+1;
					newmove.h = 0;
					inList = 0;

					//Check if newmove in move[i]/open list
					for(i = 0; i < listCtr; i++){
						for(m = 0; m<= dim+2; m++){
							if (newmove.thecars[m].x != move[i].thecars[m].x || newmove.thecars[m].y != move[i].thecars[m].y) {
									inList = 0;
									break;
							}
							else inList = 1;
						}
					}

					//If Not In list
					if(inList == 0){
						printf("NOT IN LIST PA\n");

						//CHECK HERE
						ptr = &current;
						newmove.parent = ptr;
						inList = 0;
						listCtr = addmove(newmove);
						printf("Moves-> %d\n", listCtr);
					}
					else printf("NASA LIST NA\n");

				}
			}
			else if(current.thecars[j].dir=='v'){
				//printf("car[%d] is vertical \n\n", j);
				 current.themap = draw(current);
		   		 printf("START MAP:\n");
		   		 printMap(current);

				//UP
				newY = up(current, j);
				if(newY < current.thecars[j].y){
					newmove = set_xy(current, j, current.thecars[j].x, newY);

					newmove.themap = draw(newmove);
					printf("MOVED UP:\n");
					printMap(newmove);

					newmove.g = current.g+1;
					newmove.h = 0;
					inList = 0;

					//Check if newmove in move[i]/open list
					for(i = 0; i < listCtr; i++){
						for(m = 0; m<= dim+2; m++){
							if (newmove.thecars[m].x != move[i].thecars[m].x || newmove.thecars[m].y != move[i].thecars[m].y) {
									inList = 0;
									break;
							}
							else inList = 1;
						}
					}

					//If Not In list
					if(inList == 0){
						printf("NOT IN LIST PA\n");

						//CHECK HERE
						ptr = &current;
						newmove.parent = ptr;
						inList = 0;
						listCtr = addmove(newmove);
						printf("Moves-> %d\n", listCtr);
					}
					else printf("NASA LIST NA\n");
				}

				//DOWN
				newY = down(current, j);
				if(newY > current.thecars[j].y){

					newmove = set_xy(current, j, current.thecars[j].x, newY);
					printf("AFTER setXY\n");
					for(i = 0; i<= dim+2; i++) for(k = 0; k <= dim+2; k++)	printf(" %c",  newmove.themap[k][i]);

					newmove.themap = draw(newmove);
					printf("MOVED DOWN:\n");
					printMap(newmove);
					//scanf("%d", &mika);

					newmove.g = current.g+1;
					newmove.h = 0;
					inList = 0;

					//Check if newmove in move[i]/open list
					for(i = 0; i < listCtr; i++){
						for(m = 0; m<= dim+2; m++){
							if (newmove.thecars[m].x != move[i].thecars[m].x || newmove.thecars[m].y != move[i].thecars[m].y) {
									inList = 0;
									break;
							}
							else inList = 1;
						}
					}

					//If Not In list
					if(inList == 0){
						printf("NOT IN LIST PA\n");

						//CHECK HERE
						ptr = &current;
						newmove.parent = ptr;
						inList = 0;
						listCtr = addmove(newmove);
						printf("Moves-> %d\n", listCtr);
					}
					else {
						//Compare cost/BFS to
						for(i = 0; i < listCtr; i++){
							for(m = 0; m<= dim+2; m++){
								if (newmove.thecars[m].x != move[i].thecars[m].x || newmove.thecars[m].y != move[i].thecars[m].y) {
										break;
								}
								else ay = i;
							}
						}

						if(move[ay].f < newmove.f )	continue;	//ignore successor
						//remove occcurences
						ptr = &current;
						newmove.parent = ptr;
						inList = 0;
						listCtr = addmove(newmove);
						printf("Moves-> %d\n", listCtr);

					} //printf("NASA LIST NA\n");
				}
			}
			scanf("%d", &mika);
		}
		//addVisited(move, i);

	}
	return 0;
}
