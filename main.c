#include <stdio.h>
#include <string.h>
#include <stdint-gcc.h>
#include "cube.h"
#include "search.h"
#include "easySolutions.h"

int main() {
    init_cube();

    parse_alg("F U2 L2 B2 F' U L2 U R2 D2 L' B L2 B' R2 U2");

    //parse_alg("R2 U R2 U' L2");
    reset_cube_history();

    search_position();

    return 0;
}
