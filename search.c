//
// Created by levigibson on 6/21/21.
//

#include "search.h"
#include <string.h>
#include <stdio.h>

int best_move;
int ply;

static inline int evaluate(){
    int eval = 0;
    for (int edgeID = 0; edgeID < 12; edgeID++){
        if (get_piece_orientation(edges[edgeID]) == 0){
            eval += 4;
            if (edgeID == get_piece_index(edges[edgeID])){
                eval += 4;
            }
        }
    }
    for (int cornerID = 0; cornerID < 8; cornerID++){
        if (get_piece_orientation(corners[cornerID]) == 0){
            eval += 2;
            if (cornerID == get_piece_index(corners[cornerID])){
                eval += 3;
            }
        }
    }

    return eval;
}

static inline int search(int depth, int alpha, line *pline){
    if (is_cube_solved()){
        pline->length = 0;
        return(SOLVESCORE - ply);
    }

    if (depth == 0){
        return evaluate();
    }

    int eval;

    line node_line;
    node_line.length = 0;

    copy_cube();

    for (int move = R; move <= B2; move++){
        if (!is_repetition(move)) {
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

void search_position(){
    printf("yes\n");
    while (!is_cube_solved()) {
        ply = 0;

        line pv;
        pv.length = 0;

        int eval = search(7, -1, &pv);

        for (int move = 0; move < pv.length; move++) {
            print_move((int)pv.moves[move]);
            printf(" ");
        }

        print_move((int) pv.moves[0]);
        make_move((int) pv.moves[0]);
        printf("\n");

    }
    printf("\n");
    print_cube();
}
