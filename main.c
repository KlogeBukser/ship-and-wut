//
//  main.c
//  ship and stuff
//
//  Created by Victoria Chen on 29/11/20.
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

#define HIT     1
#define MISS    0
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
int test_shot(short row, short column, char *grid);
int is_illegal(short row, short column);
void render(void);

int main(int argc, const char * argv[]) {
    
    //specify column size
    
    
    printf("Dumme svin!\n");
    render();
    return ERR_NONE;
}

int is_illegal(short row, short column);

int test_shot(short row, short column, char *grid) {
    if (is_illegal(row, column)) {
        return 0;
    }
    
    return HIT;
    return MISS;
}

int get_grid(short row, short column, int column_size) {
    // to get the index of a cell in the array using its coordinate
    return (row * (column_size) + column);
}

// get the grid for ships
char *read_ship_grid(short row_size, short column_size, int *ship_count) {
    char *new_grid; int i; short row, column, length, is_vertical;
    
    new_grid = (char *)malloc(row_size*(column_size)*sizeof(char));
    
    for (i=0;i<row_size*(column_size);i++) {
        new_grid[i] = 0;
    }
    
    while (4 == scanf("[%hd,%hd,%hd,%hd] ",&row, &column, &length, &is_vertical)) {
        for (i=0;i<length;i++) {
            
            new_grid[get_grid(row, column, column_size)] = 1;
            if (is_vertical) {
                column++;
            }
            else {
                row++;
            }
            (*ship_count)++;
        }
    }
    return new_grid;
}
