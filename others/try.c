#include <stdio.h>
#include <stdlib.h>
#define dim 6

int main(){
    int k,j;
    char *** cmd = malloc(sizeof(char **) * dim+3);
    for(k = 0; k < dim+3; k++) {
        cmd[k] = malloc(sizeof(char *) * dim+3);
        for( j = 0; j < dim+3; j++)
               cmd[k][j] = malloc(5);
    }



}
