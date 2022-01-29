//
// Created by levigibson on 6/21/21.
//

#include "search.h"
#include "easySolutions.h"
#include "easyDominoes.h"
#include <string.h>
#include <stdio.h>

#define UNSOLVED 5000

//enum{R, L, U, D, F, B, RP, LP, UP, DP, FP, BP, R2, L2, U2, D2, F2, B2};
int movesides[18] = {R, L, U, D, F, B, R, L, U, D, F, B, R, L, U, D, F, B};

int searchPath[MAX_PLY];
int ply;

void search(float depth, int extention){
    if (is_cube_solved()) {
//        printf("found solution at ply %d\n", ply);
        for (int i = 0; i < ply; ++i) {
            print_move(searchPath[i]);
            printf(" ");
        }
        printf("\n");
        return;
    }

    if (depth <= 0){
        return;
    }

    if (!extention && cube_has_simple_solution()){
//        printf("found easty solution at ply %d\n", ply);
//        for (int i = 0; i < ply; ++i) {
//            print_move(searchPath[i]);
//            printf(" ");
//        }
//        printf("\n");
        depth += 7;
        extention = 1;
    }

    copy_cube();
    int searchPathCopy[MAX_PLY];
    memcpy(searchPathCopy, searchPath, sizeof(searchPath));

    for (int move = R; move <= B2; move++) {
        if (full_is_repetition(move))
            continue;

        make_move(move);

        if (extention && !cube_has_simple_solution()) {
            paste_cube();
            continue;
        }

        searchPath[ply] = move;

        ply++;
        search(depth-1, extention);
        ply--;

        paste_cube();
        memcpy(searchPath, searchPathCopy, sizeof(searchPath));

    }
}

int search_position(){
    ply = 0;
    handpos = 0;
    memset(searchPath, 0, sizeof searchPath);

    for (int currentDepth = 0; currentDepth < MAX_PLY; ++currentDepth) {
        printf("depth %d\n", currentDepth);
        search((float)currentDepth, 0);
    }
}