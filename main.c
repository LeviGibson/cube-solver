#include <stdio.h>
#include <string.h>
#include <stdint-gcc.h>
#include "cube.h"
#include "search.h"

int main() {
    init_cube();

    parse_alg("R U R' U' R' F R2 U' R' U' R U R' F'");
    print_cube();
    reset_cube_history();
    search_position();

    return 0;
}
