#include <stdio.h>

typedef enum {WHITE, YELLOW, RED, BLUE, GREEN, ORANGE} color;

const char *colorNames = {"WHITE", "YELLOW", "RED", "BLUE", "GREEN", "ORANGE"};

void swap(color *x, color *y) {
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

void fillSideFromArray(color *cubeSide, char sideColors[]) {
    for (int index; index < 9; index++) {
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

void rotateSideBy90(Cube *thisCube, color sideToRotate) {
    switch (sideToRotate) {
        case WHITE:
            swap(thisCube->whiteSide[7], thisCube->whiteSide[3]);
            swap(thisCube->whiteSide[6], thisCube->whiteSide[4]);
            swap(thisCube->whiteSide[0], thisCube->whiteSide[2]);
            swap(thisCube->whiteSide[7], thisCube->whiteSide[5]);
            swap(thisCube->whiteSide[0], thisCube->whiteSide[4]);
            swap(thisCube->whiteSide[1], thisCube->whiteSide[3]);

            swap(thisCube->blueSide[0], thisCube->orangeSide[0]);
            swap(thisCube->blueSide[7], thisCube->orangeSide[7]);
            swap(thisCube->blueSide[6], thisCube->orangeSide[6]);

            swap(thisCube->orangeSide[6], thisCube->greenSide[6]);
            swap(thisCube->orangeSide[7], thisCube->greenSide[7]);
            swap(thisCube->orangeSide[0], thisCube->greenSide[0]);

            swap(thisCube->greenSide[6], thisCube->redSide[6]);
            swap(thisCube->greenSide[7], thisCube->redSide[7]);
            swap(thisCube->greenSide[0], thisCube->redSide[0]);
            break;
        case YELLOW:
            swap(thisCube->yellowSide[7], thisCube->yellowSide[3]);
            swap(thisCube->yellowSide[6], thisCube->yellowSide[4]);
            swap(thisCube->yellowSide[0], thisCube->yellowSide[2]);
            swap(thisCube->yellowSide[7], thisCube->yellowSide[5]);
            swap(thisCube->yellowSide[0], thisCube->yellowSide[4]);
            swap(thisCube->yellowSide[1], thisCube->yellowSide[3]);

            swap(thisCube->blueSide[4], thisCube->redSide[4]);
            swap(thisCube->blueSide[3], thisCube->redSide[3]);
            swap(thisCube->blueSide[6], thisCube->redSide[2]);

            swap(thisCube->redSide[2], thisCube->greenSide[2]);
            swap(thisCube->redSide[3], thisCube->greenSide[3]);
            swap(thisCube->redSide[4], thisCube->greenSide[4]);

            swap(thisCube->greenSide[4], thisCube->orangeSide[4]);
            swap(thisCube->greenSide[3], thisCube->orangeSide[3]);
            swap(thisCube->greenSide[2], thisCube->orangeSide[2]);
            break;
        case RED:
            swap(thisCube->redSide[0], thisCube->redSide[4]);
            swap(thisCube->redSide[7], thisCube->redSide[5]);
            swap(thisCube->redSide[1], thisCube->redSide[3]);
            swap(thisCube->redSide[0], thisCube->redSide[6]);
            swap(thisCube->redSide[1], thisCube->redSide[5]);
            swap(thisCube->redSide[2], thisCube->redSide[4]);

            swap(thisCube->blueSide[6], thisCube->whiteSide[3]);
            swap(thisCube->blueSide[5], thisCube->whiteSide[2]);
            swap(thisCube->blueSide[4], thisCube->whiteSide[1]);

            swap(thisCube->whiteSide[1], thisCube->greenSide[0]);
            swap(thisCube->whiteSide[2], thisCube->greenSide[1]);
            swap(thisCube->whiteSide[3], thisCube->greenSide[2]);

            swap(thisCube->greenSide[0], thisCube->yellowSide[3]);
            swap(thisCube->greenSide[1], thisCube->yellowSide[2]);
            swap(thisCube->greenSide[2], thisCube->yellowSide[1]);
            break;
        case BLUE:
            swap(thisCube->blueSide[1], thisCube->blueSide[7]);
            swap(thisCube->blueSide[2], thisCube->blueSide[6]);
            swap(thisCube->blueSide[5], thisCube->blueSide[3]);
            swap(thisCube->blueSide[2], thisCube->blueSide[0]);
            swap(thisCube->blueSide[7], thisCube->blueSide[3]);
            swap(thisCube->blueSide[6], thisCube->blueSide[4]);

            swap(thisCube->yellowSide[1], thisCube->orangeSide[4]);
            swap(thisCube->yellowSide[0], thisCube->orangeSide[5]);
            swap(thisCube->yellowSide[7], thisCube->orangeSide[6]);

            swap(thisCube->whiteSide[7], thisCube->orangeSide[4]);
            swap(thisCube->whiteSide[0], thisCube->orangeSide[5]);
            swap(thisCube->whiteSide[1], thisCube->orangeSide[6]);

            swap(thisCube->whiteSide[7], thisCube->redSide[0]);
            swap(thisCube->whiteSide[0], thisCube->redSide[1]);
            swap(thisCube->whiteSide[1], thisCube->redSide[2]);
            break;
        case GREEN:
            swap(thisCube->greenSide[6], thisCube->greenSide[2]);
            swap(thisCube->greenSide[5], thisCube->greenSide[3]);
            swap(thisCube->greenSide[7], thisCube->greenSide[1]);
            swap(thisCube->greenSide[4], thisCube->greenSide[6]);
            swap(thisCube->greenSide[7], thisCube->greenSide[3]);
            swap(thisCube->greenSide[0], thisCube->greenSide[2]);

            swap(thisCube->whiteSide[5], thisCube->orangeSide[2]);
            swap(thisCube->whiteSide[4], thisCube->orangeSide[1]);
            swap(thisCube->whiteSide[3], thisCube->orangeSide[0]);

            swap(thisCube->yellowSide[3], thisCube->orangeSide[2]);
            swap(thisCube->yellowSide[4], thisCube->orangeSide[1]);
            swap(thisCube->yellowSide[5], thisCube->orangeSide[0]);

            swap(thisCube->yellowSide[3], thisCube->redSide[6]);
            swap(thisCube->yellowSide[4], thisCube->redSide[5]);
            swap(thisCube->yellowSide[5], thisCube->redSide[4]);
            break;
        case ORANGE:
            swap(thisCube->orangeSide[4], thisCube->orangeSide[0]);
            swap(thisCube->orangeSide[3], thisCube->orangeSide[1]);
            swap(thisCube->orangeSide[5], thisCube->orangeSide[7]);
            swap(thisCube->orangeSide[4], thisCube->orangeSide[2]);
            swap(thisCube->orangeSide[5], thisCube->orangeSide[1]);
            swap(thisCube->orangeSide[6], thisCube->orangeSide[0]);

            swap(thisCube->blueSide[2], thisCube->yellowSide[5]);
            swap(thisCube->blueSide[1], thisCube->yellowSide[6]);
            swap(thisCube->blueSide[0], thisCube->yellowSide[7]);

            swap(thisCube->yellowSide[5], thisCube->greenSide[6]);
            swap(thisCube->yellowSide[6], thisCube->greenSide[5]);
            swap(thisCube->yellowSide[7], thisCube->greenSide[4]);

            swap(thisCube->greenSide[6], thisCube->whiteSide[7]);
            swap(thisCube->greenSide[5], thisCube->whiteSide[6]);
            swap(thisCube->greenSide[4], thisCube->whiteSide[5]);
            break;
        default:
            break;
    }
}
