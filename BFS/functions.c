#include "declaration.h"

int dim, listCtr, numExp, numCars, bottom, viCtr, x, y; //+3 for the borders and the newline "\n"
/*
///LINKED-STACK IMPLEMENTATIONS
void create(){
	top = NULL;
}
void push(STATE info){
	if(top==NULL){												//VERY FIRST PUSH:
		top = (struct NodeStack *) malloc(1*sizeof(struct NodeStack));	//so top will personally receive its first information
		top->prev = NULL;
		top->data = info;
	}
	else{
		cur = (struct NodeStack *) malloc(1*sizeof(struct NodeStack));	//NOT THE FIRST PUSH:
		cur->prev = top;										//so a cur will temporarily hold the top as its previous,
		cur->data = info;										//and it will take the new information.
		top = cur;												//Then, top will later on take everything from cur
	}
}
void pop(){														//the cur will hold the prev node, the next top element,
	if(top==NULL)	 return;									//then free/delete the old top node.
	else{
		cur=top->prev;
		free(top);
		top = cur;
	}
}

STATE peek(){
	return top->data;											//Returns the top value
}

*/
//AALL ABOUT THE NODE
void init(STATE *node){
	node->g = 0;
	node->h = 0;
	node->f = 0;
	node->parent = NULL;
}

int h(STATE node){
	return node.h;
}

int g(STATE node){
	return node.g;
}

