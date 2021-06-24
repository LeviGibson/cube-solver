//
// Created by levigibson on 6/21/21.
//

#include "search.h"
#include <string.h>
#include <stdio.h>

enum {eo_search, G1_search, solve_search};

int best_move;
int ply;
int search_type;

       //R, L, U, D, F, B, RP, LP, UP, DP, FP, BP, R2, L2, U2, D2, F2, B2
int move_restrictions[3][18] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        //{1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},
};

static inline int are_edges_oriented(){
    for (int edge = 0; edge < 12; edge++){
        if (get_piece_orientation(edges[edge]) == 1)
            return 0;
    }
    return 1;
}

static inline int are_corners_oriented(){
    for (int corner = 0; corner < 8; corner++){
        if (get_piece_orientation(corners[corner]) != 0)
            return 0;
    }
    return 1;
}

static inline int num_edges_oriented(){
    int num = 0;
    for (int corner = 0; corner < 8; corner++){
        if (get_piece_orientation(corners[corner]) == 0)
            num++;
    }
    return num;
}

int middle_layer_edges[4] = {4, 5, 6, 7};

static inline int is_domino_reduction(){

    for (int edge = 4; edge < 8; edge++){
        U8 ptype = get_piece_index(edges[edge]);
        if ((ptype < 4) || (ptype > 7)){
            return 0;
        }
    }

    if (are_edges_oriented()) {
        return are_corners_oriented();
    }
    return 0;
}

static inline int is_search_condition_met(){
    if (search_type == eo_search){
        return are_edges_oriented();
    }
    if (search_type == G1_search){
        return is_domino_reduction();
    }
    if (search_type == solve_search){
        return is_cube_solved();
    }
    return 0;
}

static inline int search(int depth, int alpha, line *pline){

    if (is_search_condition_met()){
        pline->length = 0;
        return(SOLVESCORE - ply);
    }

    if (depth == 0){
        return 0;
    }

    int eval;

    line node_line;
    node_line.length = 0;

    if (depth < 4 && depth > 1){
        if (num_edges_oriented() < 6){
            depth--;
        }
    }

    copy_cube();

    for (int move = R; move <= B2; move++){
        if (!is_repetition(move) & move_restrictions[search_type][move]) {
            make_move(move);
            ply++;
            eval = search(depth - 1, alpha, &node_line);
            ply--;
            if (eval > alpha) {
                alpha = eval;

                pline->moves[0] = move;
                memcpy(pline->moves + 1, node_line.moves, node_line.length * 4);
                pline->length = node_line.length + 1;

                if (ply == 0) {
                    best_move = move;
                }
            }

            paste_cube();
        }
    }
    return alpha;
}

void iterative_deepening(line *pv){
    for (int currentDepth = 0; currentDepth < 30; currentDepth++){
        printf("depth: %d\n", currentDepth);
        int eval = search(currentDepth, -1, pv);
        if (eval > 0){
            break;
        }
    }
    for (int move = 0; move < pv->length; move++) {
        make_move((int)pv->moves[move]);
        print_move((int)pv->moves[move]);
        printf(" ");
    }
}

void search_position(){
    ply = 0;

    line pv;
    pv.length = 0;

    //search_type = eo_search;
    //iterative_deepening(&pv);

    search_type = G1_search;
    iterative_deepening(&pv);

    search_type = solve_search;
    iterative_deepening(&pv);

    printf("\n");
}
