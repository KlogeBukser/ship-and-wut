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
#define SHIP_COUNT  5

// direction of the ships
#define HORIZONTAL  0
#define VERTICAL    1

// shooting result
#define HIT     1
#define MISS    0
#define GAME_ERR_ILLEGAL_SHOT   2
#define INPUT_ERR_INVALID_CELL  3

//visualising symbols
#define MISS_SHOT   'X'
#define HIT_SHOT    'O'

// grid struct
typedef struct {
    short row;
    short column;
} cell_t;

// helper functions, move later accordingly
int get_grid(short row, short column, int column_size) ;
int is_illegal(short row, short column, short row_size, short column_size);
void render(void);
void graph(short column_size, short row_size, char *shot_grid, char *ship_grid);
char *create_shotgrid(short row_size, short column_size);
char *place_ships(short row_size, short column_size, int ship_count);
int test_shot(int *result, short row_size, short column_size, char *ship_grid);


int *shoot_ship()
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
    
    int ship_count = SHIP_COUNT, *shot, result;
    char *shotgrid, *shipgrid;
    
    //debug
    shotgrid = create_shotgrid(ROW_SIZE, COLUMN_SIZE);
    shipgrid = place_ships(ROW_SIZE, COLUMN_SIZE, ship_count);
    shot = shoot_ship();
    result = test_shot(shot, ROW_SIZE, COLUMN_SIZE, shipgrid);
    
    graph(COLUMN_SIZE, ROW_SIZE, shotgrid, shipgrid);
    
    printf("Dumme svin!\n");
    return ERR_NONE;
    
}

void graph(short column_size, short row_size, char *shot_grid, char *ship_grid) {
    // generate of graph of a full path
    int i, j, pos;
    
    printf("%c", '\n');
    printf("%c", ' ');
    
    // row 1
    for (i=0;i<column_size;i++) {
        printf("%d",i);
        
    }
    printf("%c", '\n');
    
    for (i=0;i<row_size;i++) {
        for (j=0;j<=column_size;j++) {
            pos = get_grid(i, j, column_size);
            if (0 == j) {
                printf("%d",i);
            }
            if (1 == shot_grid[pos]) {
                if (1 == shot_grid[pos]) {
                    printf("%c", HIT_SHOT);
                }
                else {
                    printf("%c", MISS_SHOT);
                }
            }
            else {
                printf("%c",' ');
            }
        }
        printf("%c",'\n');
    }
}

int is_illegal(short row, short column, short row_size, short column_size) {
    
    if (0 < row && row < row_size && 0 < column && column < column_size) {
        return 0;
    }
    return 1;
}

// deal with shots

char *create_shotgrid(short row_size, short column_size) {
    char *shot_grid; int i;
    
    shot_grid = (char *)malloc(row_size*(column_size)*sizeof(char));
    assert(NULL != shot_grid);
    
    for (i=0;i<row_size*(column_size);i++) {
        shot_grid[i] = 0;
    }
    return shot_grid;
}



int test_shot(int* choice, short row_size, short column_size, char *ship_grid) {
    
    if (is_illegal(choice[0], choice[1], column_size, row_size)) {
        printf("Your shot is not in the grid, stupid fwak \n");
        return GAME_ERR_ILLEGAL_SHOT;
    }
    
    if ('1' == ship_grid[get_grid(choice[0], choice[1], column_size)]) {
        return HIT;
    }
    return MISS;
}

int get_grid(short row, short column, int column_size) {
    // to get the index of a cell in the array using its coordinate
    return (row * (column_size) + column);
}

// get the grid for ships
char *place_ships(short row_size, short column_size, int ship_count) {
    char *ship_grid; int i; short row, column, length, is_vertical;
    
    ship_grid = (char *)malloc(row_size*(column_size)*sizeof(char));
    assert(NULL != ship_grid);
    
    for (i=0;i<row_size*(column_size);i++) {
        ship_grid[i] = 0;
    }
    
    printf("give a ship, in the format of [row, column, length, is_vertical] \n");
    for (i=0;i<ship_count;i++) {
         if (4 == scanf("[%hd,%hd,%hd,%hd] ",&row, &column, &length, &is_vertical)) {
               for (i=0;i<length;i++) {
                   if (is_illegal(row, column, row_size, column_size)) {
                       printf("illegal bitch!!! \n");
                       break;
                   }
                   ship_grid[get_grid(row, column, column_size)] = 1;
                   if (is_vertical) {
                       column++;
                   }
                   else {
                       row++;
                   }

               }
         }
    }
    
    return ship_grid;
}

//  free things
void free_mem(char* shot_grid, char* ship_grid) {
    free(shot_grid);
    free(ship_grid);
}
