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

// grid struct
typedef struct {
    short row;
    short column;
} cell_t;


int main(int argc, const char * argv[]) {
    printf("Hello, World!\n");
    return ERR_NONE;
}


