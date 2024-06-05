#ifndef CUBE_H
#define CUBE_H

#include <stdio.h>
#include <string.h>
#include "colors.h"
#include "algo.h"

#define CORNERFACE 1
#define CORNERWHITE 2
#define CORNERPREV 3

typedef enum { R, _R, G, _G, B, _B, W, _W, O, _O, Y, _Y } action;

typedef enum { STRAIGHT, BACK } rotationMode;

typedef enum { LEVEL_ONE, LEVEL_TWO, LEVEL_THREE } flatCubeLevel;

typedef struct {
    int index;
    color sideColor;
} IndexAndSide;

IndexAndSide getIndexAndSideFromNumber(int absoluteIndex) {
    color sideColor;
    int relativeIndex;

    if (absoluteIndex >= 0 && absoluteIndex <= 8) {
        sideColor = BLUE;
        relativeIndex = flatBlueSideOrder[absoluteIndex - 9 * 0];
    } else if (absoluteIndex >= 9 && absoluteIndex <= 17) {
        sideColor = ORANGE;
        relativeIndex = flatOrangeSideOrder[absoluteIndex - 9 * 1];
    } else if (absoluteIndex >= 18 && absoluteIndex <= 26) {
        sideColor = WHITE;
        relativeIndex = flatWhiteSideOrder[absoluteIndex - 9 * 2];
    } else if (absoluteIndex >= 27 && absoluteIndex <= 35) {
        sideColor = RED;
        relativeIndex = flatRedSideOrder[absoluteIndex - 9 * 3];
    } else if (absoluteIndex >= 36 && absoluteIndex <= 44) {
        sideColor = YELLOW;
        relativeIndex = flatYellowSideOrder[absoluteIndex - 9 * 4];
    } else if (absoluteIndex >= 45 && absoluteIndex <= 53) {
        sideColor = GREEN;
        relativeIndex = flatGreenSideOrder[absoluteIndex - 9 * 5];
    }

    IndexAndSide result;
    result.index = relativeIndex;
    result.sideColor = sideColor;
    return result;
}

action getActionFromChar(char letter) {
    switch (letter) {
        case 'R':
        case 'r':
            return R;
        case 'D':
        case 'd':
            return G;
        case 'U':
        case 'u':
            return B;
        case 'F':
        case 'f':
            return W;
        case 'L':
        case 'l':
            return O;
        case 'B':
        case 'b':
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
            strcpy(text, "ROTATE RIGHT");
            break;
        case G:
            strcpy(text, "ROTATE DOWN");
            break;
        case B:
            strcpy(text, "ROTATE UP");
            break;
        case W:
            strcpy(text, "ROTATE FRONT");
            break;
        case O:
            strcpy(text, "ROTATE LEFT");
            break;
        case Y:
            strcpy(text, "ROTATE BACK");
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
} LinearCube;

void initLinearCube(LinearCube* thisCube) {
    for (int index = 0; index < 9; index++) {
        thisCube->whiteSide[index] = WHITE;
        thisCube->yellowSide[index] = YELLOW;
        thisCube->redSide[index] = RED;
        thisCube->blueSide[index] = BLUE;
        thisCube->greenSide[index] = GREEN;
        thisCube->orangeSide[index] = ORANGE;
    }
}

void initFlatCube(LinearCube* thisCube) {
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

int isLinearCubeCorrect(LinearCube* thisCube) {
    IndexAndSide iterationSquare;
    int colorCount[6];
    memset(colorCount, 0, sizeof(colorCount));

    for (int i = 0; i < 54; i++) {
        iterationSquare = getIndexAndSideFromNumber(i);
        switch (iterationSquare.sideColor) {
            case BLUE:
                colorCount[thisCube->blueSide[iterationSquare.index]]++;
                break;
            case ORANGE:
                colorCount[thisCube->orangeSide[iterationSquare.index]]++;
                break;
            case WHITE:
                colorCount[thisCube->whiteSide[iterationSquare.index]]++;
                break;
            case RED:
                colorCount[thisCube->redSide[iterationSquare.index]]++;
                break;
            case YELLOW:
                colorCount[thisCube->yellowSide[iterationSquare.index]]++;
                break;
            case GREEN:
                colorCount[thisCube->greenSide[iterationSquare.index]]++;
                break;
            default:
                break;
        }
    }

    for (int i = 0; i < 6; i++) {
        if (colorCount[i] != 9) {
            return 0;
        }
    }
    if (thisCube->blueSide[8] != BLUE) {
        return 0;
    }
    if (thisCube->orangeSide[8] != ORANGE) {
        return 0;
    }
    if (thisCube->whiteSide[8] != WHITE) {
        return 0;
    }
    if (thisCube->redSide[8] != RED) {
        return 0;
    }
    if (thisCube->yellowSide[8] != YELLOW) {
        return 0;
    }
    if (thisCube->greenSide[8] != GREEN) {
        return 0;
    }
    return 1;
}

#endif
