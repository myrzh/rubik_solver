#include <stdio.h>

typedef enum {WHITE, YELLOW, RED, BLUE, GREEN, ORANGE} color;
typedef enum {F, S, B, U, E, D, R, M, L} layer;
// typedef enum {F, U, R, B, D, L} face;

typedef struct {
    color F[3][3];
    color U[3][3];
    color R[3][3];
    color B[3][3];
    color D[3][3];
    color L[3][3];
} Cube;

color *getFace(Cube thisCube, layer thisFaceName) {
    color face[3][3];

    switch (thisFaceName) {
    case F:
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                face[row][col] = thisCube.F[row][col];
            }
        }
        break;
    case U:
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                face[row][col] = thisCube.U[row][col];
            }
        }
        break;
    case R:
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                face[row][col] = thisCube.R[row][col];
            }
        }
        break;
    case B:
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                face[row][col] = thisCube.B[row][col];
            }
        }
    case D:
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                face[row][col] = thisCube.D[row][col];
            }
        }
        break;
    case L:
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                face[row][col] = thisCube.L[row][col];
            }
        }
        break;
    default:
        printf("NOT A FACE\n");
        break;
    }

    return face;
}

void printFace(Cube thisCube, layer thisFaceName) {
    return;
}
