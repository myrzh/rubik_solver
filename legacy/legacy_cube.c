void rotateLinearSideBy90(LinearCube* thisCube, color sideToRotate, rotationMode mode) {
    int count = 1;
    if (mode == BACK) {
        count += 2;
    }

    int isPrinted = 0;

    for (int i = 0; i < count; i++) {
        switch (sideToRotate) {
        case WHITE:
            if (!isPrinted) {
                printf("ROTATE FRONT");
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
                printf("ROTATE BACK");
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
                printf("ROTATE RIGHT");
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
                printf("ROTATE UP");
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
                printf("ROTATE DOWN");
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
                printf("ROTATE LEFT");
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

    for (i=0; i<3; i++) for (j=0; j<3; j++) buffer[3+i][3+j] = c->front[i][j];
    for (i=0; i<3; i++) for (j=0; j<3; j++) buffer[3+i][9+j] = c->back[i][j];
    for (i=0; i<3; i++) for (j=0; j<3; j++) buffer[0+i][3+j] = c->up[i][j];
    for (i=0; i<3; i++) for (j=0; j<3; j++) buffer[6+i][3+j] = c->down[i][j];
    for (i=0; i<3; i++) for (j=0; j<3; j++) buffer[3+i][0+j] = c->left[i][j];
    for (i=0; i<3; i++) for (j=0; j<3; j++) buffer[3+i][6+j] = c->right[i][j];

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
