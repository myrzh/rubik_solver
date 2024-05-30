#ifndef CUBE_H
#define CUBE_H

#include <stdio.h>
#include <string.h>
#include "colors.h"

#define CORNERFACE 1
#define CORNERWHITE 2
#define CORNERPREV 3

typedef enum { R, _R, G, _G, B, _B, W, _W, O, _O, Y, _Y } action;

typedef enum { STRAIGHT, BACK } rotationMode;

typedef enum { LEVEL_ONE, LEVEL_TWO, LEVEL_THREE } flatCubeLevel;

action getActionFromChar(char letter) {
    switch (letter) {
        case 'R':
            return R;
        case 'G':
            return G;
        case 'B':
            return B;
        case 'W':
            return W;
        case 'O':
            return O;
        case 'Y':
            return Y;
        default:
            return 0;
            break;
    }
}

void getTextFromAction(char text[], action act) {
    // memset(text, 0, 20);
    int backFactor = 0;
    if (act % 2 == 1) {
        backFactor = 1;
    }
    switch (act - backFactor) {
        case R:
            strcpy(text, "ROTATE RED");
            break;
        case G:
            strcpy(text, "ROTATE GREEN");
            break;
        case B:
            strcpy(text, "ROTATE BLUE");
            break;
        case W:
            strcpy(text, "ROTATE WHITE");
            break;
        case O:
            strcpy(text, "ROTATE ORANGE");
            break;
        case Y:
            strcpy(text, "ROTATE YELLOW");
            break;
        default:
            break;
    }
    if (backFactor == 1) {
        strcat(text, " BACK");
    }
}

void swap(color* x, color* y) {
    color t;
    t = (*x);
    (*x) = (*y);
    (*y) = t;
}

typedef struct {
    color whiteSide[9];
    color yellowSide[9];
    color redSide[9];
    color blueSide[9];
    color greenSide[9];
    color orangeSide[9];
} Cube;

void initCube(Cube* thisCube) {
    for (int index = 0; index < 9; index++) {
        thisCube->whiteSide[index] = WHITE;
        thisCube->yellowSide[index] = YELLOW;
        thisCube->redSide[index] = RED;
        thisCube->blueSide[index] = BLUE;
        thisCube->greenSide[index] = GREEN;
        thisCube->orangeSide[index] = ORANGE;
    }
}

void initFlatCube(Cube* thisCube) {
    for (int index = 0; index < 8; index++) {
        thisCube->whiteSide[index] = CYAN;
        thisCube->yellowSide[index] = CYAN;
        thisCube->redSide[index] = CYAN;
        thisCube->blueSide[index] = CYAN;
        thisCube->greenSide[index] = CYAN;
        thisCube->orangeSide[index] = CYAN;
    }
    thisCube->whiteSide[8] = WHITE;
    thisCube->yellowSide[8] = YELLOW;
    thisCube->redSide[8] = RED;
    thisCube->blueSide[8] = BLUE;
    thisCube->greenSide[8] = GREEN;
    thisCube->orangeSide[8] = ORANGE;
}

void fillSideFromArray(color* cubeSide, char sideColors[]) {
    for (int index = 0; index < 9; index++) {
        switch (sideColors[index]) {
        case 'w':
            cubeSide[index] = WHITE;
            break;
        case 'y':
            cubeSide[index] = YELLOW;
            break;
        case 'r':
            cubeSide[index] = RED;
            break;
        case 'b':
            cubeSide[index] = BLUE;
            break;
        case 'g':
            cubeSide[index] = GREEN;
            break;
        case 'o':
            cubeSide[index] = ORANGE;
            break;
        default:
            break;
        }
    }
}

