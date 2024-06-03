#ifndef ALGO_H
#define ALGO_H

#include <string.h>
#include <stdlib.h>

#define HORIZONTALUP 1
#define VERTICALUP 3
#define HORIZONTALDOWN -1
#define VERTICALDOWN -3

typedef struct Cube {
    char front[3][3];
    char back[3][3];
    char left[3][3];
    char right[3][3];
    char up[3][3];
    char down[3][3];
    char opeartion;
    struct Cube* previousState;
} Cube;

typedef struct {
    int shift;
    char* line;
} CubeLine;

typedef struct {
    int openNodes;
    int closedNodes;
    int size;
    Cube* cubes;
} SolutionTable;

typedef enum 
{
    FRONTROTATE, BACKROTATE, LEFTROTATE, RIGHTROTATE, UPROTATE, DOWNROTATE
} rotationType;

enum
{
    FIRSTSTEP1, FIRSTSTEP2, SECONDSTEP, THIRDSTEP, FOURTHSTEP, FIFTHSTEP, SIXTHSTEP, SEVENTHSTEP
};

void initCube(Cube* thisCube)
{
    memset(thisCube->front, 'w', sizeof(thisCube->front));
    memset(thisCube->back, 'y', sizeof(thisCube->back));
    memset(thisCube->left, 'o', sizeof(thisCube->left));
    memset(thisCube->right, 'r', sizeof(thisCube->right));
    memset(thisCube->up, 'b', sizeof(thisCube->up));
    memset(thisCube->down, 'g', sizeof(thisCube->down));
}

void rotateSideBy90(char panel[3][3])
{
    char tempPanel[3][3] = { '\0' };
    memcpy(tempPanel, panel, sizeof(tempPanel));
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            panel[i][j] = tempPanel[3 - j - 1][i];
        }
    }
}

void rotateOtherSides(CubeLine sides[5])
{
    int destinantionIndex = 0;
    int sourceIndex = 0;
    int destinationShift = 0;
    int sourceShift = 0;
    char* destinationBuf = NULL;
    char* sourceBuf = NULL;
    
    for (int i = 0; i < 5; i++)
    {
        destinantionIndex = i;
        sourceIndex = i + 1;
        if (sourceIndex >= 5)
        {
            sourceIndex = 0;
        }

        destinationBuf = sides[destinantionIndex].line;
        sourceBuf = sides[sourceIndex].line;

        destinationShift = sides[destinantionIndex].shift;
        sourceShift = sides[sourceIndex].shift;

        for (int j = 0; j < 3; j++)
        {
            *destinationBuf = *sourceBuf;
             destinationBuf += destinationShift;
           sourceBuf += sourceShift;
        }
    }
}

void cubeFrontRotate(Cube* thisCube)
{
    char temp[3] = { '\0' };
    CubeLine sides[5];
    sides[0].shift = 1;
    sides[0].line = temp;
    sides[1].shift = VERTICALUP;
    sides[1].line = &(thisCube->left[0][2]);
    sides[2].shift = HORIZONTALUP;
    sides[2].line = &(thisCube->down[0][0]);
    sides[3].shift = VERTICALDOWN;
    sides[3].line = &(thisCube->right[2][0]);
    sides[4].shift = HORIZONTALDOWN;
    sides[4].line = &(thisCube->up[2][2]);

    rotateOtherSides(sides);
    rotateSideBy90(thisCube->front);
};

void cubeBackRotate(Cube* thisCube)
{
    char temp[3] = { '\0' };
    CubeLine sides[5];
    sides[0].shift = 1;
    sides[0].line = temp;
    sides[1].shift = VERTICALUP;
    sides[1].line = &(thisCube->right[0][2]);
    sides[2].shift = HORIZONTALDOWN;
    sides[2].line = &(thisCube->down[2][2]);
    sides[3].shift = VERTICALDOWN;
    sides[3].line = &(thisCube->left[2][0]);
    sides[4].shift = HORIZONTALUP;
    sides[4].line = &(thisCube->up[0][0]);

    rotateOtherSides(sides);
    rotateSideBy90(thisCube->back);
};

void cubeUpRotate(Cube* thisCube)
{
    char temp[3] = { '\0' };
    CubeLine sides[5];
    sides[0].shift = 1;
    sides[0].line = temp;
    sides[1].shift = HORIZONTALUP;
    sides[1].line = &(thisCube->left[0][0]);
    sides[2].shift = HORIZONTALUP;
    sides[2].line = &(thisCube->front[0][0]);
    sides[3].shift = HORIZONTALUP;
    sides[3].line = &(thisCube->right[0][0]);
    sides[4].shift = HORIZONTALUP;
    sides[4].line = &(thisCube->back[0][0]);

    rotateOtherSides(sides);
    rotateSideBy90(thisCube->up);
};

void cubeDownRotate(Cube* thisCube)
{
    char temp[3] = { '\0' };
    CubeLine sides[5];
    sides[0].shift = 1;
    sides[0].line = temp;
    sides[1].shift = HORIZONTALUP;
    sides[1].line = &(thisCube->back[2][0]);
    sides[2].shift = HORIZONTALUP;
    sides[2].line = &(thisCube->right[2][0]);
    sides[3].shift = HORIZONTALUP;
    sides[3].line = &(thisCube->front[2][0]);
    sides[4].shift = HORIZONTALUP;
    sides[4].line = &(thisCube->left[2][0]);

    rotateOtherSides(sides);
    rotateSideBy90(thisCube->down);
};

void cubeLeftRotate(Cube* thisCube)
{
    char temp[3] = { '\0' };
    CubeLine sides[5];
    sides[0].shift = 1;
    sides[0].line = temp;
    sides[1].shift = VERTICALUP;
    sides[1].line = &(thisCube->down[0][0]);
    sides[2].shift = VERTICALUP;
    sides[2].line = &(thisCube->front[0][0]);
    sides[3].shift = VERTICALUP;
    sides[3].line = &(thisCube->up[0][0]);
    sides[4].shift = VERTICALDOWN;
    sides[4].line = &(thisCube->back[2][2]);

    rotateOtherSides(sides);
    rotateSideBy90(thisCube->left);
};

void cubeRightRotate(Cube* thisCube)
{
    char temp[3] = { '\0' };
    CubeLine sides[5];
    sides[0].shift = 1;
    sides[0].line = temp;
    sides[1].shift = VERTICALUP;
    sides[1].line = &(thisCube->up[0][2]);
    sides[2].shift = VERTICALUP;
    sides[2].line = &(thisCube->front[0][2]);
    sides[3].shift = VERTICALUP;
    sides[3].line = &(thisCube->down[0][2]);
    sides[4].shift = VERTICALDOWN;
    sides[4].line = &(thisCube->back[2][0]);

    rotateOtherSides(sides);
    rotateSideBy90(thisCube->right);
};

void cubeDoOp(Cube* thisCube, int op)
{
    switch (op)
    {
    case FRONTROTATE: 
        cubeFrontRotate(thisCube);
        break;
    case BACKROTATE:
        cubeBackRotate(thisCube);
        break;
    case LEFTROTATE:
        cubeLeftRotate(thisCube);
        break;
    case RIGHTROTATE:
        cubeRightRotate(thisCube);
        break;
    case UPROTATE:
        cubeUpRotate(thisCube);
        break;
    case DOWNROTATE:
        cubeDownRotate(thisCube);
        break;
    default:
        break;
    }
}

void randCube(Cube* thisCube, int n)
{
    while (n > 0)
    {
        cubeDoOp(thisCube, rand() % 6);
        n--;
    }
}

#endif
