//
// Created by levigibson on 6/25/21.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "easySolutions.h"

#define simple_solution_hash_size 14739521

U64 corner_keys[8][64];
U64 edge_keys[12][32];
int four_move_hashes_found = 0;

U64 simple_solution_hashes[simple_solution_hash_size];

const int domino_restrictions[18] = {0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1};

U64 get_cube_key(){
    U64 key = 0;
    for (int corner = 0; corner < 8; corner++){
        key ^= corner_keys[corner][corners[corner]];
    }
    for (int edge = 0; edge < 12; edge++){
        key ^= edge_keys[edge][edges[edge]];
    }

    return key;
}

int cmpfunc(const void * a, const void * b) {
    return (int)(*(U64*)a - *(U64*)b);
}

int cube_has_simple_solution() {
    U64 key = get_cube_key();
    int *id = (int*)bsearch((void*)&key, simple_solution_hashes, simple_solution_hash_size, sizeof(U64), cmpfunc);
    return id != NULL;
}

void find_hashable_solutions(int depth){
    if (depth == 0){
        simple_solution_hashes[four_move_hashes_found] = get_cube_key();
        four_move_hashes_found++;
        return;
    }

    copy_cube();

    for (int move = 0; move < 18; move++){
        if (domino_restrictions[move] && (!full_is_repetition(move))){
            make_move(move);

            find_hashable_solutions(depth - 1);
            paste_cube();
        }
    }
}



void init_easy_solutions(){
    reset_cube_history();
    for (int i = 0; i <= 8; i++) {
        history = -1;
        find_hashable_solutions(i);
    }

    qsort(simple_solution_hashes, simple_solution_hash_size, sizeof(U64), cmpfunc);
    printf("Found %d hashable solutions\n", four_move_hashes_found);
}

void init_key_generator(){
    for (int cs = 0; cs < 8; cs++){
        for (int corner = 0; corner < 64; corner++){
            corner_keys[cs][corner] = get_random_U64();
        }
    }
    for (int es = 0; es < 12; es++){
        for (int edge = 0; edge < 32; edge++){
            edge_keys[es][edge] = get_random_U64();
        }
    }
}

void print_U64_binary(U64 number){
    printf("\n");
    for (int i = 0; i < 64; i++) {
        if (i % 8 == 0)
            printf("\n");
        if ((number >> i) & 1ULL){
            printf(" 1 ");
        } else {
            printf(" 0 ");
        }
    }
    printf("\n");
}
