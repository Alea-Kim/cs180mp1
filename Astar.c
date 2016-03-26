#include<stdio.h>
#include<string.h>

struct Node{							//Structures for the Nodes/Cars
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
void draw_board(CAR [], char [dimension+3][dimension+3][5], int);       //Prints the current set-up/condition of the cars
void draw_cars(CAR [], char [dimension+3][dimension+3][5], int);       //Prints the current set-up/condition of the cars
void init_board(char themap[dimension+3][dimension+3][5]);
void readInput();               //Reads the scenario from input.txt
char readChar(FILE *);
/*     ___________________
______/ Main Function     \_______________________________________________________________________________________________________*/

int main(){

  readInput();
	return 0;
}

void draw_board(CAR thecars[], char themap[dimension+3][dimension+3][5], int numCars){
		int i, j;
		init_board(themap);
		draw_cars(thecars, themap, numCars);

		//print the board
		for(i = 0; i<= dimension+2; i++) for(j = 0; j <= dimension+2; j++)	printf("%s", themap[j][i]);
}

void init_board(char themap[dimension+3][dimension+3][5]){
	int i, j;
	//place empty board
	for(i = 0; i<= dimension+1; i++){
			for(j = 0; j <= dimension+1; j++){
					if(i == 0 || i == dimension+1){
						if (j == 0) strcpy(themap[j][i], "+");
						else if(j == dimension+1) strcpy(themap[j][i], "+");
						else  strcpy(themap[j][i], "---");
					}
					else if(j == 0)		strcpy(themap[j][i], "|");
					else if(j == dimension+1)	strcpy(themap[j][i], "|");
					else strcpy(themap[j][i]," . ");
			}
	}
	//place spaces and new line
	for(i = 0; i<dimension+3; i++)	strcpy(themap[dimension+2][i],"\n");
	for(i = 0; i<dimension+3; i++){
				strcpy(themap[i][dimension+2]," ");
				if(i==dimension+2)		strcpy(themap[i][dimension+2],"\n");
	}
}

void draw_cars(CAR thecars[], char themap[dimension+3][dimension+3][5], int numCars){
	int i, j;
	//exit
	strcpy(themap[(dimension+1)][thecars[1].y], " ");
	//placing the car accdg to their x & y coordinates and checking their orientations to know which way to expand legth of car accdg to its width
	for(i = 1; i <= numCars; i++){
		if(thecars[i].dir == 'v'){
			strcpy(themap[thecars[i].x][thecars[i].y], " ^ ");
			for(j = 1; j < thecars[i].width - 1; j++)	strcpy(themap[thecars[i].x][thecars[i].y+j], " | ");
			strcpy(themap[thecars[i].x][thecars[i].y+(thecars[i].width-1)], " v ");
		}
		else if(thecars[i].dir == 'h'){
			strcpy(themap[thecars[i].x][thecars[i].y], " < ");
			for(j = 1; j < thecars[i].width - 1; j++)	strcpy(themap[thecars[i].x+j][thecars[i].y], " = ");
			strcpy(themap[thecars[i].x+(thecars[i].width-1)][thecars[i].y], " > ");
		}
	}
}

void readInput(){
  FILE *fp;
  fp = fopen("input.txt", "r");
  if(fp==NULL)	return;
  dimension = readChar(fp) - '0';
  char themap[dimension+3][dimension+3][5];
  CAR thecars[(dimension*dimension)/2];
  int i, numCars, j;
  for(i = 1; (!feof(fp)) ; i++){
        thecars[i].x = (readChar(fp) - '0') + 1;
        thecars[i].y = (readChar(fp) - '0') + 1;
        thecars[i].dir = readChar(fp);
        thecars[i].width = readChar(fp) - '0';
        if((numCars = fgetc(fp)) == EOF) numCars = i;
  }
  draw_board(thecars, themap, numCars);
}

char readChar(FILE *fp){
  char a = fgetc(fp);
  if (isspace(a)){
      a = fgetc(fp);
  }
  return a;
}