int f(STATE node){
	//printf("g: %d, h: %d\n", g(node), h(node));
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


//REMOVING
/*
int* remove (int* array, int sizeofArray, int indexremove){
	int* temp = mallloc ((sizeofArray-10 * sizeof(int)); //allocate an array with a size less than curr

	if(indexremove != 0)
		memcpy(temp, array, (indexremmove-1) * sizeof(int)); //copy everything BEFORE the indexremmove

	if(indexremove != (sizeofArray-1))
			memcpy(temp+indexremove, array+indexremove+1, (sizeofArray-indexremove-1)*sizeof(int)); //copy aftr index

		free (array);
		return temp;
}*/

//ALL ABOUT THE LIST/MOVE

int removeNode(STATE node){
	int i, m, ay;
	STATE temp;
	for(i = 0; i < listCtr; i++){
		for(m = 1; m< numCars; m++){
			if (node.thecars[m].x != move[i].thecars[m].x || node.thecars[m].y != move[i].thecars[m].y) {
					ay = -1;
					break;
			}
			else ay = i;
		}
		if (ay > -1)	break;
	}
	//listCtr = listCtr - 1;
	temp = move[bottom];
	move[bottom] = move[ay];
	move[ay] = temp;
	for( i = 0; i < listCtr-1 ; i++){
		move[ay+i] = move[ay+i+1];
	}
	return bottom+=1;
}


int addmove(STATE newmove){
	if(listCtr == 0) move = (struct States *) realloc(move, sizeof(STATE));	//need to allocate dynamically
	else move = (struct States *) realloc(move, sizeof(STATE)*listCtr*2);	//need to allocate dynamically
	move[listCtr] = newmove;
	listCtr = listCtr + 1;
	//delete(newmove);
	return listCtr;
}

STATE get_move_lowF(){
	int i, lowCost = f(move[0]);
	STATE lowNode = move[0];
	for(i = bottom; i < listCtr; i++){
//		printf("f(move[%d])= %d < lowCost= %d \n", i, f(move[i]), lowCost);
		if (f(move[i]) < lowCost){
			lowCost = f(move[i]);
			lowNode = move[i];
		}
	}
	return lowNode;
}

int goal(STATE node, STATE start){
	int mika;
	STATE curr, *temp;
	//printf(" car.x: %d vs. goal.x: %d\n", node.thecars[1].x, x);
	if(node.thecars[1].x == x && node.thecars[1].y == y){
		printf(">> ACHIEVED GOAL <<\n\nFrom:\n");
		draw(start.thecars);
		printf("To: \n");
		draw(node.thecars);
		curr = node;
		printf("%d\n", curr.g);
		printf("Expanded %d Nodes\n", numExp);

		/*while(curr.parent!=NULL || curr.parent != 0){
			curr = *curr.parent;
			printf("WITH COST: %d after Expanding %d Nodes\n", curr.g, numExp);
			scanf("%d", &mika);
		}*/

															//create()Create Stack for Operators
		return 1;
	}
//	printf(">>UNDER CONSTRUCTION(function.c->int goal())<< Always return 1 for now para no infinite loop\n");
	return 0;
}


int right(CAR thecars[], int i){
	int j, x, wid;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int k;
	char themap[dim+3][dim+3];
	//INIT BOARD
	for(k = 0; k<= dim+1; k++){
			for(j = 0; j <= dim+1; j++){
					if(k == 0 || k == dim+1){
						if (j == 0 || j == dim+1)   themap[j][k] = '+';
						else    themap[j][k] = '-';
					}
					else if(j == 0 || j == dim+1)	  themap[j][k] = '|';
					else  themap[j][k] ='.';
			}
	}
	//place spaces and new line
	for(k = 0; k<dim+3; k++)	  themap[dim+2][k] = '\n';
	for(k = 0; k<dim+3; k++){
		 themap[k][dim+2] = ' ';
		if(k==dim+2)  themap[k][dim+2] = '\n';
		if(thecars[1].dir == 'h')    themap[(dim+1)][thecars[1].y] = ' ';
		else if(thecars[1].dir == 'v')    themap[thecars[1].x][(dim+1)] = ' ';
	}

	//placing the car accdg to their x & y coordinates and checking their orientations to know which way to expand legth of car accdg to its width
	for(k = 1; k <= numCars; k++){
		if(thecars[k].dir == 'v'){
			  themap[thecars[k].x][thecars[k].y] = '^';
			for(j = 1; j < thecars[k].width - 1; j++)	   themap[thecars[k].x][thecars[k].y+j] = '|';
			  themap[thecars[k].x][thecars[k].y+(thecars[k].width-1)] = 'v';
		}
		else if(thecars[k].dir == 'h'){
			  themap[thecars[k].x][thecars[k].y] = '<';
			for(j = 1; j < thecars[k].width - 1; j++)	   themap[thecars[k].x+j][thecars[k].y] = '=';
			  themap[thecars[k].x+(thecars[k].width-1)][thecars[k].y] = '>';
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	wid = thecars[i].width;
	j = 1;
	x = thecars[i].x;
	if(thecars[i].x+wid-1 == dim)	return 0;
	while(j <= dim-thecars[i].x-wid+1){
		if((themap[thecars[i].x+j][thecars[i].y] == '>' && themap[thecars[i].x+j+1][thecars[i].y] =='.') ||
			(themap[thecars[i].x+j+1][thecars[i].y] =='.') ||
		(themap[thecars[i].x+j][thecars[i].y] == '=' && (themap[thecars[i].x+wid-1][thecars[i].y] == '>'))){
			x += 1;
		}
		else return x;
		j+=1;
	}
	return x;
}

int left(CAR thecars[], int i){
	int j, x, wid, allowed;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int k;
	char themap[dim+3][dim+3];
	//INIT BOARD
	for(k = 0; k<= dim+1; k++){
			for(j = 0; j <= dim+1; j++){
					if(k == 0 || k == dim+1){
						if (j == 0 || j == dim+1)   themap[j][k] = '+';
						else    themap[j][k] = '-';
					}
					else if(j == 0 || j == dim+1)	  themap[j][k] = '|';
					else  themap[j][k] ='.';
			}
	}
	//place spaces and new line
	for(k = 0; k<dim+3; k++)	  themap[dim+2][k] = '\n';
	for(k = 0; k<dim+3; k++){
		 themap[k][dim+2] = ' ';
		if(k==dim+2)  themap[k][dim+2] = '\n';
		if(thecars[1].dir == 'h')    themap[(dim+1)][thecars[1].y] = ' ';
		else if(thecars[1].dir == 'v')    themap[thecars[1].x][(dim+1)] = ' ';
	}

	//placing the car accdg to their x & y coordinates and checking their orientations to know which way to expand legth of car accdg to its width
	for(k = 1; k <= numCars; k++){
		if(thecars[k].dir == 'v'){
			  themap[thecars[k].x][thecars[k].y] = '^';
			for(j = 1; j < thecars[k].width - 1; j++)	   themap[thecars[k].x][thecars[k].y+j] = '|';
			  themap[thecars[k].x][thecars[k].y+(thecars[k].width-1)] = 'v';
		}
		else if(thecars[k].dir == 'h'){
			  themap[thecars[k].x][thecars[k].y] = '<';
			for(j = 1; j < thecars[k].width - 1; j++)	   themap[thecars[k].x+j][thecars[k].y] = '=';
			  themap[thecars[k].x+(thecars[k].width-1)][thecars[k].y] = '>';
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	wid = thecars[i].width;
	//allowed = dim - wid;
	j = 1;
	x = thecars[i].x;

	if(thecars[i].x+wid-1 == 1)	return 0;	//dim or dim + 1?? gaaah try both if error
	while(j < thecars[i].x){//dim-thecars[i].x-wid+1){
		if(themap[thecars[i].x-j][thecars[i].y] == '.'){
			x -= 1;
		}
		else return x;
		j+=1;
	}
	return x;
}

int down(CAR thecars[], int i){
	int j, y, wid;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int k;
	char themap[dim+3][dim+3];
	//INIT BOARD
	for(k = 0; k<= dim+1; k++){
			for(j = 0; j <= dim+1; j++){
					if(k == 0 || k == dim+1){
						if (j == 0 || j == dim+1)   themap[j][k] = '+';
						else    themap[j][k] = '-';
					}
					else if(j == 0 || j == dim+1)	  themap[j][k] = '|';
					else  themap[j][k] ='.';
			}
	}
	//place spaces and new line
	for(k = 0; k<dim+3; k++)	  themap[dim+2][k] = '\n';
	for(k = 0; k<dim+3; k++){
		 themap[k][dim+2] = ' ';
		if(k==dim+2)  themap[k][dim+2] = '\n';
		if(thecars[1].dir == 'h')    themap[(dim+1)][thecars[1].y] = ' ';
		else if(thecars[1].dir == 'v')    themap[thecars[1].x][(dim+1)] = ' ';
	}

	//placing the car accdg to their x & y coordinates and checking their orientations to know which way to expand legth of car accdg to its width
	for(k = 1; k <= numCars; k++){
		if(thecars[k].dir == 'v'){
			  themap[thecars[k].x][thecars[k].y] = '^';
			for(j = 1; j < thecars[k].width - 1; j++)	   themap[thecars[k].x][thecars[k].y+j] = '|';
			  themap[thecars[k].x][thecars[k].y+(thecars[k].width-1)] = 'v';
		}
		else if(thecars[k].dir == 'h'){
			  themap[thecars[k].x][thecars[k].y] = '<';
			for(j = 1; j < thecars[k].width - 1; j++)	   themap[thecars[k].x+j][thecars[k].y] = '=';
			  themap[thecars[k].x+(thecars[k].width-1)][thecars[k].y] = '>';
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	wid = thecars[i].width;
	j = 1;
	y = thecars[i].y;
	if(thecars[i].y+wid-1 == dim)	return 0;
	while(j <= dim-(thecars[i].y+wid)+1){
		if((themap[thecars[i].x][thecars[i].y+j] == 'v' && themap[thecars[i].x][thecars[i].y+j+1] =='.') ||
			(themap[thecars[i].x][thecars[i].y+j+1] =='.') || (themap[thecars[i].x][thecars[i].y+j] == '|' && (themap[thecars[i].x][thecars[i].y+wid-1] == 'v'))){
			y += 1;
		}
		else return y;
		j+=1;
	}
	return y;
}

int up(CAR thecars[], int i){
	int j, y, wid, allowed;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int k;
	char themap[dim+3][dim+3];
	//INIT BOARD
	for(k = 0; k<= dim+1; k++){
			for(j = 0; j <= dim+1; j++){
					if(k == 0 || k == dim+1){
						if (j == 0 || j == dim+1)   themap[j][k] = '+';
						else    themap[j][k] = '-';
					}
					else if(j == 0 || j == dim+1)	  themap[j][k] = '|';
					else  themap[j][k] ='.';
			}
	}
	//place spaces and new line
	for(k = 0; k<dim+3; k++)	  themap[dim+2][k] = '\n';
	for(k = 0; k<dim+3; k++){
		 themap[k][dim+2] = ' ';
		if(k==dim+2)  themap[k][dim+2] = '\n';
		if(thecars[1].dir == 'h')    themap[(dim+1)][thecars[1].y] = ' ';
		else if(thecars[1].dir == 'v')    themap[thecars[1].x][(dim+1)] = ' ';
	}

	//placing the car accdg to their x & y coordinates and checking their orientations to know which way to expand legth of car accdg to its width
	for(k = 1; k <= numCars; k++){
		if(thecars[k].dir == 'v'){
			  themap[thecars[k].x][thecars[k].y] = '^';
			for(j = 1; j < thecars[k].width - 1; j++)	   themap[thecars[k].x][thecars[k].y+j] = '|';
			  themap[thecars[k].x][thecars[k].y+(thecars[k].width-1)] = 'v';
		}
		else if(thecars[k].dir == 'h'){
			  themap[thecars[k].x][thecars[k].y] = '<';
			for(j = 1; j < thecars[k].width - 1; j++)	   themap[thecars[k].x+j][thecars[k].y] = '=';
			  themap[thecars[k].x+(thecars[k].width-1)][thecars[k].y] = '>';
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	wid = thecars[i].width;
	j = 1;
	y = thecars[i].y;
	if(thecars[i].y+wid-1 == 1)	return 0;
	while(j < thecars[i].y){
		if(themap[thecars[i].x][thecars[i].y-j] == '.'){
			y -= 1;
		}
		else return y;
		j+=1;
	}
	return y;
}


/*     ____________________________________
______/ DRAWING FUNCTIONS  AND FILE READING\_______________________________________________________________________________________________________*/
void draw(CAR thecars[]){
	char themap[dim+3][dim+3];
	int i, j;
	//INIT BOARD
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
		if(thecars[1].dir == 'h')    themap[(dim+1)][thecars[1].y] = ' ';
		else if(thecars[1].dir == 'v')    themap[thecars[1].x][(dim+1)] = ' ';
	}

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
	for(i = 0; i<= dim+2; i++) for(j = 0; j <= dim+2; j++)	printf(" %c",  themap[j][i]);
}

char readChar(FILE *fp){
    char a = fgetc(fp);
    if (isspace(a))	a = fgetc(fp);
    return a;
}
