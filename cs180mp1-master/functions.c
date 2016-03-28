#include "declaration.h"

int dim, listCtr, numCars, x, y; //+3 for the borders and the newline "\n"

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
	node.f = 0;
}


void addCost(STATE node){
	node.g += 1;
}

int h(STATE node){
	return node.h;
}

int g(STATE node){
	return node.g;
}

int f(STATE node){
	return g(node)+h(node);
}

void mallocate(STATE *node){
	node = (struct States *) malloc(sizeof(STATE));	//need to allocate dynamically
	if (node == NULL)   printf("malloc fail\n");
}



STATE set_xy(STATE node, int i, int newX, int newY){
	STATE temp = node;
	//printf("%d %d\n", newX, newY);
	temp.thecars[i].x = newX;
	temp.thecars[i].y = newY;
	return temp;
}

//ALL ABOUT THE LIST/MOVE
int addmove(STATE newmove){
	if(listCtr == 0) move = (struct States *) realloc(move, sizeof(STATE));	//need to allocate dynamically
	else move = (struct States *) realloc(move, sizeof(STATE)*listCtr);	//need to allocate dynamically
	move[listCtr] = newmove;
	listCtr = listCtr + 1;
	//delete(newmove);
	return listCtr;
}

STATE get_move_lowF(){
	int i, lowCost = f(move[0]);
	STATE lowNode = move[0];
	for(i = 1; i < listCtr-1; i++){
		if (f(move[i]) < lowCost){
			lowCost = f(move[i]);
			lowNode = move[i];
		}
	}
	return lowNode;
}

int goal(STATE node){
	if(node.thecars[1].x == x && node.thecars[1].y == y){
		printf("ACHIEVED GOAL\n");
		return 1;
	}
	printf(">>UNDER CONSTRUCTION(function.c->int goal())<< Always return 1 for now para no infinite loop\n");
	return 1;
}


int right(STATE node, int i){
	int j, x, wid, allowed;
	wid = node.thecars[i].width;
	allowed = dim - wid;
	j = 1;
	x = node.thecars[i].x;
	if(node.thecars[i].x+wid-1 == dim)	return 0;	
	while(j <= dim-node.thecars[i].x-wid+1){
		if((node.themap[node.thecars[i].x+j][node.thecars[i].y] == '>' && node.themap[node.thecars[i].x+j+1][node.thecars[i].y] =='.') || 
			(node.themap[node.thecars[i].x+j+1][node.thecars[i].y] =='.') ||
		(node.themap[node.thecars[i].x+j][node.thecars[i].y] == '=' && (node.themap[node.thecars[i].x+wid-1][node.thecars[i].y] == '>'))){
			x += 1;
		}
		else return x;
		j+=1;
	}
	return x;
}

int left(STATE node, int i){
	int j, x, wid, allowed;
	wid = node.thecars[i].width;
	//allowed = dim - wid;
	j = 1;
	x = node.thecars[i].x;
		
	if(node.thecars[i].x+wid-1 == 1)	return 0;	//dim or dim + 1?? gaaah try both if error
	while(j < node.thecars[i].x){//dim-node.thecars[i].x-wid+1){
		if(node.themap[node.thecars[i].x-j][node.thecars[i].y] == '.'){
			x -= 1;	
		} 	
		else return x;
		j+=1;
	}
	return x;
}

int down(STATE node, int i){
	int j, y, wid, allowed;
	wid = node.thecars[i].width;
	j = 1;
	y = node.thecars[i].y;
	if(node.thecars[i].y+wid-1 == dim)	return 0;	

	while(j <= dim-(node.thecars[i].y+wid)+1){
		if((node.themap[node.thecars[i].x][node.thecars[i].y+j] == 'v' && node.themap[node.thecars[i].x][node.thecars[i].y+j+1] =='.') ||
			(node.themap[node.thecars[i].x][node.thecars[i].y+j+1] =='.') || (node.themap[node.thecars[i].x][node.thecars[i].y+j] == '|' && (node.themap[node.thecars[i].x][node.thecars[i].y+wid-1] == 'v'))){
			y += 1;
		
		}
		else return y;
		j+=1;

	}
	return y;
}

int up(STATE node, int i){
	int j, y, wid, allowed;
	wid = node.thecars[i].width;
	j = 1;
	y = node.thecars[i].y;
	if(node.thecars[i].y+wid-1 == 1)	return 0;
	while(j < node.thecars[i].y){
		if(node.themap[node.thecars[i].x][node.thecars[i].y-j] == '.'){
			y -= 1;
		}
		else return y;
		j+=1;
	}
	return y;
}


/*     ____________________________________
______/ DRAWING FUNCTIONS  AND FILE READING\_______________________________________________________________________________________________________*/
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
char readChar(FILE *fp){
    char a = fgetc(fp);
    if (isspace(a))	a = fgetc(fp);
    return a;
}
