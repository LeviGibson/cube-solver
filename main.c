#include "cube.h"
#include "search.h"
#include "easySolutions.h"
#include <stdio.h>

int main() {
    init_cube();
    init_easy_solutions();

    parse_alg("R U R' U' R' F R2 U' R' U' R U R' F' ");
    print_cube();
    reset_cube_history();
    search_position();

    return 0;
}