void rotateSideBy90(Cube* thisCube, color sideToRotate, rotationMode mode) {
    int count = 1;
    if (mode == BACK) {
        count += 2;
    }

    int isPrinted = 0;

    for (int i = 0; i < count; i++) {
        switch (sideToRotate) {
        case WHITE:
            if (!isPrinted) {
                printf("ROTATE WHITE");
            }
            swap(&thisCube->whiteSide[7], &thisCube->whiteSide[3]);
            swap(&thisCube->whiteSide[6], &thisCube->whiteSide[4]);
            swap(&thisCube->whiteSide[0], &thisCube->whiteSide[2]);
            swap(&thisCube->whiteSide[7], &thisCube->whiteSide[5]);
            swap(&thisCube->whiteSide[0], &thisCube->whiteSide[4]);
            swap(&thisCube->whiteSide[1], &thisCube->whiteSide[3]);

            swap(&thisCube->blueSide[0], &thisCube->orangeSide[0]);
            swap(&thisCube->blueSide[7], &thisCube->orangeSide[7]);
            swap(&thisCube->blueSide[6], &thisCube->orangeSide[6]);

            swap(&thisCube->orangeSide[6], &thisCube->greenSide[6]);
            swap(&thisCube->orangeSide[7], &thisCube->greenSide[7]);
            swap(&thisCube->orangeSide[0], &thisCube->greenSide[0]);

            swap(&thisCube->greenSide[6], &thisCube->redSide[6]);
            swap(&thisCube->greenSide[7], &thisCube->redSide[7]);
            swap(&thisCube->greenSide[0], &thisCube->redSide[0]);
            break;
        case YELLOW:
            if (!isPrinted) {
                printf("ROTATE YELLOW");
            }
            swap(&thisCube->yellowSide[7], &thisCube->yellowSide[3]);
            swap(&thisCube->yellowSide[6], &thisCube->yellowSide[4]);
            swap(&thisCube->yellowSide[0], &thisCube->yellowSide[2]);
            swap(&thisCube->yellowSide[7], &thisCube->yellowSide[5]);
            swap(&thisCube->yellowSide[0], &thisCube->yellowSide[4]);
            swap(&thisCube->yellowSide[1], &thisCube->yellowSide[3]);

            swap(&thisCube->blueSide[4], &thisCube->redSide[4]);
            swap(&thisCube->blueSide[3], &thisCube->redSide[3]);
            swap(&thisCube->blueSide[2], &thisCube->redSide[2]);

            swap(&thisCube->redSide[2], &thisCube->greenSide[2]);
            swap(&thisCube->redSide[3], &thisCube->greenSide[3]);
            swap(&thisCube->redSide[4], &thisCube->greenSide[4]);

            swap(&thisCube->greenSide[4], &thisCube->orangeSide[4]);
            swap(&thisCube->greenSide[3], &thisCube->orangeSide[3]);
            swap(&thisCube->greenSide[2], &thisCube->orangeSide[2]);
            break;
        case RED:
            if (!isPrinted) {
                printf("ROTATE RED");
            }
            swap(&thisCube->redSide[0], &thisCube->redSide[4]);
            swap(&thisCube->redSide[7], &thisCube->redSide[5]);
            swap(&thisCube->redSide[1], &thisCube->redSide[3]);
            swap(&thisCube->redSide[0], &thisCube->redSide[6]);
            swap(&thisCube->redSide[1], &thisCube->redSide[5]);
            swap(&thisCube->redSide[2], &thisCube->redSide[4]);

            swap(&thisCube->blueSide[6], &thisCube->whiteSide[3]);
            swap(&thisCube->blueSide[5], &thisCube->whiteSide[2]);
            swap(&thisCube->blueSide[4], &thisCube->whiteSide[1]);

            swap(&thisCube->whiteSide[1], &thisCube->greenSide[0]);
            swap(&thisCube->whiteSide[2], &thisCube->greenSide[1]);
            swap(&thisCube->whiteSide[3], &thisCube->greenSide[2]);

            swap(&thisCube->greenSide[0], &thisCube->yellowSide[3]);
            swap(&thisCube->greenSide[1], &thisCube->yellowSide[2]);
            swap(&thisCube->greenSide[2], &thisCube->yellowSide[1]);
            break;
        case BLUE:
            if (!isPrinted) {
                printf("ROTATE BLUE");
            }
            swap(&thisCube->blueSide[1], &thisCube->blueSide[7]);
            swap(&thisCube->blueSide[2], &thisCube->blueSide[6]);
            swap(&thisCube->blueSide[5], &thisCube->blueSide[3]);
            swap(&thisCube->blueSide[2], &thisCube->blueSide[0]);
            swap(&thisCube->blueSide[7], &thisCube->blueSide[3]);
            swap(&thisCube->blueSide[6], &thisCube->blueSide[4]);

            swap(&thisCube->yellowSide[1], &thisCube->orangeSide[4]);
            swap(&thisCube->yellowSide[0], &thisCube->orangeSide[5]);
            swap(&thisCube->yellowSide[7], &thisCube->orangeSide[6]);

            swap(&thisCube->whiteSide[7], &thisCube->orangeSide[4]);
            swap(&thisCube->whiteSide[0], &thisCube->orangeSide[5]);
            swap(&thisCube->whiteSide[1], &thisCube->orangeSide[6]);

            swap(&thisCube->whiteSide[7], &thisCube->redSide[0]);
            swap(&thisCube->whiteSide[0], &thisCube->redSide[1]);
            swap(&thisCube->whiteSide[1], &thisCube->redSide[2]);
            break;
        case GREEN:
            if (!isPrinted) {
                printf("ROTATE GREEN");
            }
            swap(&thisCube->greenSide[6], &thisCube->greenSide[2]);
            swap(&thisCube->greenSide[5], &thisCube->greenSide[3]);
            swap(&thisCube->greenSide[7], &thisCube->greenSide[1]);
            swap(&thisCube->greenSide[4], &thisCube->greenSide[6]);
            swap(&thisCube->greenSide[7], &thisCube->greenSide[3]);
            swap(&thisCube->greenSide[0], &thisCube->greenSide[2]);

            swap(&thisCube->whiteSide[5], &thisCube->orangeSide[2]);
            swap(&thisCube->whiteSide[4], &thisCube->orangeSide[1]);
            swap(&thisCube->whiteSide[3], &thisCube->orangeSide[0]);

            swap(&thisCube->yellowSide[3], &thisCube->orangeSide[2]);
            swap(&thisCube->yellowSide[4], &thisCube->orangeSide[1]);
            swap(&thisCube->yellowSide[5], &thisCube->orangeSide[0]);

            swap(&thisCube->yellowSide[3], &thisCube->redSide[6]);
            swap(&thisCube->yellowSide[4], &thisCube->redSide[5]);
            swap(&thisCube->yellowSide[5], &thisCube->redSide[4]);
            break;
        case ORANGE:
            if (!isPrinted) {
                printf("ROTATE ORANGE");
            }
            swap(&thisCube->orangeSide[4], &thisCube->orangeSide[0]);
            swap(&thisCube->orangeSide[3], &thisCube->orangeSide[1]);
            swap(&thisCube->orangeSide[5], &thisCube->orangeSide[7]);
            swap(&thisCube->orangeSide[4], &thisCube->orangeSide[2]);
            swap(&thisCube->orangeSide[5], &thisCube->orangeSide[1]);
            swap(&thisCube->orangeSide[6], &thisCube->orangeSide[0]);

            swap(&thisCube->blueSide[2], &thisCube->yellowSide[5]);
            swap(&thisCube->blueSide[1], &thisCube->yellowSide[6]);
            swap(&thisCube->blueSide[0], &thisCube->yellowSide[7]);

            swap(&thisCube->yellowSide[5], &thisCube->greenSide[6]);
            swap(&thisCube->yellowSide[6], &thisCube->greenSide[5]);
            swap(&thisCube->yellowSide[7], &thisCube->greenSide[4]);

            swap(&thisCube->greenSide[6], &thisCube->whiteSide[7]);
            swap(&thisCube->greenSide[5], &thisCube->whiteSide[6]);
            swap(&thisCube->greenSide[4], &thisCube->whiteSide[5]);
            break;
        default:
            break;
        }
        isPrinted = 1;
    }

    if (mode == BACK) {
        printf(" BACK");
    }
    printf("\n");
}

#endif
