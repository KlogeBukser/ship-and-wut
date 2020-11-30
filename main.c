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

// direction of the ships
#define HORIZONTAL  0
#define VERTICAL    1

// shooting result
#define HIT     1
#define MISS    0
#define GAME_ERR_ILLEGAL_SHOT 2
#define INPUT_ERR_INVALID_CELL 3


// grid struct
typedef struct {
    short row;
    short column;
} cell_t;

typedef struct {
    int length;
    cell_t *start;
} ship_t;

// helper functions, move later accordingly
int get_grid(short row, short column, int column_size) ;
int is_illegal(short row, short column, short row_size, short column_size);
void render(void);
int *Human_UI();

int main(int argc, const char * argv[]) {
    
    //specify column size
    int *test = Human_UI();
    printf("%d %d", test[0], test[1]);
    render();
    return ERR_NONE;
}

int is_illegal(short row, short column, short row_size, short column_size) {
    
    if (0 <= row && row < row_size && 0 <= column && column < column_size) {
        return 0;
    }
    return 1;
}

// deal with shots
int test_shot(short row, short column, short row_size, short column_size, char *grid);

char *create_shotgrid(short row_size, short column_size) {
    
    char *shot_grid; int i;
    
    shot_grid = (char *)malloc(row_size*(column_size)*sizeof(char));
    assert(NULL != shot_grid);
    
    for (i=0;i<row_size*(column_size);i++) {
        shot_grid[i] = 0;
    }
    return shot_grid;
}

int take_shot(short row_size, short column_size, char *shot_grid, char *ship_grid) {
    
    short row, column; int result = INPUT_ERR_INVALID_CELL, i;
    
    for (i=0;i<5;i++) {
        if (2 == scanf("[%hd,%hd] ",&row, &column)) {
            if (1 == shot_grid[get_grid(row, column, column_size)]) {
                printf("You've shot here, try again you stupid fool!");
            }
            shot_grid[get_grid(row, column, column_size)] = 1;
            result = test_shot(row, column, row_size, column_size, ship_grid);
            break;
        }
        else {
            printf("Not a cell, please try again, %d times remaining", i);
        }
    }
     return result;
}

int test_shot(short row, short column, short row_size, short column_size, char *ship_grid) {
    
    if (is_illegal(row, column, column_size, row_size)) {
        printf("Your shot is not in the grid, stupid fwak");
        return GAME_ERR_ILLEGAL_SHOT;
    }
    
    if (1 == ship_grid[get_grid(row, column, column_size)]) {
        return HIT;
    }
    return MISS;
}

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

// get the grid for ships
char *read_ship_grid(short row_size, short column_size, int *ship_count) {
    char *ship_grid; int i; short row, column, length, is_vertical;
    
    ship_grid = (char *)malloc(row_size*(column_size)*sizeof(char));
    assert(NULL != ship_grid);
    
    for (i=0;i<row_size*(column_size);i++) {
        ship_grid[i] = 0;
    }
    
    while (4 == scanf("[%hd,%hd,%hd,%hd] ",&row, &column, &length, &is_vertical)) {
        for (i=0;i<length;i++) {
            
            ship_grid[get_grid(row, column, column_size)] = 1;
            if (is_vertical) {
                column++;
            }
            else {
                row++;
            }
            (*ship_count)++;
        }
    }
    
    // if no ship
    if (0 == *ship_count) {
        printf("No fucking ships you idiot!!");
    }
    
    return ship_grid;

}

//  free things
void free_mem(char* shot_grid, char* ship_grid) {
    free(shot_grid);
    free(ship_grid);
}
