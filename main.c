//
//  main.c
//  ship and stuff
//
//  Created by Victoria Chen and Kasper Schnack on 29/11/20.
//  Copyright © 2020 cuteppl. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

// error message to prevent overflow
#define ERR_NONE    0

// define constants
#define ROW_SIZE    10
#define COLUMN_SIZE 10

// grid struct
typedef struct {
    short row;
    short column;
} cell_t;


// helper functions, move later accordingly
int get_grid(short row, short column, int column_size) {
    // to get the index of a cell in the array using its coordinate
    return (row * (column_size) + column);
}

int *Human_UI()
{
	int row;
	char column;
	int *choice;
	choice = (int *) malloc(2*sizeof(int));
	while(1){
		printf("Where will you shoot? (1-10 / a-j)\n");
		scanf("%d %c", &row, &column);
		if (row >= 1 && row <= 10 && column >=97 && column < 107){
			choice[0] = row-1;
			choice[1] = column-97;
			break;
		}
		printf("Invalid input!!!\n");
	}
	return choice;
}

int main(int argc, const char * argv[]) {
    int *test = Human_UI();
    printf("%d %d", test[0], test[1]);
    return ERR_NONE;
}


