#include <stdio.h>
#include <string.h>
#include <stdint-gcc.h>
#include "cube.h"
#include "search.h"

int main() {
    init_cube();

    parse_alg("R U R' U'");
    print_cube();
    search_position();

    return 0;
}
