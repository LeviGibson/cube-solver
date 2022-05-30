//
// Created by levigibson on 6/18/21.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cube.h"
#include "easySolutions.h"

U8 corners[8];
U8 edges[12];
int32_t moveTransformer[21] = {R, L, U, D, F, B, RP, LP, UP, DP, FP, BP, R2, L2, U2, D2, F2, B2, M, MP, M2};
int8_t moveToAxis[21] = {AXIS_M, AXIS_M, AXIS_E, AXIS_E, AXIS_S, AXIS_S, AXIS_M, AXIS_M, AXIS_E, AXIS_E, AXIS_S, AXIS_S,
                       AXIS_M, AXIS_M, AXIS_E, AXIS_E, AXIS_S, AXIS_S, AXIS_M, AXIS_M, AXIS_M};
int8_t moveToSide[21] = {SIDE_R, SIDE_L, SIDE_U, SIDE_D, SIDE_F, SIDE_B, SIDE_R, SIDE_L, SIDE_U, SIDE_D, SIDE_F, SIDE_B, SIDE_R, SIDE_L, SIDE_U, SIDE_D, SIDE_F, SIDE_B};
int8_t axisHistory[3] = {0, 0, 0};
int8_t sideHistory[6] = {0, 0, 0, 0, 0, 0};

char corner_colors[8][3] = {
        {'Y', 'R', 'G'},
        {'Y', 'B', 'R'},
        {'Y', 'O', 'B'},
        {'Y', 'G', 'O'},

        {'W', 'O', 'G'},
        {'W', 'B', 'O'},
        {'W', 'R', 'B'},
        {'W', 'G', 'R'},
};

char edge_colors[12][2] = {
        {'Y', 'R'},
        {'Y', 'B'},
        {'Y', 'O'},
        {'Y', 'G'},
        {'O', 'G'},
        {'O', 'B'},
        {'R', 'B'},
        {'R', 'G'},
        {'W', 'O'},
        {'W', 'B'},
        {'W', 'R'},
        {'W', 'G'},
};

const char *move_chars[] = {
        "R ",
        "L ",
        "U ",
        "D ",
        "F ",
        "B ",
        "R'",
        "L'",
        "U'",
        "D'",
        "F'",
        "B'",
        "R2",
        "L2",
        "U2",
        "D2",
        "F2",
        "B2",
        "M",
        "M'",
        "M2"
};

U8 corner_twists[64][2];

int corner_orientaion_adjustments[18][4] = {
        {2, 6, 5, 1},
        {0, 4, 3, 7},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {3, 5, 2, 4},
        {1, 7, 0, 6},

        {2, 6, 5, 1},
        {0, 4, 3, 7},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {3, 5, 2, 4},
        {1, 7, 0, 6},

        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
};

//The first number represents weather it is a double move
int corner_cycles[18][5] = {
        {0, 1, 2, 5, 6},
        {0, 7, 4, 3, 0},
        {0, 0, 3, 2, 1},
        {0, 4, 7, 6, 5},
        {0, 2, 3, 4, 5},
        {0, 0, 1, 6, 7},

        {0, 6, 5, 2, 1},
        {0, 0, 3, 4, 7},
        {0, 1, 2, 3, 0},
        {0, 5, 6, 7, 4},
        {0, 5, 4, 3, 2},
        {0, 7, 6, 1, 0},

        {1, 1, 5, 2, 6},
        {1, 0, 4, 3, 7},
        {1, 0, 2, 1, 3},
        {1, 4, 6, 5, 7},
        {1, 3, 5, 2, 4},
        {1, 0, 6, 1, 7},
};

int edge_orientation_adjustments[18][4] = {
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        //F
        {2, 4, 8, 5},
        //B
        {0, 6, 10, 7},

        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        //FP
        {2, 4, 8, 5},
        //BP
        {0, 6, 10, 7},

        //double moves
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
};

//reference. Declared in cube.h
//enum{R, L, U, D, F, B, RP, LP, UP, DP, FP, BB, R2, L2, U2, D2, F2, B2};

int edge_cycles[18][5] = {
        {0, 1, 5, 9, 6},
        {0, 3, 7, 11, 4},
        {0, 0, 3, 2, 1},
        {0, 8, 11, 10, 9},
        {0, 2, 4, 8, 5},
        {0, 0, 6, 10, 7},

        {0, 6, 9, 5, 1},
        {0, 4, 11, 7, 3},
        {0, 1, 2, 3, 0},
        {0, 9, 10, 11, 8},
        {0, 5, 8, 4, 2},
        {0, 7, 10, 6, 0},

        {-1, 1, 9, 5, 6},
        {-1, 3, 11, 7, 4},
        {-1, 0, 2, 1, 3},
        {-1, 8, 10, 9, 11},
        {-1, 2, 8, 4, 5},
        {-1, 0, 10, 6, 7},
};


void reset_cube_history(){
    memset(axisHistory, 0, sizeof(axisHistory));
    memset(sideHistory, 0, sizeof(sideHistory));
}

