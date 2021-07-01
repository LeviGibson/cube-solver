//
// Created by levigibson on 6/21/21.
//

#include "search.h"
#include "easySolutions.h"
#include "easyDominoes.h"
#include <string.h>
#include <stdio.h>

enum {ed_search, dr_search, es_search, solve_search};

int ply;
int nodes;
int search_type;
int starting_time;
int time_limit;

       //R, L, U, D, F, B, RP, LP, UP, DP, FP, BP, R2, L2, U2, D2, F2, B2
int move_restrictions[4][18] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},

        //{1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},
        //{1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},

        {0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},
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

static inline int is_domino_reduction(){

    for (int edge = 4; edge < 8; edge++){
        U8 ptype = get_piece_index(edges[edge]);
        if ((ptype < 4) || (ptype > 7)){
            return 0;
        }
    }

    return are_corners_oriented();
}

int dominos_found;

static inline int is_search_condition_met(line *pv){
    if (search_type == ed_search){
        //return (cube_has_simple_domino()) ? (SOLVESCORE - ply) : 0;

        if (cube_has_simple_domino()) {
            search_type = dr_search;
            int score = iterative_deepening(pv, 0, 0);
            search_type = ed_search;
            return score;
        }
    }
    if (search_type == dr_search){
        //return (is_domino_reduction()) ? (SOLVESCORE - ply) : 0;
        if (is_domino_reduction()) {
            search_type = es_search;
            int score = iterative_deepening(pv, 0, 0);

            search_type = dr_search;
            return score;
        }
    }
    if (search_type == solve_search){
        return (is_cube_solved()) ? (ply) : 0;
    }
    if (search_type == es_search){
        //return (cube_has_simple_solution()) ? (SOLVESCORE - ply) : 0;
        if (cube_has_simple_solution()) {
            search_type = solve_search;
            int score = iterative_deepening(pv, 0, 0);
            search_type = es_search;
            return score;
        }
    }
    return 0;
}

int best_so_far = 0;

static inline int search(int depth, int alpha, line *pline){

    if ((nodes % 4096) == 0) {
        if ((get_time_ms() - starting_time) >= time_limit) {
            return alpha;
        }
    }
    nodes++;

    if ((search_type == es_search) && ((ply > 16) || (ply > (best_so_far - 9)))){
        return FAIL_LOW;
    }

    if (depth == 0){
        int search_condition_met = is_search_condition_met(pline);
        if (search_condition_met == FAIL_LOW){
            if (search_type == ed_search) {
                return SOLVESCORE;
            } else {
                return FAIL_LOW;
            }
        }
        if (search_condition_met){
            pline->length[search_type] = 0;
            return(search_condition_met);
        }
        return SOLVESCORE;
    }

    int eval;

    line node_line;
    memset(&node_line.length, 0, sizeof node_line.length);

    copy_cube();

    for (int move = R; move <= B2; move++){
        if (!(is_repetition(move)) && move_restrictions[search_type][move]) {
            make_move(move);
            ply++;
            eval = search(depth - 1, alpha, &node_line);
            ply--;
            paste_cube();
            if (eval < alpha) {
                alpha = eval;

                pline->moves[search_type][0] = move;
                memcpy(pline->moves[search_type] + 1, node_line.moves[search_type], node_line.length[search_type] * 4);
                pline->length[search_type] = (node_line.length[search_type]) + 1;

                for (int type = search_type+1; type <= solve_search; type++){
                    memcpy(pline->moves[type], node_line.moves[type], sizeof node_line.moves[type]);
                    pline->length[type] = node_line.length[type];
                }

                if ((search_type == dr_search) || (search_type == solve_search) || (search_type == es_search))
                    return eval;
                //return eval;

                if (eval < best_so_far){
                    printf("%d\n", eval);
                    best_so_far = eval;
                }
            }
        }
    }
    return alpha;
}

int iterative_deepening(line *pv, int io, int make_moves){
    int eval = SOLVESCORE;
    for (int currentDepth = 0; currentDepth < 30; currentDepth++){
        if (io)
            printf("depth: %d\n", currentDepth);

        eval = search(currentDepth, eval, pv);

        if (eval == FAIL_LOW){
            return FAIL_LOW;
        }
        if (eval < SOLVESCORE && (search_type != ed_search)){
            break;
        }
    }
    for (int move = 0; move < pv->length[search_type]; move++) {
        if (make_moves)
            make_move((int)pv->moves[search_type][move]);

        if (io) {
            print_move((int) pv->moves[search_type][move]);
            printf(" ");
        }
    }
    if (io) {
        printf("\n");
    }
    return eval;
}

int search_position(int io){
    ply = 0;
    nodes = 0;
    dominos_found = 0;

    starting_time = get_time_ms();
    time_limit = 10000;

    best_so_far = SOLVESCORE;

    line pv;
    memset(&pv.length, 0, sizeof pv.length);

    search_type = ed_search;
    iterative_deepening(&pv, io, 1);

    printf("nodes: %d\n", nodes);
    printf("Solved in %d Moves!\n", pv.length[0] + pv.length[1] + pv.length[2] + pv.length[3]);

    for (int step = 0; step < 4; step++) {
        for (int moveId = 0; moveId < pv.length[step]; moveId++){
            print_move(pv.moves[step][moveId]);
            printf(" ");
        }
    }

    return 0;
}
