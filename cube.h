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
