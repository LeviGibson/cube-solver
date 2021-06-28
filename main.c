#include <stdio.h>
#include <string.h>
#include <stdint-gcc.h>
#include "cube.h"
#include "search.h"
#include "easySolutions.h"
#include "easyDominoes.h"

char* testScrambles[10][100] = {
        "L' F' B2 U2 B' D' L' B R2 B2 D F2 L2 U L2 U2 D R",
        "R2 F D' R' D L F' U2 D2 F2 D2 L B2 L2 F2 L' U2 L2 F'",
        "U2 F' D F2 R2 B L R2 U' F2 B2 R2 D F2 B2 D L2 B2 L B R",
        "D B' R2 U2 R' F L D' F' R2 D2 L2 D2 R2 B D2 F' R2 F' B'",
        "B D2 B2 R2 D2 B U2 F' U2 B2 R2 B R F2 D' F2 U B D2 L D",
        "R2 F' L2 U2 B2 D' R2 F2 D L2 B2 R2 U' R' F' L' B2 D' R'",
        "U B D' R2 U2 R2 F2 U' R2 U B2 D2 B' L2 D2 R' U' L' D2 U",
        "B D F' L2 B' R' U D2 F L2 D2 B U2 L2 F2 R2 D2 B' R D",
        "R' B2 D' L2 R2 F2 U' B2 D' L2 R2 B' D F2 D U2 F' L' B R'",
        "L' D' B L2 U' R2 L B2 U' B2 L2 U' R2 D F2 U2 B2 F R2"
};

int main() {
    init_cube();

    parse_alg("L' F' B2 U2 B' D' L' B R2 B2 D F2 L2 U L2 U2 D R");
    reset_cube_history();
    search_position(1);

    return 0;
}
