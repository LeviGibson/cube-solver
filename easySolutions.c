//
// Created by levigibson on 6/25/21.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "easySolutions.h"

U64 corner_keys[8][64];
U64 edge_keys[12][32];

int hash_length = 5;
int four_move_hashes_found = 0;
U64 simple_position_hashes[100000];

const int domino_restrictions[18] = {0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1};


U64 get_random_U64(){
    U64 rando = 0ULL;
    rando |= (U64)rand();
    rando |= ((U64)rand() << 32);
    return rando;
}

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
    int upper_bound = 100000;

    while (1){
        int guess_id = (lower_bound + upper_bound)/2;
        U64 guess = simple_position_hashes[guess_id];
        if (key > guess){
            lower_bound = guess_id;
        } else if (key < guess){
            upper_bound = guess_id;
        } else {
            return 1;
        }

        if ((upper_bound - lower_bound) <= 1){
            if (simple_position_hashes[upper_bound] == key)
                return 1;
            if (simple_position_hashes[lower_bound] == key)
                return 1;
            return 0;
        }
    }

    /**
    for (int i = 0; i < 100000; i++){
        //printf("%ud\n", simple_position_hashes[i]);
        if (key == simple_position_hashes[i])
            return 1;
    }**/
}

void find_hashable_positions(int depth){
    if (depth == 0){
        simple_position_hashes[four_move_hashes_found] = get_cube_key();
        four_move_hashes_found++;
        return;
    }

    copy_cube();

    for (int move = 0; move < 18; move++){
        if (domino_restrictions[move]){
            make_move(move);

            find_hashable_positions(depth-1);
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

void init_magic_hashes(){
    find_hashable_positions(5);
    qsort( simple_position_hashes, 100000, sizeof(U64), compare);
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
