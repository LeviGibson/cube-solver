//
// Created by levigibson on 6/21/21.
//

#ifndef CUBE_SOLVER_SEARCH_H
#define CUBE_SOLVER_SEARCH_H

#include "cube.h"
#define SOLVESCORE 50000

typedef struct LINE {
    U8 moves[64];
    int length;
} line;

void search_position();

#endif //CUBE_SOLVER_SEARCH_H
