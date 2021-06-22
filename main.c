#include <stdio.h>
#include <string.h>
#include <stdint-gcc.h>
#include "cube.h"
#include "search.h"

int main() {
    init_cube();

    parse_alg("U2 F2 D' U2 B2 L2 B2 F2 U F2 L B2 F' L2 D2 B2 U' B L2 U'");
    print_cube();
    search_position();

    return 0;
}
