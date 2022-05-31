//
// Created by levigibson on 6/21/21.
//

#include "search.h"
#include "easySolutions.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

int searchPath[MAX_PLY];
int ply;

void search(float depth, int extention){
//    if (ply == 1 && history == U) depth++;
    assert(ply < MAX_PLY);

    if (is_cube_solved()) {
        for (int i = 0; i < ply; ++i) {
            print_move(searchPath[i]);
            printf(" ");
        }
        printf("(%d)\n", ply);
        return;
    }

    if (depth <= 0){
        return;
    }

    if (!extention && cube_has_simple_solution()){
        printf("found easty solution at ply %d with hash %llx\n", ply, get_cube_key());
        for (int i = 0; i < ply; ++i) {
            print_move(searchPath[i]);
            printf(" ");
        }
        printf("\n%d\n", handpos);
        depth += 9;
        extention = 1;
    }

    copy_cube();
    int searchPathCopy[MAX_PLY];
    memcpy(searchPathCopy, searchPath, sizeof(searchPath));

    for (int move = R; move <= M2; move++) {
        paste_cube();
        float ds = 0;

        if (move == R)
            handpos += 1;

        if (move == RP)
            handpos -= 1;

        if (move == R2) {
            if (handpos == 0)
                continue;
            handpos = -handpos;
        }

        if (handpos > 1 || handpos < -1) {
            ds += 4;
            handpos = 0;
        }

        if (move == B || move == BP || move == B2) {
            if (handpos != 1)
                ds += 6;
        }

        if (move == L2)
            ds += 2;

        if (move == L || move == LP){
            ds+=1;
            if (searchPath[ply-1] == R || searchPath[ply-1] == RP || searchPath[ply-1] == R2)
                ds += 6;
        }

        if (move == M2 || move == M) {
            if ((searchPath[ply-2] != M) && (searchPath[ply-2] != MP) && (searchPath[ply-2] != M2)){
                ds += 4;
            }
        }

        if (full_is_repetition(move))
            continue;

        if (move == F2 || move == R2 || move == L2 || move == B2 || move == D2)
            ds += 0.75f;

        if (move == F2){
            if (searchPath[ply-2] == F2) {
                ds += 6;
            }
        }

        if (move == F2 || move == FP || move == F){
            if (handpos == 0)
                ds += 6;
            if (handpos == 1)
                ds += 4;
        }

        make_move(move);

        if (extention && !cube_has_simple_solution()) {
            continue;
        }

        searchPath[ply] = move;

        ply++;
        search(depth - 1 - ds, extention);
        ply--;

        memcpy(searchPath, searchPathCopy, sizeof(searchPath));

    }

    paste_cube();
}

int search_position(){
    ply = 0;
    handpos = 0;
    memset(searchPath, 0, sizeof searchPath);

    for (int currentDepth = 0; currentDepth < MAX_PLY; ++currentDepth) {
        printf("depth %d\n", currentDepth);
        reset_cube_history();
        handpos = 0;

        search((float)currentDepth, 0);
    }
}