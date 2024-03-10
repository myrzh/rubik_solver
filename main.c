#include <stdio.h>
#include "cube.h"

int main() {
    Cube defaultCube;
    defaultCube.F[1][2] = BLUE;
    color front[3][3];
    writeFaceToArray(front, defaultCube.F);
    printFaceFromArray(front);
    return 0;
}
