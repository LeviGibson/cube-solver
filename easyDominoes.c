//
// Created by levigibson on 6/26/21.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "easyDominoes.h"

#define easy_domino_hash_size 13831474

U64 domino_corner_keys[8][64];
U64 domino_edge_keys[12][32];

U64 uncompiled_edge_keys[12][3][2];
U64 uncompiled_corner_keys[8][3];

int domino_edge_types[12] = {0,0,0,0,1,1,1,1,2,2,2,2};

int easy_dominos_found = 0;
U64 easy_domino_hashes[easy_domino_hash_size];

void find_hashable_dominos(int depth){
    if (depth == 0){
        easy_domino_hashes[easy_dominos_found] = get_domino_key();
        easy_dominos_found++;
        return;
    }

    copy_cube();

    for (int move = 0; move < 18; move++){
        if (!is_repetition(move)){
            make_move(move);

            find_hashable_dominos(depth - 1);
            paste_cube();
        }
    }
}

int compare_dom( const void* a, const void* b)
{
    U64 int_a = * ( (U64*) a );
    U64 int_b = * ( (U64*) b );

    if ( int_a == int_b ) return 0;
    else if ( int_a < int_b ) return -1;
    else return 1;
}

void init_easy_domino_array(){
    for (int i = 0; i <= 6; i++) {
        find_hashable_dominos(i);
    }

    qsort(easy_domino_hashes, easy_domino_hash_size, sizeof(U64), compare_dom);

    printf("Found %d hashable dominos\n\n", easy_dominos_found);
}

U64 get_domino_key(){
    U64 key = 0;

    for (int corner = 0; corner < 8; corner++){
        key ^= uncompiled_corner_keys[corner][get_piece_orientation(corners[corner])];
    }
    for (int edge = 0; edge < 12; edge++){
        key ^= domino_edge_keys[edge][edges[edge]];
    }

    return key;
}

int cube_has_simple_domino(){
    U64 key = get_domino_key();

    int lower_bound = 0;
    int upper_bound = easy_domino_hash_size;

    while (1){
        int guess_id = (lower_bound + upper_bound)/2;
        U64 guess = easy_domino_hashes[guess_id];
        if (key > guess){
            lower_bound = guess_id;
        } else if (key < guess){
            upper_bound = guess_id;
        } else {
            return 1;
        }

        if (easy_domino_hashes[upper_bound] == key)
            return 1;
        if (easy_domino_hashes[lower_bound] == key)
            return 1;
        if (upper_bound - lower_bound < 2){
            return 0;
        }
    }
}

void init_easy_dominos(){

    for (int spot = 0; spot < 12; spot++){
        for (int etype = 0; etype < 3; etype++){
            for (int orin = 0; orin < 2; orin++){
                uncompiled_edge_keys[spot][etype][orin] = get_random_U64();
            }
        }
    }

    for (int spot = 0; spot < 8; spot++){
        for (int orin = 0; orin < 3; orin++){
            uncompiled_corner_keys[spot][orin] = get_random_U64();
        }
    }

    for (int spot = 0; spot < 12; spot++) {
        for (int etype = 0; etype < 32; etype++) {
            domino_edge_keys[spot][etype] = uncompiled_edge_keys[spot][domino_edge_types[get_piece_index(etype)]][get_piece_orientation(etype)];
        }
    }

    init_easy_domino_array();
}

