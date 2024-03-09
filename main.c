#include <stdio.h>
#include "cube.h"

int main() {
    Cube defaultCube;
    defaultCube.F[1][1] = BLUE;
    color front[3][3] = getFace(defaultCube, F);
    return 0;
}
