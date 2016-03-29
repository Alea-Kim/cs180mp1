#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "declaration.h"
#include "functions.c"

/*     ___________________
______/ Main Function     \_______________________________________________________________________________________________________*/

int main(){
	int i, j, m, n, k, ay,  listCtr = 0, newX = 0, newY=0, inList;
	STATE start, newmove, current, temp;
	bottom = 0;
	numExp = 0;
	//file reading
	FILE *fp;
    fp = fopen("input.txt", "r");
    if(fp==NULL)	return;
    fscanf(fp, "%d,", &dim);
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
		x = dim+1 - thecars[1].width;
		y = thecars[1].y;
	}
	else{
		y = dim+1 - thecars[1].width;
		x = thecars[1].x;
	}
	//ALLOCATE
	mallocate(move);
	int mika;
	//CREATE START NODE
	init(&start);
	for(i = 1; i < numCars; i++) start.thecars[i] = thecars[i];

	//ADDING START NODE TO QUEUE
	listCtr=addmove(start);
	while(listCtr>0){
		 current = get_move_lowF();
		 if(goal(current, start))	 exit(0); // for no goal() == 1 always. Ayusing later
		 for(j = 1; j < numCars; j++){
			if(current.thecars[j].dir=='h'){
				 printf("START MAP:\n");
				 draw(current.thecars);

				//RIGHT
				newX = right(current.thecars, j);
				if(newX > current.thecars[j].x){
					newmove = set_xy(current, j, newX, current.thecars[j].y);

					printf("MOVED RIGHT: car[%d]:\n", j);
					draw(newmove.thecars);
					inList = 0;
					numExp+=1;
					//Check if newmove in move[i]/open list
					for(i = 0; i < listCtr; i++){
						//printf(">>STATE %d\n", i);
						for(m = 1; m< numCars; m++){
							//printf("Newmove's xy: %d%d ?= move[%d]'s xy: %d%d\n", newmove.thecars[m].x, newmove.thecars[m].y, i, move[i].thecars[m].x, move[i].thecars[m].y);
							if (newmove.thecars[m].x != move[i].thecars[m].x || newmove.thecars[m].y != move[i].thecars[m].y) {
									inList = 0;
									break;
							}
							else inList = 1;
						}
						if (inList == 1) break;
					}

					//If Not In list
					if(inList == 0){
						printf("NOT IN LIST PA (Moves++: %d)\n", listCtr);
						newmove.parent = &current;
						//current.h = h(current);
						newmove.h = 0;
						newmove.g = current.g + 1;
						newmove.f = newmove.g + newmove.h;
						listCtr = addmove(newmove);
						if(goal(newmove, start))	 exit(0); // for no goal() == 1 always. Ayusing later
					}
					else printf("Repeated States Not Allowed (Successor Ignored) \n");
				}

				//LEFT
				newX = left(current.thecars, j);
				if(newX < current.thecars[j].x){
					newmove = set_xy(current, j, newX, current.thecars[j].y);
					printf("MOVED LEFT(car[%d]):\n", j);
					draw(newmove.thecars);
					numExp+=1;
					inList = 0;

					//Check if newmove in move[i]/open list
					for(i = 0; i < listCtr; i++){
						//printf(">>STATE %d\n", i);
						for(m = 1; m< numCars; m++){
						//	printf("Newmove's xy: %d%d ?= move[%d]'s xy: %d%d\n", newmove.thecars[m].x, newmove.thecars[m].y, i, move[i].thecars[m].x, move[i].thecars[m].y);
							if (newmove.thecars[m].x != move[i].thecars[m].x || newmove.thecars[m].y != move[i].thecars[m].y) {
									inList = 0;
									break;
							}
							else inList = 1;
						}
						if (inList == 1) break;
					}

					//If Not In list
					if(inList == 0){
						printf("NOT IN LIST PA (Moves++: %d)\n", listCtr);
						newmove.parent = &current;
						//current.h = h(current);
						newmove.h = 0;
						newmove.g = current.g + 1;
						newmove.f = newmove.g + newmove.h;
						listCtr = addmove(newmove);
						if(goal(newmove, start))	exit(0); // for no goal() == 1 always. Ayusing later
					}
					else printf("Repeated States Not Allowed (Successor Ignored)\n");

				}
			}
			else if(current.thecars[j].dir=='v'){
				 printf("START MAP:\n");
				 draw(current.thecars);

				//UP
				newY = up(current.thecars, j);
				if(newY < current.thecars[j].y){
					newmove = set_xy(current, j, current.thecars[j].x, newY);

					printf("MOVED UP: car[%d]:\n", j);
					draw(newmove.thecars);
					inList = 0;
					numExp+=1;
					//Check if newmove in move[i]/open list
					for(i = 0; i < listCtr; i++){
					//	printf(">>STATE %d\n", i);
						for(m = 1; m< numCars; m++){
						//	printf("Newmove's xy: %d%d ?= move[%d]'s xy: %d%d\n", newmove.thecars[m].x, newmove.thecars[m].y, i, move[i].thecars[m].x, move[i].thecars[m].y);
							if (newmove.thecars[m].x != move[i].thecars[m].x || newmove.thecars[m].y != move[i].thecars[m].y) {
									inList = 0;
									break;
							}
							else inList = 1;
						}
						if (inList == 1) break;
					}

					//If Not In list
					if(inList == 0){
						printf("NOT IN LIST PA (Moves++: %d)\n", listCtr);
						newmove.parent = &current;
						//current.h = h(current);
						newmove.h = 0;
						newmove.g = current.g + 1;
						newmove.f = newmove.g + newmove.h;
						listCtr = addmove(newmove);
						if(goal(newmove, start))	exit(0); // for no goal() == 1 always. Ayusing later
					}
					else printf("Repeated States Not Allowed (Successor Ignored)\n");
				}

				//DOWN
				newY = down(current.thecars, j);
				if(newY > current.thecars[j].y){

					printf("MOVED DOWN: car[%d]:\n", j);
					newmove = set_xy(current, j, current.thecars[j].x, newY);
					draw(newmove.thecars);
					inList = 0;
					numExp+=1;
					//Check if newmove in move[i]/open list
					for(i = 0; i < listCtr; i++){
					//	printf(">>STATE %d\n", i);
						for(m = 1; m< numCars; m++){
							///printf("Newmove's xy: %d%d ?= move[%d]'s xy: %d%d\n", newmove.thecars[m].x, newmove.thecars[m].y, i, move[i].thecars[m].x, move[i].thecars[m].y);
							if (newmove.thecars[m].x != move[i].thecars[m].x || newmove.thecars[m].y != move[i].thecars[m].y) {
									inList = 0;
									break;
							}
							else inList = 1;
						}
						if (inList == 1) break;
					}

					//If Not In list
					if(inList == 0){
						printf("NOT IN LIST PA (Moves++: %d)\n", listCtr);
						newmove.parent = &current;
						//current.h = h(current);
						newmove.h = 0;
						newmove.g = current.g + 1;
						newmove.f = newmove.g + newmove.h;
						listCtr = addmove(newmove);
						if(goal(newmove, start))	exit(0); // for no goal() == 1 always. Ayusing later
					}
					else printf("Repeated States Not Allowed (Successor Ignored)\n");
				}
			}
//			scanf("%d", &mika);
		}//end of exhausting all possible movements of CAR[j]
		bottom = removeNode(current);
	}//end of while / Astar
	return 0;
}