void parse_alg(char *alg){
    while (*alg){
        if (*alg == 'R'){

            if (*(alg+1) == '\'')
                make_move(RP);
            else if (*(alg+1) == '2')
                make_move(R2);
            else
                make_move(R);

        } else if (*alg == 'U'){

            if (*(alg+1) == '\'')
                make_move(UP);
            else if (*(alg+1) == '2')
                make_move(U2);
            else
                make_move(U);

        } else if (*alg == 'F'){

            if (*(alg+1) == '\'')
                make_move(FP);
            else if (*(alg+1) == '2')
                make_move(F2);
            else
                make_move(F);

        } else if (*alg == 'L'){

            if (*(alg+1) == '\'')
                make_move(LP);
            else if (*(alg+1) == '2')
                make_move(L2);
            else
                make_move(L);

        } else if (*alg == 'D'){

            if (*(alg+1) == '\'')
                make_move(DP);
            else if (*(alg+1) == '2')
                make_move(D2);
            else
                make_move(D);

        } else if (*alg == 'B'){

            if (*(alg+1) == '\'')
                make_move(BP);
            else if (*(alg+1) == '2')
                make_move(B2);
            else
                make_move(B);

        }

        alg++;
    }
}

void swap(int *x, int *y){
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

void update_rotation(int move){
    if (move == XP){
        swap(&moveTransformer[U], &moveTransformer[F]);
        swap(&moveTransformer[UP], &moveTransformer[FP]);
        swap(&moveTransformer[U2], &moveTransformer[F2]);

        swap(&moveTransformer[U], &moveTransformer[D]);
        swap(&moveTransformer[UP], &moveTransformer[DP]);
        swap(&moveTransformer[U2], &moveTransformer[D2]);

        swap(&moveTransformer[U], &moveTransformer[B]);
        swap(&moveTransformer[UP], &moveTransformer[BP]);
        swap(&moveTransformer[U2], &moveTransformer[B2]);
    }
    if (move == X){
        update_rotation(XP);
        update_rotation(XP);
        update_rotation(XP);
    }
    if (move == X2){
        update_rotation(XP);
        update_rotation(XP);
    }
}

void make_move(int move){
    move = moveTransformer[move];

    if (move == M){
        make_move(R);
        make_move(LP);
        update_rotation(XP);
        return;
    }
    if (move == MP){
        make_move(RP);
        make_move(L);
        update_rotation(X);
        return;
    }
    if (move == M2){
        make_move(R2);
        make_move(L2);
        update_rotation(X2);
        return;
    }

    U8 corner_buffer[8];
    memcpy(corner_buffer, corners, sizeof corner_buffer);

    //Rotating Corners, ignoring moves like U, D, and R2
    if (corner_orientaion_adjustments[move][0] != -1) {
        increment_corner_orientation(corner_buffer[corner_orientaion_adjustments[move][0]]);
        increment_corner_orientation(corner_buffer[corner_orientaion_adjustments[move][1]]);
        decrement_corner_orientation(corner_buffer[corner_orientaion_adjustments[move][2]]);
        decrement_corner_orientation(corner_buffer[corner_orientaion_adjustments[move][3]]);
    }
    if (corner_cycles[move][0] == 0) {
        corners[corner_cycles[move][1]] = corner_buffer[corner_cycles[move][2]];
        corners[corner_cycles[move][2]] = corner_buffer[corner_cycles[move][3]];
        corners[corner_cycles[move][3]] = corner_buffer[corner_cycles[move][4]];
        corners[corner_cycles[move][4]] = corner_buffer[corner_cycles[move][1]];
    } else {
        corners[corner_cycles[move][2]] = corner_buffer[corner_cycles[move][1]];
        corners[corner_cycles[move][1]] = corner_buffer[corner_cycles[move][2]];
        corners[corner_cycles[move][3]] = corner_buffer[corner_cycles[move][4]];
        corners[corner_cycles[move][4]] = corner_buffer[corner_cycles[move][3]];
    }

    U8 edge_buffer[12];
    memcpy(edge_buffer, edges, sizeof edge_buffer);

    if (edge_orientation_adjustments[move][0] != -1){
        flip_edge(edge_buffer[edge_orientation_adjustments[move][0]]);
        flip_edge(edge_buffer[edge_orientation_adjustments[move][1]]);
        flip_edge(edge_buffer[edge_orientation_adjustments[move][2]]);
        flip_edge(edge_buffer[edge_orientation_adjustments[move][3]]);
    }

    if (edge_cycles[move][0] == 0) {
        edges[edge_cycles[move][1]] = edge_buffer[edge_cycles[move][2]];
        edges[edge_cycles[move][2]] = edge_buffer[edge_cycles[move][3]];
        edges[edge_cycles[move][3]] = edge_buffer[edge_cycles[move][4]];
        edges[edge_cycles[move][4]] = edge_buffer[edge_cycles[move][1]];
    } else {
        edges[edge_cycles[move][1]] = edge_buffer[edge_cycles[move][2]];
        edges[edge_cycles[move][2]] = edge_buffer[edge_cycles[move][1]];

        edges[edge_cycles[move][3]] = edge_buffer[edge_cycles[move][4]];
        edges[edge_cycles[move][4]] = edge_buffer[edge_cycles[move][3]];
    }

    if (!axisHistory[moveToAxis[move]])
        reset_cube_history();
    axisHistory[moveToAxis[move]]++;
    sideHistory[moveToSide[move]]++;
}

int is_cube_solved(){

    for (int edgeID = 0; edgeID < 12; edgeID++){
        if (edgeID != get_piece_index(edges[edgeID])){
            return 0;
        }
        if (get_piece_orientation(edges[edgeID]) != 0){
            return 0;
        }
    }
    for (int cornerID = 0; cornerID < 8; cornerID++){
        if (cornerID != get_piece_index(corners[cornerID])){
            return 0;
        }
        if (get_piece_orientation(corners[cornerID]) != 0){
            return 0;
        }
    }

    return 1;
}

void generate_corner_twists(){
    for (U8 i = 0; i < 64; i++){
        corner_twists[i][1] = increment_corner_orientation_otf(i);
        corner_twists[i][0] = decrement_corner_orientation_otf(i);
    }
}

void print_move(int move){
    if (move_chars[move][1] == ' ')
        printf("%c", move_chars[move][0]);
    else
        printf("%s", move_chars[move]);
}

void print_cube(){

    char compiled_corner_colors[24];
    char compiled_edge_colors[24];

    for (int colorID = 0; colorID < 24; colorID++){
        compiled_corner_colors[colorID] = '0';
        compiled_edge_colors[colorID] = '0';
    }

    for (int cornerId = 0; cornerId < 8; cornerId++){
        U8 corner = corners[cornerId];
        for (int colorID = 0; colorID < 3; colorID++){
            compiled_corner_colors[((cornerId) * 3) + colorID] = corner_colors[get_piece_index(corner)][(((int)get_piece_orientation(corner)) + colorID) % 3];
        }
    }

    for (int edgeId = 0; edgeId < 12; edgeId++){
        U8 edge = edges[edgeId];
        for (int colorId = 0; colorId < 2; colorId++){
            compiled_edge_colors[(edgeId*2)+colorId] = edge_colors[get_piece_index(edge)][(((int)get_piece_orientation(edge)) + colorId) % 2];
        }
    }

    printf("\n");

    printf("         %c  %c  %c\n", compiled_corner_colors[0], compiled_edge_colors[0], compiled_corner_colors[3]);
    printf("         %c  Y  %c\n", compiled_edge_colors[6], compiled_edge_colors[2]);
    printf("         %c  %c  %c\n", compiled_corner_colors[9], compiled_edge_colors[4], compiled_corner_colors[6]);
    printf("%c  %c  %c  %c  %c  %c  %c  %c  %c  %c  %c  %c\n", compiled_corner_colors[2], compiled_edge_colors[7], compiled_corner_colors[10], compiled_corner_colors[11], compiled_edge_colors[5], compiled_corner_colors[7], compiled_corner_colors[8], compiled_edge_colors[3], compiled_corner_colors[4], compiled_corner_colors[5], compiled_edge_colors[1], compiled_corner_colors[1]);
    printf("%c  G  %c  %c  O  %c  %c  B  %c  %c  R  %c\n", compiled_edge_colors[15], compiled_edge_colors[9], compiled_edge_colors[8], compiled_edge_colors[10], compiled_edge_colors[11], compiled_edge_colors[13], compiled_edge_colors[12], compiled_edge_colors[14]);
    printf("%c  %c  %c  %c  %c  %c  %c  %c  %c  %c  %c  %c\n", compiled_corner_colors[22], compiled_edge_colors[23], compiled_corner_colors[14], compiled_corner_colors[13], compiled_edge_colors[17], compiled_corner_colors[17], compiled_corner_colors[16], compiled_edge_colors[19], compiled_corner_colors[20], compiled_corner_colors[19], compiled_edge_colors[21], compiled_corner_colors[23]);
    printf("         %c  %c  %c\n", compiled_corner_colors[12], compiled_edge_colors[16], compiled_corner_colors[15]);
    printf("         %c  W  %c\n", compiled_edge_colors[22], compiled_edge_colors[18]);
    printf("         %c  %c  %c\n\n", compiled_corner_colors[21], compiled_edge_colors[20], compiled_corner_colors[18]);

}

void init_cube(){
    for (int i = 0; i < 8; i++){
        corners[i] = encode_piece(i, 0);
    }
    for (int i = 0; i < 12; i++){
        edges[i] = encode_piece(i, 0);
    }

    generate_corner_twists();
    init_key_generator();
//    init_easy_dominos();
}

U64 get_random_U64(){
    U64 rando = 0ULL;
    rando |= (U64)rand();
    rando |= ((U64)rand() << 32);
    return rando;
}

int full_is_repetition(int move) {
    if (move == M || move == MP || move == M2){
        if (sideHistory[SIDE_L] || sideHistory[SIDE_R])
            return 1;
    } else if (sideHistory[moveToSide[move]])
        return 1;

    return 0;
}

