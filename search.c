//
// Created by levigibson on 6/21/21.
//

#include "search.h"
#include <string.h>
#include <stdio.h>

int best_move;
int ply;

static inline int search(int depth){
    if (is_cube_solved()){
        return(SOLVESCORE - ply);
    }

    if (depth == 0){
        return 0;
    }

    int eval;
    int maxEval = -1;

    copy_cube();

    for (int move = R; move <= B2; move++){

        make_move(move);
        ply++;
        eval = search(depth-1);
        ply--;
        if (eval > maxEval){
            maxEval = eval;



            if (ply == 0){
                best_move = move;
            }
        }

        paste_cube();
    }

    return maxEval;

}

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
        "B2"
};

void search_position(){
    ply = 0;

    int eval = search(6);

    printf("%d\n", eval);
    printf("%s\n", move_chars[best_move]);
}
