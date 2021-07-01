//
// Created by levigibson on 6/21/21.
//

#ifndef CUBE_SOLVER_SEARCH_H
#define CUBE_SOLVER_SEARCH_H

#include "cube.h"
#include <immintrin.h>
#define SOLVESCORE 50000
#define FAIL_LOW 25000

typedef struct LINE {
    U8 moves[4][32];
    int length[4];
} line;

int iterative_deepening(line *pv, int io, int make_moves);
int search_position(int io);

static inline int get_time_ms()
{
    #ifdef WIN64
        return GetTickCount();
    #else
    #include <sys/time.h>
        struct timeval time_value;
        gettimeofday(&time_value, NULL);
        return time_value.tv_sec * 1000 + time_value.tv_usec / 1000;
    #endif
}

#endif //CUBE_SOLVER_SEARCH_H
