//
// Created by levigibson on 6/25/21.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "easySolutions.h"

#define simple_solution_hash_size 10223620

U64 corner_keys[8][64][64];
U64 edge_keys[12][32][32];
int four_move_hashes_found = 0;

U64 simple_solution_hashes[simple_solution_hash_size];

U64 get_cube_key() {
    U64 key = 0;
    for (int corner = 1; corner < 8; corner++) {
        key ^= corner_keys[corner][corners[corner]][corners[corner-1]];
    }
    for (int edge = 1; edge < 12; edge++) {
        key ^= edge_keys[edge][edges[edge]][edges[edge-1]];
    }

    return key;
}

int cmpfunc(const void *a, const void *b) {
//    return (int) (*(U64 *) a - *(U64 *) b);
    if (*(U64 *) a > *(U64 *) b) return 1;
    if (*(U64 *) a < *(U64 *) b) return -1;
    return 0;
}

int cube_has_simple_solution() {
    U64 key = get_cube_key();
    int *id = (int*)bsearch((void*)&key, simple_solution_hashes, simple_solution_hash_size, sizeof(U64), cmpfunc);
    return id != NULL;
}

void find_hashable_solutions(int depth) {
    simple_solution_hashes[four_move_hashes_found] = get_cube_key();
    four_move_hashes_found++;

    if (depth == 0) {
        return;
    }

    copy_cube();

    for (int move = 0; move < 18; move++) {
        if (!full_is_repetition(move)) {
            make_move(move);

            find_hashable_solutions(depth - 1);
            paste_cube();
        }
    }
}


void init_easy_solutions() {

    find_hashable_solutions(6);

    qsort(simple_solution_hashes, simple_solution_hash_size, sizeof(U64), cmpfunc);
//    for (int i = 0; i < simple_solution_hash_size; ++i) {
//        printf("%d\n", simple_solution_hashes[i] >= simple_solution_hashes[i-1]);
//    }
    printf("Found %d hashable solutions\n", four_move_hashes_found);
}

void init_key_generator() {
    for (int cs = 0; cs < 8; cs++) {
        for (int i = 0; i < 64; ++i) {
            for (int corner = 0; corner < 64; corner++) {
                corner_keys[cs][corner][i] = get_random_U64();
            }
        }
    }
    for (int es = 0; es < 12; es++) {
        for (int i = 0; i < 32; ++i) {
            for (int edge = 0; edge < 32; edge++) {
                edge_keys[es][i][edge] = get_random_U64();
            }
        }
    }
}

void print_U64_binary(U64 number) {
    printf("\n");
    for (int i = 0; i < 64; i++) {
        if (i % 8 == 0)
            printf("\n");
        if ((number >> i) & 1ULL) {
            printf(" 1 ");
        } else {
            printf(" 0 ");
        }
    }
    printf("\n");
}
