//
// Created by levigibson on 6/25/21.
//

#ifndef CUBE_SOLVER_EASYSOLUTIONS_H
#define CUBE_SOLVER_EASYSOLUTIONS_H

#include "cube.h"
void init_key_generator();
void init_easy_solutions();

int cube_has_simple_solution();
U64 get_cube_key();

void print_U64_binary(U64 number);

#endif //CUBE_SOLVER_EASYSOLUTIONS_H
