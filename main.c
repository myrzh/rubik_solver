#include <stdio.h>
#include "cube.h"

int main() {
    Cube defaultCube;
    char blueUserSide[] = {'b', 'g', 'y', 'y', 'g', 'b', 'r', 'b', 'b'};
    // color blueUserSide[] = {BLUE, GREEN, YELLOW, YELLOW, GREEN, BLUE, RED, BLUE, BLUE};
    fillSideFromArray(defaultCube.blueSide, blueUserSide);
    for (int i = 0; i < 9; i++) {
        printf("%u", colorNames[defaultCube.blueSide[i]]);
    }
    return 0;
}
