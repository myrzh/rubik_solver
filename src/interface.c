#include <algo.h>
#include <cube.h>
#include <interface.h>
#include <objects.h>

rotationType getRotationFromColor(color clr) {
    switch (clr) {
        case RED:
            return RIGHTROTATE;
        case GREEN:
            return DOWNROTATE;
        case BLUE:
            return UPROTATE;
        case WHITE:
            return FRONTROTATE;
        case ORANGE:
            return LEFTROTATE;
        case YELLOW:
            return BACKROTATE;
        default:
            return RIGHTROTATE;
    }
}

void linearToMatrixCube(Cube *dst, LinearCube *src) {
    int counter = 0;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            dst->up[row][column] =
                getCharFromColor(src->blueSide[flatBlueSideOrder[counter]]);
            counter++;
        }
    }
    counter = 0;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            dst->left[row][column] =
                getCharFromColor(src->orangeSide[flatOrangeSideOrder[counter]]);
            counter++;
        }
    }
    counter = 0;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            dst->front[row][column] =
                getCharFromColor(src->whiteSide[flatWhiteSideOrder[counter]]);
            counter++;
        }
    }
    counter = 0;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            dst->right[row][column] =
                getCharFromColor(src->redSide[flatRedSideOrder[counter]]);
            counter++;
        }
    }
    counter = 0;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            dst->back[row][column] =
                getCharFromColor(src->yellowSide[flatYellowSideOrder[counter]]);
            counter++;
        }
    }
    counter = 0;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            dst->down[row][column] =
                getCharFromColor(src->greenSide[flatGreenSideOrder[counter]]);
            counter++;
        }
    }
}

void matrixToLinearCube(LinearCube *dst, Cube *src) {
    int counter = 0;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            dst->blueSide[flatBlueSideOrder[counter]] =
                getColorFromChar(src->up[row][column]);
            counter++;
        }
    }
    counter = 0;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            dst->orangeSide[flatOrangeSideOrder[counter]] =
                getColorFromChar(src->left[row][column]);
            counter++;
        }
    }
    counter = 0;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            dst->whiteSide[flatWhiteSideOrder[counter]] =
                getColorFromChar(src->front[row][column]);
            counter++;
        }
    }
    counter = 0;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            dst->redSide[flatRedSideOrder[counter]] =
                getColorFromChar(src->right[row][column]);
            counter++;
        }
    }
    counter = 0;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            dst->yellowSide[flatYellowSideOrder[counter]] =
                getColorFromChar(src->back[row][column]);
            counter++;
        }
    }
    counter = 0;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            dst->greenSide[flatGreenSideOrder[counter]] =
                getColorFromChar(src->down[row][column]);
            counter++;
        }
    }
}
