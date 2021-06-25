//
// Created by levigibson on 6/18/21.
//

#ifndef CFOPSOLVER_CUBE_H
#define CFOPSOLVER_CUBE_H

#include <stdint-gcc.h>
#define U8 uint8_t
#define U64 unsigned long long
#define U32 unsigned int

enum{R, L, U, D, F, B, RP, LP, UP, DP, FP, BP, R2, L2, U2, D2, F2, B2};

#define encode_piece(index, orientation) \
    ((index) | ((orientation) << 4))

#define get_piece_index(piece) ((piece) & 15)
#define get_piece_orientation(piece) ((piece) >> 4)

/**
#define increment_corner_orientation(corner) \
    corner = (encode_piece(get_piece_index((corner)), (get_piece_orientation((corner)) + 1)%3))

#define decrement_corner_orientation(corner) \
    corner = (encode_piece(get_piece_index((corner)), (get_piece_orientation((corner)) + 2)%3))**/

#define increment_corner_orientation(corner) \
    corner = corner_twists[corner][1]

#define decrement_corner_orientation(corner) \
    corner = corner_twists[corner][0]

#define increment_corner_orientation_otf(corner) \
    (encode_piece(get_piece_index((corner)), (get_piece_orientation((corner)) + 1)%3))

#define decrement_corner_orientation_otf(corner) \
    (encode_piece(get_piece_index((corner)), (get_piece_orientation((corner)) + 2)%3))

#define flip_edge(edge) \
    edge = (edge) ^ 16

#define copy_cube() \
    U8 corners_copy[8];   \
    U8 edges_copy[12];    \
    int history_copy[2];    \
    int history_length_copy = history_length; \
    memcpy(history_copy, history, sizeof history_copy);   \
    memcpy(edges_copy, edges, sizeof(edges_copy)); \
    memcpy(corners_copy, corners, sizeof(corners_copy)) \

#define paste_cube() \
    memcpy(edges, edges_copy, sizeof edges); \
    memcpy(corners, corners_copy, sizeof corners); \
    memcpy(history, history_copy, sizeof history); \
    history_length = history_length_copy

U8 corners[8];
U8 edges[12];

int history[2];
int history_length;

void init_cube();

void make_move(int move);

void parse_alg(char *alg);

int is_cube_solved();
int is_repetition(int move);

void print_move(int move);
void print_cube();
void print_piece_binary(U8 piece);

#endif //CFOPSOLVER_CUBE_H
