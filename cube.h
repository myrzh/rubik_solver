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

void writeFaceToArray(color face[3][3], color cubeFace[3][3]) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            face[row][col] = cubeFace[row][col];
        }
    }
}

void printFaceFromArray(color face[3][3]) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            printf("%u ", face[row][col]);
        }
        printf("\n");
    }
}
