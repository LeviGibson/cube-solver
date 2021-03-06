//
// Created by levigibson on 6/18/21.
//

#ifndef CFOPSOLVER_CUBE_H
#define CFOPSOLVER_CUBE_H

#include <stdint-gcc.h>
#define U8 uint8_t
#define U64 unsigned long long
#define U32 unsigned int

int handpos;
enum{R, L, U, D, F, B, RP, LP, UP, DP, FP, BP, R2, L2, U2, D2, F2, B2, M, MP, M2};
enum{X, Y, Z, XP, YP, ZP, X2, Y2, Z2};
enum{AXIS_M, AXIS_E, AXIS_S};
enum{SIDE_R, SIDE_L, SIDE_U, SIDE_D, SIDE_F, SIDE_B};

int8_t axisHistory[3];
int8_t sideHistory[6];
int8_t moveToSide[21];

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
    int moveTransformer_copy[21];\
    int8_t axisHistory_copy[3]; \
    int8_t sideHistory_copy[6]; \
    int handpos_copy = handpos;  \
    memcpy(edges_copy, edges, sizeof(edges_copy)); \
    memcpy(axisHistory_copy, axisHistory, sizeof(axisHistory_copy)); \
    memcpy(sideHistory_copy, sideHistory, sizeof(sideHistory_copy)); \
    memcpy(corners_copy, corners, sizeof(corners_copy)); \
    memcpy(moveTransformer_copy, moveTransformer, sizeof(moveTransformer))

#define paste_cube() \
    memcpy(edges, edges_copy, sizeof edges); \
    memcpy(corners, corners_copy, sizeof corners); \
    handpos = handpos_copy;                 \
    memcpy(moveTransformer, moveTransformer_copy, sizeof(moveTransformer)); \
    memcpy(axisHistory, axisHistory_copy, sizeof(axisHistory_copy)); \
    memcpy(sideHistory, sideHistory_copy, sizeof(sideHistory_copy)) \

U8 corners[8];
U8 edges[12];
int32_t moveTransformer[21];


void init_cube();

void reset_cube_history();

void make_move(int move);

void parse_alg(char *alg);

int is_cube_solved();
int full_is_repetition(int move);

void print_move(int move);
void print_cube();
U64 get_random_U64();

#endif //CFOPSOLVER_CUBE_H
