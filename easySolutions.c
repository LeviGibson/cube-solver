//
// Created by levigibson on 6/25/21.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "easySolutions.h"

#define simple_solution_hash_size 21745698

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

int cube_has_simple_solution(){
    U64 key = get_cube_key();

    int lower_bound = 0;
    int upper_bound = simple_solution_hash_size;

    while (1){
        int guess_id = (lower_bound + upper_bound)/2;
        U64 guess = simple_solution_hashes[guess_id];
        if (key > guess){
            lower_bound = guess_id;
        } else if (key < guess){
            upper_bound = guess_id;
        } else {
            return 1;
        }

        if (simple_solution_hashes[upper_bound] == key)
            return 1;
        if (simple_solution_hashes[lower_bound] == key)
            return 1;
        if (upper_bound - lower_bound < 2){
            return 0;
        }
    }

    /**
    for (int i = 0; i < 100000; i++){
        //printf("%ud\n", simple_solution_hashes[i]);
        if (key == simple_solution_hashes[i])
            return 1;
    }**/
}

void find_hashable_solutions(int depth){
    if (depth == 0){
        simple_solution_hashes[four_move_hashes_found] = get_cube_key();
        four_move_hashes_found++;
        return;
    }

    copy_cube();

    for (int move = 0; move < 18; move++){
        if (domino_restrictions[move] && (!is_repetition(move))){
            make_move(move);

            find_hashable_solutions(depth - 1);
            paste_cube();
        }
    }
}

int compare( const void* a, const void* b)
{
    U64 int_a = * ( (U64*) a );
    U64 int_b = * ( (U64*) b );

    if ( int_a == int_b ) return 0;
    else if ( int_a < int_b ) return -1;
    else return 1;
}

void init_easy_solutions(){
    for (int i = 0; i <= 8; i++) {
        history = -1;
        find_hashable_solutions(i);
    }

    qsort(simple_solution_hashes, simple_solution_hash_size, sizeof(U64), compare);
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
