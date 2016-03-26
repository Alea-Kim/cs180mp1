#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node{							//Structures for the Nodes in the TREE.
	int x;
	int y;
	char dir;
	int width;
  //struct Node *prev;
};

typedef struct Node CAR;

int dimension;
/*          _________________________
___________/ FUNCTION PROTOTYPES     \_____________________________________________________________________________*/

//PRIORITY QUEUES
void draw(CAR [],char [dimension][dimension][2], int, int);       //Prints the current set-up/condition of the cars
void readInput();               //Reads the scenario from input.txt
char readChar(FILE *);



/*     ___________________
______/ Main Function     \_______________________________________________________________________________________________________*/

int main(){

  readInput();
	return 0;
}

/*          ______________________________
___________/ P R I O R I T Y    Q U E U E \_________________________________________________________________*/
/*
void PQ_insert(int *PQ, int PQsize, int x){			//Insert an element to the PQ, and find its place.
	int i = PQsize, j = i/2;
	while(i>1 && PQ[j]<x){
		PQ[i] = PQ[j];
		i = j;
		j = i/2;
	}
	PQ[i] = x;
}

int PQ_extract(int *PQ, int PQsize){				//Returns the element with the higest priority AND delete it.
	int temp, n = PQsize;
	temp = PQ[0];
    PQ[0] = PQ[PQsize-1];
    PQsize--;
	HEAPIFY(PQ, PQsize, 0);
	return temp;
}

int PQ_return(int *PQ, int PQsize){					//Returns the element with the higest priority NO NEED to delete it.
	return PQ[PQsize-1];
}
void PQ_delete(int *PQ, int PQsize, int x){			//Like extract, the last and the PQ[x] exchanged places
	int last = PQ[PQsize-1];						//Then we'll disregard the righmost bottom element before heapify()
    PQ[PQsize-1] = PQ[x];							//Note that after this fxn gets called, we must PQsize--
    PQ[x] = last;
    PQsize--;
	HEAPIFY(PQ, PQsize, x);
}

void PQ_change(int *PQ, int PQsize, int decinc){
	int i = 0, j = PQsize - 1, temp;				//	PQ - Already sorted array
	if(decinc == 0){
		printf("(Ascending): ");					//	Decinc : 1 if Descending, as is. (default is MAX Heap)
	    while (i < j) {								//  	   : 0 if Ascending order
	       temp = PQ[i];							//				- Reversed the order of the PQ's element
	       PQ[i] = PQ[j];							//				  because the one with the highest priority
	       PQ[j] = temp;							//				  is now the smallest number
	       i++;
	       j--;
	    }
	}
	else printf("(Descending): ");
}
*/

void draw(CAR thecars[], char themap[dimension+3][dimension+3][2], int dimension, int numCars){
    int i, j;

		//first way yo initialize
		//actual empty board
    for(i = 0; i<= dimension+1; i++){
        for(j = 0; j <= dimension+1; j++){
      			if(i == 0 || i == dimension+1){
							if (j == 0) strcpy(themap[j][i], "+");
							else if(j == dimension+1) strcpy(themap[j][i], "+");
							else  strcpy(themap[j][i], "-");
            }
            else if(j == 0)		strcpy(themap[j][i], "|");
						else if(j == dimension+1)	strcpy(themap[j][i], "|");
						else strcpy(themap[j][i],".");
				}
    }

	/*//another way	for(i = 0; i<= dimension+1; i++){
        for(j = 0; j <= dimension+1; j++){
						strcpy(themap[i][j], ".");
				}
		}
		for(i = 0; i<dimension+2; i++){
			strcpy(themap[i][0],"-");
			if(i == 0 || i == dimension+1) strcpy(themap[0][0],"+");
		}
		for(i = 0; i<dimension+2; i++){
			strcpy(themap[i][dimension+1],"-");
			if(i == 0 || i == dimension+1) strcpy(themap[0][0],"+");
		}
		for(i = 1; i<dimension+1; i++){
			strcpy(themap[0][i],"|");
		}
		for(i = 1; i<dimension+1; i++){
			strcpy(themap[dimension+1][i],"|");
		}*/

//for spaces and new line
		for(i = 0; i<dimension+3; i++){
			strcpy(themap[dimension+2][i],"\n");
		}
		for(i = 0; i<dimension+3; i++){
					strcpy(themap[i][dimension+2]," ");
					if(i==dimension+2)		strcpy(themap[i][dimension+2],"\n");
		}

		//printing
		for(i = 0; i<= dimension+2; i++){
				for(j = 0; j <= dimension+2; j++){
						printf("%s", themap[j][i]);
						//printf("%d%d %s  ", j,i, themap[j][i]);
						//scanf("%d", &k);

				}
		}
/*    for(k = 0; k<numCars; k++){
        if(thecars[k].x == j+1 && thecars[k].y == i+1){
          for(m = 0; m<thecars[k].width ; m++)
              if(thecars[k].dir == 'v'){

              }
              else if(thecars[k].dir == 'h'){

              }
        }
    }*/

}

void readInput(){
    //File Reading
  FILE *fp;
  fp = fopen("input.txt", "r");
  if(fp==NULL)	return;

  dimension = readChar(fp) - '0';
  char themap[dimension+3][dimension+3][2];

		CAR thecars[(dimension*dimension)/2];
  int i, numCars, j;
  for(i = 1; (!feof(fp)) ; i++){
        thecars[i].x = readChar(fp) - '0';
        thecars[i].y = readChar(fp) - '0';
        thecars[i].dir = readChar(fp);
        thecars[i].width = readChar(fp) - '0';
        if((numCars = fgetc(fp)) == EOF) numCars = i;
  }
	//for(i = 0; i < 5; i++)	for(j = 0; j < 5; j++)	try[j][i] = i;
	//for(i = 0; i < 5; i++)	for(j = 0; j < 5; j++)	printf("%d: %d %d\n", try[j][i], j, i);

  draw(thecars, themap, dimension, numCars);
  //for(i = 1; i <= numCars; i++)  printf(" = %d. %d %d %c %d \n", i, thecars[i].x, thecars[i].y, thecars[i].dir, thecars[i].width);

}

char readChar(FILE *fp){
  char a = fgetc(fp);
  if (isspace(a)){
      a = fgetc(fp);
  }
  return a;
}
