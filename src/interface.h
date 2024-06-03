#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include "cube.h"
#include "algo.h"
#include "objects.h"

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
            dst->up[row][column] = getCharFromColor(src->blueSide[flatBlueSideOrder[counter]]);
            counter++;
        }
    }
    counter = 0;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            dst->left[row][column] = getCharFromColor(src->orangeSide[flatOrangeSideOrder[counter]]);
            counter++;
        }
    }
    counter = 0;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            dst->front[row][column] = getCharFromColor(src->whiteSide[flatWhiteSideOrder[counter]]);
            counter++;
        }
    }
    counter = 0;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            dst->right[row][column] = getCharFromColor(src->redSide[flatRedSideOrder[counter]]);
            counter++;
        }
    }
    counter = 0;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            dst->back[row][column] = getCharFromColor(src->yellowSide[flatYellowSideOrder[counter]]);
            counter++;
        }
    }
    counter = 0;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            dst->down[row][column] = getCharFromColor(src->greenSide[flatGreenSideOrder[counter]]);
            counter++;
        }
    }
}

void matrixToLinearCube(LinearCube *dst, Cube *src) {
    int counter = 0;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            dst->blueSide[flatBlueSideOrder[counter]] = getColorFromChar(src->up[row][column]);
            counter++;
        }
    }
    counter = 0;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            dst->orangeSide[flatOrangeSideOrder[counter]] = getColorFromChar(src->left[row][column]);
            counter++;
        }
    }
    counter = 0;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            dst->whiteSide[flatWhiteSideOrder[counter]] = getColorFromChar(src->front[row][column]);
            counter++;
        }
    }
    counter = 0;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            dst->redSide[flatRedSideOrder[counter]] = getColorFromChar(src->right[row][column]);
            counter++;
        }
    }
    counter = 0;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            dst->yellowSide[flatYellowSideOrder[counter]] = getColorFromChar(src->back[row][column]);
            counter++;
        }
    }
    counter = 0;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            dst->greenSide[flatGreenSideOrder[counter]] = getColorFromChar(src->down[row][column]);
            counter++;
        }
    }
}

#ifndef _WIN32
static void renderMatrixCube(Cube *c) { // draw cube on screen (console)
    char buffer[9][12] = {0};
    int  i, j;

    for (i=0; i<3; i++) for (j=0; j<3; j++) buffer[3+i][3+j] = c->front[i][j];
    for (i=0; i<3; i++) for (j=0; j<3; j++) buffer[3+i][9+j] = c->back[i][j];
    for (i=0; i<3; i++) for (j=0; j<3; j++) buffer[0+i][3+j] = c->up[i][j];
    for (i=0; i<3; i++) for (j=0; j<3; j++) buffer[6+i][3+j] = c->down[i][j];
    for (i=0; i<3; i++) for (j=0; j<3; j++) buffer[3+i][0+j] = c->left[i][j];
    for (i=0; i<3; i++) for (j=0; j<3; j++) buffer[3+i][6+j] = c->right[i][j];

    for (i=0; i<9; i++) {
        for (j=0; j<12; j++) {
            switch (buffer[i][j]) {
            case 'w': case 'W': printf("\x1b[37m"); break;
            case 'y': case 'Y': printf("\x1b[33m"); break;
            case 'b': case 'B': printf("\x1b[34m"); break;
            case 'g': case 'G': printf("\x1b[32m"); break;
            case 'o': case 'O': printf("\x1b[35m"); break;
            case 'r': case 'R': printf("\x1b[31m"); break;
            }
            printf(buffer[i][j] ? "# " : "  ");
            printf("\x1b[0m");
        }
        printf("\n");
    }
    printf("\x1b[0m");
}
#else
#include <windows.h>
#include <conio.h>
static void renderMatrixCube(Cube *c) // draw cube on screen, now only working on win32 console
{
    char buffer[9][12] = {0};
    int  i, j;

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD wOldColorAttrs;
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

    // save the current color
    GetConsoleScreenBufferInfo(h, &csbiInfo);
    wOldColorAttrs = csbiInfo.wAttributes;

    for (i=0; i<3; i++) for (j=0; j<3; j++) buffer[3+i][3+j] = c->f[i][j];
    for (i=0; i<3; i++) for (j=0; j<3; j++) buffer[3+i][9+j] = c->b[i][j];
    for (i=0; i<3; i++) for (j=0; j<3; j++) buffer[0+i][3+j] = c->u[i][j];
    for (i=0; i<3; i++) for (j=0; j<3; j++) buffer[6+i][3+j] = c->d[i][j];
    for (i=0; i<3; i++) for (j=0; j<3; j++) buffer[3+i][0+j] = c->l[i][j];
    for (i=0; i<3; i++) for (j=0; j<3; j++) buffer[3+i][6+j] = c->r[i][j];

    for (i=0; i<9; i++) {
        for (j=0; j<12; j++) {
            switch (buffer[i][j]) {
            case 'w': case 'W': SetConsoleTextAttribute(h, FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE); break;
            case 'y': case 'Y': SetConsoleTextAttribute(h, FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN); break;
            case 'b': case 'B': SetConsoleTextAttribute(h, FOREGROUND_INTENSITY|FOREGROUND_BLUE ); break;
            case 'g': case 'G': SetConsoleTextAttribute(h, FOREGROUND_INTENSITY|FOREGROUND_GREEN); break;
            case 'o': case 'O': SetConsoleTextAttribute(h, FOREGROUND_RED|FOREGROUND_BLUE       ); break;
            case 'r': case 'R': SetConsoleTextAttribute(h, FOREGROUND_INTENSITY|FOREGROUND_RED  ); break;
            }
            printf(buffer[i][j] ? "# " : "  ");
        }
        printf("\n");
    }

    // restore the original color
    SetConsoleTextAttribute(h, wOldColorAttrs);
}
#endif

#endif
