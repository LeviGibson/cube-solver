#include <stdio.h>
#include <string.h>
#include <stdint-gcc.h>
#include "cube.h"
#include "search.h"
#include "easySolutions.h"

int main() {
    init_cube();

    parse_alg("B R2 U2 L2 F D2 B' U2 L2 B' R2 L' B' F U' L' D L R' D2 U2");

    reset_cube_history();

    search_position(0);

    return 0;
}
